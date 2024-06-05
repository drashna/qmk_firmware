// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define QMK_WAITING_TEST_BUSY_PIN A15
// #define QMK_WAITING_TEST_YIELD_PIN GP9

#define I2C_DRIVER I2CD2
#define I2C1_SDA_PIN B11
#define I2C1_SCL_PIN B10

#define I2C1_CLOCK_SPEED  400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_16_9

#define BACKLIGHT_PWM_DRIVER PWMD8
#define BACKLIGHT_PWM_CHANNEL 2

#define AUDIO_PIN C6

#define AUDIO_PWM_DRIVER PWMD8
#define AUDIO_PWM_CHANNEL 1
#define AUDIO_PWM_PAL_MODE 3
#define AUDIO_SHUTDOWN_PIN C5
#define AUDIO_INIT_DELAY

#define ENCODERS_PAD_A { C0 }
#define ENCODERS_PAD_B { C1 }

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_MOSI_PIN A7
#define SPI_MISO_PIN A6

/* OLED SPI Pins */
#define OLED_DC_PIN C0
#define OLED_RST_PIN C1
#define OLED_CS_PIN C4

/* Divisor for OLED */
#define OLED_SPI_DIVISOR 4
