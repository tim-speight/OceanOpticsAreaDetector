TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE

#----------------------------------------------------
# Create and install (or just install) into <top>/db
# databases, templates, substitutions like this
DB += oceanDirect.template
DB += heartbeat.db
DB += trafficLight.db

DB_INSTALLS += $(DEVIOCSTATS)/db/iocAdminSoft.db
DB_INSTALLS += $(wildcard $(AUTOSAVE)/db/*)
DB_INSTALLS += $(filter %.db %.req %.template, $(wildcard $(AUTOSAVE)/asApp/db/*))
DB_INSTALLS += $(filter %.db %.req %.template, $(wildcard $(AREA_DETECTOR)/ADCore/db/*))
#----------------------------------------------------
# If <anyname>.db template is not named <anyname>*.template add
# <anyname>_template = <templatename>

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

