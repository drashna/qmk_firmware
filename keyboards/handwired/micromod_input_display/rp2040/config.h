// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP4
#define I2C1_SCL_PIN GP5

#define AUDIO_PIN GP24
#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_A

#define SPI_DRIVER          SPID0
#define SPI_SCK_PIN         GP22
#define SPI_MOSI_PIN        GP23
#define SPI_MISO_PIN        GP20

#define DISPLAY_CS_PIN_ILI9341      GP6
#define DISPLAY_DC_PIN_ILI9341      GP7
#define DISPLAY_RST_PIN_ILI9341     GP18

#define BACKLIGHT_PWM_DRIVER PWMD6
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_B

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
#define "SERIAL_NUMBER" "MICROMOD_INPUT_DISPLAY"

#define APA102_NOPS (100 / (1000000000L / (CPU_CLOCK / 4)))
