/* oceanDirect.cpp
 *
 * Driver for Ocean Insight optical spectrometers
 *
 * John Dobbins
 * CHESS, Cornell University
 *
 * Thanks to Mark Rivers
 *
 */
 /* Standard includes... */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <iterator>

/* EPICS includes */
#include <epicsString.h>
#include <epicsTime.h>
#include <epicsThread.h>
#include <epicsEvent.h>
#include <epicsMessageQueue.h>
#include <epicsMutex.h>
#include <epicsExit.h>
#include <envDefs.h>
#include <iocsh.h>

/* Area Detector includes */
#include <ADDriver.h>

#include "api/OceanDirectAPI.h"

#include <epicsExport.h>
#include "oceanDirect.h"


#define SDK_VERSION       "3.1.0"
#define DRIVER_VERSION       "1.0.0"

/** Trigger modes */
typedef enum {
    TMSoftware,
    TMExternalEdge,
    TMExternalLevel,
} OceanDirectTriggerMode;


static void triggerTaskC(void *drvPvt)
{
    OceanDirect *pOceanDirect = (OceanDirect *)drvPvt;
    printf("triggerTaskC\n");
    pOceanDirect->triggerTask();

}

static void acquireTaskC(void *drvPvt)
{
    OceanDirect *pOceanDirect = (OceanDirect *)drvPvt;
    printf("acquireTaskC\n");
    pOceanDirect->acquireTask();

}

static void connectionMonitorTaskC(void *drvPvt)
{
    OceanDirect *pOceanDirect = (OceanDirect *)drvPvt;
    printf("connectionMonitorTaskC\n");
    pOceanDirect->connectionMonitorTask();

}

/** Only used for debugging/error messages to identify where the message comes from*/
static const char *driverName = "OceanDirect";

extern "C" int OceanDirectConfig(const char *portName, const char *serialNumber )
{
    new OceanDirect(portName, serialNumber);
    return 0;
}

OceanDirect::OceanDirect(const char *portName, const char * serNum )
    : ADDriver(portName, 1, 0, 0, 0,
            asynInt32Mask | asynFloat64Mask | asynInt32ArrayMask | asynFloat64ArrayMask | asynGenericPointerMask | asynOctetMask | asynDrvUserMask,
            asynInt32Mask | asynFloat64Mask | asynInt32ArrayMask | asynFloat64ArrayMask | asynGenericPointerMask | asynOctetMask,
            ASYN_MULTIDEVICE | ASYN_CANBLOCK, 1, 0, 0)
{

    printf("Hello from OceanDirect Driver\n");
    
    int status = asynSuccess;
    const char *functionName = "OceanDirect";
    strncpy(deviceSerialNumber, serNum, sizeof(deviceSerialNumber));
    deviceSerialNumber[sizeof(deviceSerialNumber) - 1] = '\0'; // Ensure null-termination    
    // Start by initializing the SDK
    odapi_initialize();
    
    /* Internal asyn driver parameters */
    createParam(OceanDirectAcquiringString,            asynParamInt32, &OceanDirectAcquiring);
    createParam(OceanDirectDelayTimeString,          asynParamFloat64, &OceanDirectDelayTime);
    createParam(OceanDirectSpectrumXAxisString, asynParamFloat64Array, &OceanDirectSpectrumXAxis);
    createParam(OceanDirectWaveCoeffsString,    asynParamFloat64Array, &OceanDirectWaveCoeffs);
    createParam(OceanDirectConnectionStatusString,    asynParamInt32, &OceanDirectConnectionStatus);
    

    deviceId = findDevice(serNum);    
    if( deviceId < 0 ) {
        printf("OceanDirect::OceanDirect failed to find device!\n");
        return;
    }

    /* Create the start and stop events that will be used to signal our
     * triggerTask when to start/stop polling the HW     */
    cmdStartEvent_        = new epicsEvent();
    cmdStopEvent_         = new epicsEvent();
    stoppedEvent_         = new epicsEvent();
    acquireEvent_         = new epicsEvent();
    acquireCompleteEvent_ = new epicsEvent();
    
    // Get the device name
    const int nameLength = 32;
    char deviceName[nameLength] = { 0 };
    odapi_get_device_name(deviceId, &error, deviceName, nameLength);
    if (error != 0) {
         printf("OceanDirect::OceanDirect Failed to cread device name, error %i", error);  
    }
    
    // Get the formatted spectrum length
    formattedSpectrumLength = odapi_get_formatted_spectrum_length(deviceId, &error);
    if (error != 0) {
         printf("OceanDirect::OceanDirect Failed to get formatted spectrum length, error %i", error);  
    }
    formattedSpectrumArray = (double *)malloc(formattedSpectrumLength*sizeof(double));
    
    wavelengthsArray = (double *)malloc(formattedSpectrumLength*sizeof(double));
    
    wavelengthCoefficients =(double *)malloc(numWavelengthCoeffincients*sizeof(double));
     
    setStringParam(NDDriverVersion, DRIVER_VERSION);
    setStringParam(ADManufacturer, "Ocean Optics");
    setStringParam(ADModel, deviceName);
    setStringParam(ADSDKVersion, SDK_VERSION);
    setStringParam(ADSerialNumber, serNum);
    /* Start up acquisition thread */
    setIntegerParam(OceanDirectAcquiring, 0);
    
    callParamCallbacks();
    
    acquiring_ = 0;
    
    status = (epicsThreadCreate("triggerTask",
              epicsThreadPriorityMedium,
              epicsThreadGetStackSize(epicsThreadStackMedium),
              (EPICSTHREADFUNC)triggerTaskC, this) == NULL);
    if (status) {
        printf("%s:%s epicsThreadCreate failure for trigger task\n",
                driverName, functionName);
        return ;
    }
    
    status = (epicsThreadCreate("acquireTask",
              epicsThreadPriorityMedium,
              epicsThreadGetStackSize(epicsThreadStackMedium),
              (EPICSTHREADFUNC)acquireTaskC, this) == NULL);
    if (status) {
        printf("%s:%s epicsThreadCreate failure for acquire task\n",
                driverName, functionName);
        return ;
    }  
    
    status = (epicsThreadCreate("connectionMonitorTask",
              epicsThreadPriorityMedium,
              epicsThreadGetStackSize(epicsThreadStackMedium),
              (EPICSTHREADFUNC)connectionMonitorTaskC, this) == NULL);
    if (status) {
        printf("%s:%s epicsThreadCreate failure for connection Monitor task\n",
                driverName, functionName);
        return ;
    }  

    return;
}

