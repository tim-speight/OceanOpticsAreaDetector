TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#INC += DLL_DPP_Callback.h

#INC += $(patsubst ../%, %, $(wildcard ../include/common/*))

ifeq ($(OS_CLASS), Linux)
	ifeq ($(ARCH_CLASS), x86_64)
		LIB_INSTALLS  += ../os/linux-x86_64/liboceandirect.so
	endif
endif

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
