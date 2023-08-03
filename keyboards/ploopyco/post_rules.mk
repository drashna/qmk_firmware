VALID_OPT_ENCODER_TYPES := default simple tiny custom
OPTICAL_ENCODER_DRIVER ?= default

ifeq ($(strip $(ENCODER_ENABLE)), yes)
    ifneq ($(strip $(OPTICAL_ENCODER_DRIVER)), custom)
        ifeq ($(filter $(OPTICAL_ENCODER_DRIVER),$(VALID_OPT_ENCODER_TYPES)),)
            $(call CATASTROPHIC_ERROR,Invalid OPTICAL_ENCODER_DRIVER,OPTICAL_ENCODER_DRIVER="$(OPTICAL_ENCODER_DRIVER)" is not a valid optical encoder type)
        endif
        QUANTUM_LIB_SRC += analog.c
        SRC += opt_encoder_$(strip $(OPTICAL_ENCODER_DRIVER)).c
    endif
endif
