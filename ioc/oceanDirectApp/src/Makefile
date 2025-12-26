TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

DBD += oceanDirectSupport.dbd
PROD_NAME = oceanDirectApp

USR_CXXFLAGS_Linux += -std=c++11
USR_INCLUDES += -I $(TOP)/oceanDirectApp/oceanDirectSupport/include

LIBRARY_IOC_Linux += oceanDirect
PROD_IOC_Linux  += $(PROD_NAME)

LIB_SRCS += oceanDirect.cpp

LIB_LIBS          += asyn 
LIB_LIBS          += ADBase
LIB_LIBS          += pv
LIB_LIBS          += $(EPICS_BASE_IOC_LIBS)
PROD_SYS_LIBS += oceandirect
USR_LDFLAGS += -L$(TOP)/lib/$(EPICS_HOST_ARCH)

DBD += $(PROD_NAME).dbd  #OceanDirectSupport library
$(PROD_NAME)_DBD += base.dbd
$(PROD_NAME)_DBD += oceanDirectSupport.dbd
$(PROD_NAME)_DBD += asub.dbd
$(PROD_NAME)_DBD += opcua.dbd
## <name>_registerRecordDeviceDriver.cpp will be created from <name>.dbd

$(PROD_NAME)_SRCS += $(PROD_NAME)_registerRecordDeviceDriver.cpp
$(PROD_NAME)_SRCS += $(PROD_NAME)Main.cpp
$(PROD_NAME)_SRCS += fwhm_calculation.c

$(PROD_NAME)_LIBS += oceanDirect
$(PROD_NAME)_LIBS += pv
$(PROD_NAME)_LIBS += opcua

include $(ADCORE)/ADApp/commonDriverMakefile

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
