# Enter lower-power sleep mode when on the ChibiOS idle thread
OPT_DEFS += -DNO_USB_STARTUP_CHECK -DENABLE_FACTORY_TEST

include keyboards/keychron/bluetooth/bluetooth.mk
include keyboards/keychron/common/common.mk
