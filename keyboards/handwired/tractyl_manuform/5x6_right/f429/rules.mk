# Cortex version
MCU = cortex-m4

# ARM version, CORTEX-M0/M1 are 6, CORTEX-M3/M4/M7 are 7
ARMV = 7

## chip/board settings
# - the next two should match the directories in
#   <chibios[-contrib]>/os/hal/ports/$(MCU_PORT_NAME)/$(MCU_SERIES)
#   OR
#   <chibios[-contrib]>/os/hal/ports/$(MCU_FAMILY)/$(MCU_SERIES)
MCU_FAMILY = STM32
MCU_SERIES = STM32F4xx

# Linker script to use
# - it should exist either in <chibios>/os/common/startup/ARMCMx/compilers/GCC/ld/
#   or <keyboard_dir>/ld/
MCU_LDSCRIPT ?= STM32F429xG

# Startup code to use
#  - it should exist in <chibios>/os/common/startup/ARMCMx/compilers/GCC/mk/
MCU_STARTUP ?= stm32f4xx

# Board: it should exist either in <chibios>/os/hal/boards/,
# <keyboard_dir>/boards/, or drivers/boards/
BOARD ?= ST_NUCLEO144_F429ZI

USE_FPU ?= yes

# UF2 settings
UF2_FAMILY ?= STM32F4

# Bootloader address for STM32 DFU
STM32_BOOTLOADER_ADDRESS ?= 0x1FFF0000

# SRC += $(CHIBIOS_CONTRIB)/os/various/bitmap.c
