
# project specific files
SRC += matrix.c
I2C_DRIVER_REQUIRED = yes

MOUSE_SHARED_EP = no

ifeq ($(RGBLIGHT_ENABLE),yes)
    RGBLIGHT_DRIVER = custom
    WS2812_DRIVER_REQUIRED = yes
    SRC += rgblight_custom.c
endif
