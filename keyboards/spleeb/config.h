// Copyright 2022 Chris Hoage (@chrishoage)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Transport dpi and enc mode for display on oled
#define SPLIT_TRANSACTION_IDS_KB RPC_ID_KB_CONFIG_SYNC

#ifdef POINTING_DEVICE_ENABLE
#    define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// Absolute mode allows for z/touchdown triggering of auto mouse layer with out
// moving finger
#    define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#    define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
#endif // POINTING_DEVICE_ENABLE

#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP16
#define I2C1_SCL_PIN GP17

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define OLED_FONT_H "./lib/glcdfont.c"
#endif // OLED_ENABLE

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