long OceanDirect::findDevice(const char * serNum) {
    // Next search for a device with a matching serial number
    int deviceCount = odapi_probe_devices();
    if (deviceCount < 1) {
        printf("OceanDirect::findDevice No connected spectrometers found\n");
        return -1;
    }
    else {
        // Retrieve the number of device IDs from the connected spectrometers.
        // The device ID will be used to address a specific spectrometer in later function calls
        int deviceIdCount = odapi_get_number_of_device_ids();
        // Declare a vector to hold the device IDs
        std::vector<long> deviceIds(deviceIdCount);
        // then get the device IDs
        int retrievedIdCount = odapi_get_device_ids(deviceIds.data(), deviceIdCount);
	if (retrievedIdCount == 0) return -1;
        
        // Errors in the following functions will be reported in an integer argument, zero indicates success
        
        int serialNumberLength;
        for(int i = 0; i < retrievedIdCount; i++) {
            // Open the device found to enable it to be used
            odapi_open_device(deviceIds[i], &error);
            if (error != 0) {
                printf("OceanDirect::findDevice Failed to open the spectrometer. i = %i, error code is: %i\n", i, error);
                continue;
            }
            serialNumberLength = odapi_get_serial_number_maximum_length(deviceIds[0], &error);
            std::unique_ptr<char> serialNumber(new char[serialNumberLength]);
            odapi_get_serial_number(deviceIds[i], &error, serialNumber.get(), serialNumberLength);
            if (error != 0) {
                printf("OceanDirect::OceanDirect Failed to retrieve the spectrometer serial number, i = %i, error code is: %i\n", i, error);
                odapi_close_device(deviceIds[0], &error);
                if(error != 0) {
                    printf("OceanDirect::findDevice Failed to close device number %i, error %i", i , error);
                }
            }
            else {
                if( strcmp(serNum, serialNumber.get()) == 0 ) {
                    
                    printf( "OceanDirect::findDevice Found S/N %s\n", serNum);
                    return deviceIds[i];
                }
                else {
                    odapi_close_device(deviceIds[i], &error);
                    if(error != 0) {
                        printf("OceanDirect::findDevice Failed to close device number %i, error %i", i , error);
                    }
                }
            }     
            
        }
 
    }
    
    return 0;
}

