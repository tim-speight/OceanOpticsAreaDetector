#ifndef OCEANDIRECT_H
#define OCEANDIRECT_H

#include <vector>
#include <epicsEvent.h>
#include <epicsMessageQueue.h>



/* Internal asyn driver parameters */
#define OceanDirectAcquiringString                "OceanDirectAcquiring"
#define OceanDirectDelayTimeString                "OceanDirectDelayTime"
#define OceanDirectSpectrumXAxisString            "OceanDirectSpectrumXAxis"
#define OceanDirectWaveCoeffsString               "OceanDirectWaveCoeffs"
#define OceanDirectConnectionStatusString         "OceanDirectConnectionStatus"

class OceanDirect : public ADDriver
{
public:
    OceanDirect(const char *portName, const char *serialNumber);
    
    /* virtual methods to override from asynNDArrayDriver */
    virtual asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);
    virtual asynStatus writeFloat64(asynUser *pasynUser, epicsFloat64 value);
    virtual asynStatus readFloat64Array(asynUser *pasynUser, epicsFloat64 *value, size_t nElements, size_t *nIn);
  
    /* Local methods to this class */
    void triggerTask();
    void acquireTask();
    void connectionMonitorTask();
    int  dataCallback(double *pData);
    
protected:
    int      OceanDirectAcquiring;           /* int32, read */
    int      OceanDirectDelayTime;
    int      OceanDirectSpectrumXAxis;
    int      OceanDirectWaveCoeffs;
    int      OceanDirectConnectionStatus;
    
    double     acquireTime;
    double   acquirePeriod;
    double       delayTime;   
    
private:
    long deviceId;
    char deviceSerialNumber[20];
    int error = 0;
    

    int formattedSpectrumLength;
    double *formattedSpectrumArray;
    double *wavelengthsArray;
    int    numWavelengthCoeffincients = 5;
    double *wavelengthCoefficients;
    
    long findDevice(const char * serNum);
    
    asynStatus handleAcquire();

    epicsEvent *cmdStartEvent_;
    epicsEvent *cmdStopEvent_;
    epicsEvent *stoppedEvent_;
    epicsEvent *acquireEvent_;
    epicsEvent *acquireCompleteEvent_;
    
    bool watingOnSpectrum_;
    
    ADImageMode_t imageMode_;
    
    int   triggerMode_;
    int     numImages_;
    
    bool acquiring_;
    bool fetchingSpectrum_;
    
};


#ifdef __cplusplus
extern "C"
{
#endif

int OceanDirectConfig(const char *portName, const char *serialNumber);

#ifdef __cplusplus
}
#endif


#endif /* OCEANDIRECT_H */
