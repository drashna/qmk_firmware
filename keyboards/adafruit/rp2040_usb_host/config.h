#pragma once

#pragma weak backing_store_lock
#pragma weak backing_store_unlock

#ifdef CRT0_EXTRA_CORES_NUMBER
#    undef CRT0_EXTRA_CORES_NUMBER
#endif
#define CRT0_EXTRA_CORES_NUMBER 1

/* Double tap reset button to enter bootloader */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP13
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 750U