/* virtual methods to override from asynNDArrayDriver */
asynStatus OceanDirect::writeInt32( asynUser *pasynUser, epicsInt32 value)
{
    asynStatus status = asynSuccess;
    int function = pasynUser->reason;
    int addr;
    const char* functionName = "writeInt32";
   
    pasynManager->getAddr(pasynUser, &addr);
    status = setIntegerParam(addr, function, value);
   
    if (function == ADAcquire)
    {
        this->handleAcquire();
        status = setIntegerParam(addr, function, value);
    }
    
    if (function == ADNumImages)
    {
        setIntegerParam(addr, function, value);        
    }    

    if (function == ADImageMode)
    {     
        setIntegerParam(addr, function, (epicsInt32)(value) );        
    }
    
    if (function == ADTriggerMode)
    {     
        setIntegerParam(addr, function, (epicsInt32)(value) );        
    }

    // Call the callback
    callParamCallbacks(addr);
    asynPrint(pasynUserSelf, ASYN_TRACE_FLOW,
        "%s:%s: exit\n",
        driverName, functionName);
    return status;
}


asynStatus OceanDirect::writeFloat64( asynUser *pasynUser, epicsFloat64 value)
{
    asynStatus status = asynSuccess;
    int function = pasynUser->reason;
    int addr;
    const char* functionName = "writeFloat64";
    
    unsigned long readback;
    
    pasynManager->getAddr(pasynUser, &addr);
    
    // printf("OceanDirect::writeFloat64 function = %i\n", function);

    if (function == ADAcquireTime)
    {
        // Spectrometer integration time is in uSec
        acquireTime = (double)value;
        unsigned long long_value = value*1.0e6;
        // printf("OceanDirect::writeFloat64 = %lu\n", long_value);
        odapi_set_integration_time_micros(deviceId, &error, long_value);
        if( error != 0 )  status = asynError;
        
        readback = odapi_get_integration_time_micros(deviceId, &error);
        
        // printf("OceanDirect::writeFloat64 readback = %lu\n", readback);
        setDoubleParam(addr, function, (epicsFloat64)(readback/1.0e6) );
    }
    
    if (function == ADAcquirePeriod)
    {
        acquirePeriod = (double)value;
        
        setDoubleParam(addr, function, (epicsFloat64)(acquirePeriod) );
    }
    
    if (function == OceanDirectDelayTime)
    {
        delayTime = (double)value;
        
        setDoubleParam(addr, function, (epicsFloat64)(delayTime) );
    }    

    
    // Call the callback 
    callParamCallbacks(addr);
    asynPrint(pasynUserSelf, ASYN_TRACE_FLOW,
        "%s:%s: exit\n",
        driverName, functionName);
    return status;
}

asynStatus OceanDirect::readFloat64Array( asynUser *pasynUser, epicsFloat64 *value, size_t nElements, size_t *nIn) 
{
  int function = pasynUser->reason;
  int addr;
  int num_coeff_read;
  int wavelengths_read;
  static const char *functionName = "readFloat64Array";

  //int currentlyAcquiring;
  //getIntegerParam(ADAcquire, &currentlyAcquiring);
  //std::cout << "InAcquisition: " << currentlyAcquiring;
  //std::cout << std::endl;

  this->getAddress(pasynUser, &addr);

  *nIn = 0;

  if (function == OceanDirectSpectrumXAxis) {
    odapi_get_wavelengths(deviceId, &error, wavelengthsArray, formattedSpectrumLength);

    if (error != 0) {
         printf("OceanDirect::readFloatArray Failed to get spectrum wavelengths, error %i", error);
         return asynError;  
    } else {
        // std::copy(&wavelengthsArray[0], &wavelengthsArray[10], std::ostream_iterator<double>(std::cout, " "));
        // std::cout << std::endl;
        memcpy(value, wavelengthsArray, formattedSpectrumLength*sizeof(double));
        *nIn = formattedSpectrumLength;
    }
  }

  if (function == OceanDirectWaveCoeffs) {
    // Get the wavelength coefficients
    num_coeff_read = odapi_get_wavelength_coeffs(deviceId, &error, wavelengthCoefficients, numWavelengthCoeffincients);
    if (error != 0) {
         printf("OceanDirect::readFloatArray Failed to get spectrum coefficients, error %i", error);
         return asynError;  
    } else {
        // std::copy(&wavelengthsArray[0], &wavelengthsArray[10], std::ostream_iterator<double>(std::cout, " "));
        // std::cout << std::endl;
        memcpy(value, wavelengthCoefficients, numWavelengthCoeffincients*sizeof(double));
        *nIn = numWavelengthCoeffincients;
    }
  } 
  
  return asynSuccess;
}

