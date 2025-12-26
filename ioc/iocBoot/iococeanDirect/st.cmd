#!../../bin/linux-x86_64/oceanDirectApp

#- You may have to change oceanDirect to something else
#- everywhere it appears in this file

< envPaths

# Prefix macro AD-plugins stack
epicsEnvSet("DEVICE_ID", "FACILITY_DESIGNATOR")
epicsEnvSet("PREFIX", "$(DEVICE_ID):")
# Autosave
epicsEnvSet("SAVE_DIR", "$(TOP)/autoSaveRestore")
# The port name for the detector
epicsEnvSet("PORT",   "SPEC1")
# Address for device, always zero
epicsEnvSet("ADDR",   "0")
# Really large queue so we can stream to disk at full camera speed
epicsEnvSet("QSIZE",  "2000")   
# The maximum number of time series points in the NDPluginStats plugin
epicsEnvSet("NCHANS", "2048")
# The maximum number of frames buffered in the NDPluginCircularBuff plugin
epicsEnvSet("CBUFFS", "500")
epicsEnvSet("EPICS_DB_INCLUDE_PATH", "$(TOP)/db")
#Spectrometer slits >> HR4=3648 and ST=1536
epicsEnvSet("NELEMENTS", "3648") 
#Serial ID of the spectrometer
epicsEnvSet("SERIAL_ID", "DEVSERIALNUM") 

epicsEnvSet("STS", "-STS")
epicsEnvSet("TFL", "-TFL")

cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/oceanDirectApp.dbd"
oceanDirectApp_registerRecordDeviceDriver pdbbase

OceanDirectConfig("$(PORT)", "$(SERIAL_ID)")

## Load record instances
dbLoadRecords("oceanDirect.template", "P=$(PREFIX), R=spec1:, Q=image1:, PORT=$(PORT), NELEMENTS=$(NELEMENTS)")
dbLoadRecords("trafficLight.db", "P=$(PREFIX), Q=image1:,TFL-PREFIX=$(DEVICE_ID)$(TFL)")
dbLoadRecords("iocAdminSoft.db", "IOC=$(DEVICE_ID)$(STS)")
# Create a standard arrays plugin
NDStdArraysConfigure("Image1", 5, 0, "$(PORT)", 0, 0)
# Use this line for 64-bit float data only
dbLoadRecords("NDStdArrays.template", "P=$(PREFIX),R=image1:,PORT=Image1,ADDR=0,TIMEOUT=1,NDARRAY_PORT=$(PORT),TYPE=Float64,FTVL=DOUBLE,NELEMENTS=$(NELEMENTS)")

cd "${TOP}/iocBoot/${IOC}"

# Load all other plugins using commonPlugins.cmd
< ./oceanDirect_commonPlugins.cmd
set_requestfile_path("$(TOP)/autoSaveRestore")
set_requestfile_path("$(TOP)/db")
set_savefile_path("$(TOP)/autoSaveRestore")
set_pass0_restoreFile("auto_settings.sav")
set_pass1_restoreFile("auto_settings.sav")
save_restoreSet_status_prefix("$(PREFIX)")
dbLoadRecords("save_restoreStatus.db", "P=$(PREFIX)")
dbLoadRecords("configMenu.db", "P=$(PREFIX), CONFIG=ADAutoSave")

# Set the callback queue size to 5000, up from default of 2000 in base.
# This can be needed to avoid errors "callbackRequest: cbLow ring buffer full".
callbackSetQueueSize(5000)

#asynSetTraceIOMask($(PORT),0,0x2)
#asynSetTraceMask($(PORT),0,255)

# deploy machine protection if needed 
epicsEnvSet("MPS_DEPLOYMENT_SCRIPT", "NoMPS")
< "${TOP}/iocBoot/${IOC}/${MPS_DEPLOYMENT_SCRIPT}"

iocInit

create_monitor_set("auto_settings.req", 30, "P=$(PREFIX), R=spec1:, Q=image1:")

dbpf $(PREFIX)spec1:Wavelengths.PROC 1
#dbpf $(PREFIX)spec1:Acquire 1
#dbpf $(PREFIX)spec1:DoAnalysis.PROC 1
