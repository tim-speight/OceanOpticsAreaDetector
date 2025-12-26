TOP = ..
include $(TOP)/configure/CONFIG

DIRS += oceanDirectSupport
DIRS += src
src_DEPENDS_DIRS += oceanDirectSupport

#DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard *db*))
DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard *Db*))
#DIRS := $(DIRS) $(filter-out $(DIRS), $(wildcard *op*))
include $(TOP)/configure/RULES_DIRS