asynStatus OceanDirect::handleAcquire()
{
    asynStatus status = asynSuccess;
    int value;

    const char *functionName = "handleAcquire";

    getIntegerParam(ADAcquire, &value);

    asynPrint(pasynUserSelf, ASYN_TRACE_FLOW,
        "%s::%s value =%d",
        driverName, functionName, value);
        
    /* if already acquiring we just ignore and return */
    if( acquiring_ == true && value == 1 ) {
        //already acquiring
        return status;
    }
    
    if( acquiring_ == true && value ==  0 ) {
         // signal stop to triggrTask
         acquiring_ = false;
         return status;
         
    }

    if( acquiring_ == false && value == 1 ) {
        // signal cmdStartEvent to start the polling thread
        acquiring_ = true;
        // read triggerMode, imageMode, numImages at the start of acquiisiton
        int imageMode_int;
        getIntegerParam(ADImageMode, &imageMode_int );
        imageMode_ = (ADImageMode_t)imageMode_int;
        getIntegerParam(ADTriggerMode, &triggerMode_);
        getIntegerParam(ADNumImages, &numImages_);
        
        cmdStartEvent_->signal();
        asynPrint(pasynUserSelf, ASYN_TRACE_FLOW,
        "%s:%s: exit\n",
        driverName, functionName);
        return status;
    }
    
    if( acquiring_ == false && value == 0 ) {
        // nothing to stop
        return status;
    }
    
    return status;
}

void OceanDirect::connectionMonitorTask() 
{
    const char* functionName = "connectionMonitorTask";
    char buffer[20];
    while(true) {
        memset(&buffer[0], 0, sizeof(buffer));
        lock();
        odapi_get_serial_number(deviceId ,&error, buffer,20);
        if(strcmp(buffer,  deviceSerialNumber) == 0){
            setIntegerParam(OceanDirectConnectionStatus, 1);
        }
        else {
            setIntegerParam(OceanDirectConnectionStatus, 0);
        }
        callParamCallbacks();
        unlock();
        epicsThreadSleep(5.0); // thread runs at 5 seconds intervals
    }
}
void OceanDirect::triggerTask() 
{
    const char* functionName = "triggerTask";
    
    lock();
    
    asynPrint(this->pasynUserSelf, ASYN_TRACE_FLOW,
        "%s:%s trigger task started!\n",
        driverName, functionName);
        
    unlock();
    
    while(true) {
        cmdStartEvent_->wait();
        // printf("OceanDirect::triggerTask received start\n");
        
        lock();

        odapi_adv_set_trigger_mode(deviceId, &error, triggerMode_);

        unlock();
        
        if( imageMode_ == ADImageContinuous) {
            while( acquiring_ == true ) {  
            
                acquireEvent_->signal();
                epicsThreadSleep(acquirePeriod);
        
            }
        }
        
        if( imageMode_ == ADImageMultiple ) {
            int N = numImages_;
            // printf("OceanDirect::triggerTask nuMImages_ = %d\n", numImages_);
            // printf("OceanDirect::triggerTask imageMode_ == ADImageMultiple\n");
            while( acquiring_ == true && N > 0 ) {
            
                acquireEvent_->signal();
                N = N -1;
                if(triggerMode_ == TMSoftware ) {
                    epicsThreadSleep(acquirePeriod);
                } else {
                    acquireCompleteEvent_->wait();
                }
            }     
        }
        
        if( imageMode_ == ADImageSingle ) {
            acquireEvent_->signal();
            epicsThreadSleep(acquirePeriod);
        }
        
        acquiring_ = 0;
        
        lock();
        setIntegerParam(OceanDirectAcquiring, 0);
        setIntegerParam(ADAcquire, 0);
        callParamCallbacks();
        unlock();
     }
}


