
ifeq ($(strip $(ADB_MOUSE_ENABLE)), yes)
    OPT_DEFS += -DADB_MOUSE_ENABLE
    MOUSE_ENABLE := yes
endif
