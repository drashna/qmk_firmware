# Enter lower-power sleep mode when on the ChibiOS idle thread
NO_STARTUP_USB_CHECK = yes
OPT_DEFS += -DENABLE_FACTORY_TEST

include keyboards/keychron/bluetooth/bluetooth.mk

DEFAULT_FOLDER = keychron/q3_pro/ansi_encoder
