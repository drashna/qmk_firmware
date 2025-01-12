ifeq ($(strip $(BOOTLOADER)), tinyuf2)
    MCU_LDSCRIPT = STM32F429xG_tinyuf2
else
    MCU_LDSCRIPT = STM32F429xG
endif
