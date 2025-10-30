ifeq ($(strip $(BOOTLOADER)), tinyuf2)
    MCU_LDSCRIPT = STM32F429xG_tinyuf2
else
    MCU_LDSCRIPT = STM32F429xG
endif

ifeq ($(strip $(COMMUNITY_SDRAM_ENABLE)),yes)
    OPT_DEFS += -DHAL_USE_SDRAM=TRUE -DHAL_USE_FSMC=TRUE
    SRC += keyboards/handwired/tractyl_manuform/5x6_right/f429_rando/community_sdram.c
else
    ifeq ($(strip $(TZARC_SDRAM_ENABLE)),yes)
        OPT_DEFS += -DTZARC_SDRAM_ENABLE
        SRC += keyboards/handwired/tractyl_manuform/5x6_right/f429_rando/tzarc_sdram.c
    endif
endif
