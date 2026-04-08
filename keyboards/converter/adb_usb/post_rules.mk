
ifeq ($(strip $(ADB_MOUSE_ENABLE)), yes)
    OPT_DEFS += -DADB_MOUSE_ENABLE
    POINTING_DEVICE_ENABLE = yes
    POINTING_DEVICE_DRIVER = custom
endif
