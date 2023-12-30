// Copyright 2023 Drashna Jael're (@Drashna Jael're)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define I2C1_CLOCK_SPEED  400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_16_9

#define OLED_DISPLAY_128X128
#define OLED_UPDATE_INTERVAL 100

#define DRV2605L_FB_ERM_LRA   0
#define DRV2605L_GREETING     DRV2605L_EFFECT_750_MS_ALERT_100
#define DRV2605L_DEFAULT_MODE DRV2605L_EFFECT_BUZZ_1_100

/* spi config for eeprom and pmw3360 sensor */
#define SPI_DRIVER        SPID1
#define SPI_SCK_PIN       B3
#define SPI_SCK_PAL_MODE  5
#define SPI_MOSI_PIN      B5
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN      B4
#define SPI_MISO_PAL_MODE 5

#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN A15
#define EXTERNAL_FLASH_SPI_CLOCK_DIVISOR    32 // 16 or less doesn't work right
#define EXTERNAL_FLASH_SIZE                 (2 * 1024 * 1024)
