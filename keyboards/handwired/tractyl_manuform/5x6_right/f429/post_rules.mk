ifeq ($(strip $(BOOTLOADER)), tinyuf2)
    MCU_LDSCRIPT = STM32F429xG_tinyuf2
endif

ifeq ($(strip $(USE_USB_OTG_HS_PORT)), yes)
    OPT_DEFS += -DUSE_USB_OTG_HS_PORT
endif
