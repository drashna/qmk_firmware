CUSTOM_QUANTUM_PAINTER_ENABLE ?= yes

ifeq ($(strip $(CUSTOM_QUANTUM_PAINTER_ENABLE)), yes)
    DEFERRED_EXEC_ENABLE = yes
    OPT_DEFS += -DCUSTOM_QUANTUM_PAINTER_ENABLE

    ifeq ($(strip $(QUANTUM_PAINTER_DRIVERS)),ili9341_spi)
        OPT_DEFS += -DCUSTOM_QUANTUM_PAINTER_ILI9341
        SRC += $(USER_PATH)/painter/ili9341_display.c
    endif

    SRC += $(USER_PATH)/painter/fonts.qff.c \
        $(USER_PATH)/painter/graphics.qgf.c

endif
