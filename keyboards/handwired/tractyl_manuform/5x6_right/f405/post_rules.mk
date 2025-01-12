ifeq ($(strip $(USE_USB_OTG_HS_PORT)), yes)
    OPT_DEFS += -DUSE_USB_OTG_HS_PORT
endif