/*
 *  acquire data from the spectrometer
 */
void OceanDirect::acquireTask()
{
    // const char* functionName = "acquire";
    
    lock();
    
    while(true) {
    
        unlock();
    
        acquireEvent_->wait();
        
        lock();
    
        odapi_get_formatted_spectrum(deviceId, &error, formattedSpectrumArray, formattedSpectrumLength);
        if(error != 0) {
            printf("OceanDirect::acquisitionTask Failed to get formatted spectrum, error %i\n", error);
        } else {
            // std::copy(&formattedSpectrumArray[0], &formattedSpectrumArray[10], std::ostream_iterator<double>(std::cout, " "));
            // std::cout << std::endl;
            dataCallback(formattedSpectrumArray);
        }
        
        if( triggerMode_ != TMSoftware) {
            acquireCompleteEvent_->signal();
        }
    }
    
    unlock();
}


epicsInt32 OceanDirect::dataCallback(double *pData)
{
    NDArray *pImage; 
    int ndims = 1;
    size_t dims[2];
    int totalBytes; 
    int arrayCallbacks;
    int imageCounter;
    epicsTimeStamp timeStamp; 
    epicsInt32 colorMode = NDColorModeMono;

    // printf("OceanDirect::dataCallback start\n");

    if (pData == NULL ) return(0); 

    dims[0] = formattedSpectrumLength;
    dims[1] = 1;
    totalBytes = this->formattedSpectrumLength*sizeof(double);

    /* Get the current time */
    epicsTimeGetCurrent(&timeStamp); 

    /* Allocate a new image buffer */
    pImage = this->pNDArrayPool->alloc(ndims, dims, NDFloat64, totalBytes, NULL);

    memcpy(pImage->pData,  pData, totalBytes); 
    pImage->dataType = NDFloat64;
    pImage->ndims = ndims; 
    pImage->dims[0].size = dims[0]; 
    pImage->dims[0].offset = 0; 
    pImage->dims[0].binning = 1; 
    pImage->dims[1].size = dims[1]; 
    pImage->dims[1].offset = 0; 
    pImage->dims[1].binning = 1; 

    pImage->pAttributeList->add("ColorMode", "Color Mode", NDAttrInt32, &colorMode);

    /* Increase image counter */
    getIntegerParam(NDArrayCounter, &imageCounter);
    imageCounter++;
    setIntegerParam(NDArrayCounter, imageCounter);

    /* Set the uniqueId and time stamp */
    pImage->uniqueId = imageCounter; 
    pImage->timeStamp = timeStamp.secPastEpoch + timeStamp.nsec / 1e9; 

    /* Get any attributes that have been defined for this driver */        
    this->getAttributes(pImage->pAttributeList);

    getIntegerParam(NDArrayCallbacks, &arrayCallbacks);
    // if (arrayCallbacks) {
    if (true) {
        /* Call the NDArray callback */
        // printf("OceanDirect::dataCallback NDArrayCallback\n");
        doCallbacksGenericPointer(pImage, NDArrayData, 0);
    }

    /* We save the most recent good image buffer so it can be used in the
     * readADImage function.  Now release it. */
    if (this->pArrays[0]) this->pArrays[0]->release();
    this->pArrays[0] = pImage;
    
    // printf("OceanDirect::dataCallback end\n");

    /* Update any changed parameters */
    callParamCallbacks();

    return(1);
}

static const iocshArg OceanDirectConfigArg0 = {"Asyn port name", iocshArgString};
static const iocshArg OceanDirectConfigArg1 = {"Serial Number", iocshArgString};
static const iocshArg * const OceanDirectConfigArgs[] =  {&OceanDirectConfigArg0, &OceanDirectConfigArg1};

static const iocshFuncDef configOceanDirect = {"OceanDirectConfig", 2, OceanDirectConfigArgs};

static void configOceanDirectCallFunc(const iocshArgBuf *args)
{
    OceanDirectConfig(args[0].sval, args[1].sval);
}

static void oceanDirectRegister(void)
{
    iocshRegister(&configOceanDirect, configOceanDirectCallFunc);
}

extern "C" {
epicsExportRegistrar(oceanDirectRegister);
}
