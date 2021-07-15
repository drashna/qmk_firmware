SYSTEM_TYPE := $(shell gcc -dumpmachine)

CC = gcc
OBJCOPY =
OBJDUMP =
SIZE =
AR =
NM =
HEX =
EEP =
BIN =


COMPILEFLAGS += -funsigned-char
ifeq ($(findstring apple, ${SYSTEM_TYPE}),)
COMPILEFLAGS += -funsigned-bitfields
endif
COMPILEFLAGS += -ffunction-sections
COMPILEFLAGS += -fdata-sections
COMPILEFLAGS += -fshort-enums
ifneq ($(findstring mingw, ${SYSTEM_TYPE}),)
COMPILEFLAGS += -mno-ms-bitfields
endif

CFLAGS += $(COMPILEFLAGS)
ifeq ($(findstring apple, ${SYSTEM_TYPE}),)
CFLAGS += -fno-inline-small-functions
endif
CFLAGS += -fno-strict-aliasing

CXXFLAGS += $(COMPILEFLAGS)
CXXFLAGS += -fno-exceptions
CXXFLAGS += -std=gnu++11
