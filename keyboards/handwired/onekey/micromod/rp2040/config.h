// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define QMK_WAITING_TEST_BUSY_PIN GP25
// #define QMK_WAITING_TEST_YIELD_PIN GP9

#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP4
#define I2C1_SCL_PIN GP5
#define I2C1_CLOCK_SPEED  400000

#define BACKLIGHT_PWM_DRIVER PWMD4
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A

#define AUDIO_PIN GP13
#define AUDIO_PWM_DRIVER PWMD6
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define AUDIO_SHUTDOWN_PIN GP26
#define AUDIO_INIT_DELAY

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 750U

#define ENCODERS_PAD_A { GP6 }
#define ENCODERS_PAD_B { GP7 }


#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP22
#define SPI_MOSI_PIN GP23
#define SPI_MISO_PIN GP20

/* OLED SPI Pins */
#define OLED_DC_PIN GP7  // D1
#define OLED_RST_PIN GP6 // D0
#define OLED_CS_PIN GP21 // SPI_CS

#define DISPLAY_DC_PIN GP6 // D0
#define DISPLAY_RST_PIN GP7 // D1
#define DISPLAY_CS_PIN GP21
#define DISPLAY_SPI_DIVIDER 16

/* Divisor for OLED */
#define OLED_SPI_DIVISOR 4
#define OLED_UPDATE_INTERVAL 1
