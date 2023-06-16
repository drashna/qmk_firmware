// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define I2C_DRIVER I2CD2
#define I2C1_SDA_PIN B11
#define I2C1_SCL_PIN B10

#define AUDIO_PIN C7
#define AUDIO_PWM_DRIVER PWMD3
#define AUDIO_PWM_CHANNEL 2
#define AUDIO_PWM_PAL_MODE 2

#define SPI_DRIVER          SPID1
#define SPI_SCK_PIN         A5
#define SPI_SCK_PAL_MODE    5
#define SPI_MOSI_PIN        A7
#define SPI_MOSI_PAL_MODE   5
#define SPI_MISO_PIN        A6
#define SPI_MISO_PAL_MODE   5

#define DISPLAY_CS_PIN_ILI9341  C0
#define DISPLAY_DC_PIN_ILI9341  C1
#define DISPLAY_RST_PIN_ILI9341 A0

#define BACKLIGHT_PWM_DRIVER PWMD8
#define BACKLIGHT_PWM_CHANNEL 1
#define BACKLIGHT_PAL_MODE	3
