// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "i2c_master.h"
#include "rtc/rtc.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief I2C definition
 */
#define DS1307_I2C_ADDRESS 0x68

#ifndef DS1307_I2C_TIMEOUT
#    define DS1307_I2C_TIMEOUT 10
#endif

/**
 * @brief register definition
 */
#define DS1307_TIME_REG 0x00
#define DS1307_CONTROL_REG 0x07
#define DS1307_NVRAM_REG 0x08

/**
 * @brief Functions Prototypes
 */
bool  ds1307_init(rtc_time_t *time);
bool  ds1307_task(rtc_time_t *time);
char *ds1307_read_temp_imperial_str(void);
char *ds1307_read_temp_str(void);
float ds1307_get_temperature(void);
bool  ds1307_has_lost_power(void);

i2c_status_t ds1307_set_time(rtc_time_t t);
i2c_status_t ds1307_get_time(rtc_time_t *t);

i2c_status_t ds1307_read_nvram(uint8_t address, uint8_t *data, uint16_t len);
i2c_status_t ds1307_write_nvram(uint8_t address, uint8_t *data, uint16_t len);
