// Copyright 2025 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 22

#define USER_BUTTON_PIN     A15
#define DEBUG_LED_PIN       C13

#define BACKLIGHT_PWM_DRIVER     PWMD3
#define BACKLIGHT_PWM_CHANNEL    2
#define BACKLIGHT_PAL_MODE       2

/* spi config for eeprom and pmw3360 sensor */
#define SPI_DRIVER         SPID1
#define SPI_SCK_PIN        A5
#define SPI_SCK_PAL_MODE   5
#define SPI_MOSI_PIN       A7
#define SPI_MOSI_PAL_MODE  5
#define SPI_MISO_PIN       A6
#define SPI_MISO_PAL_MODE  5

#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN A8
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR    2
#define EXTERNAL_FLASH_SIZE                 (8 * 1024 * 1024)

// lcd
#define DISPLAY_RST_PIN NO_PIN
#define DISPLAY_DC_PIN B12
#define DISPLAY_CS_PIN B9
#define DISPLAY_SPI_DIVIDER 1
