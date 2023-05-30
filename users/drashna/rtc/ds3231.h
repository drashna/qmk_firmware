// Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#define DS3231_I2C_ADDRESS 0x68

#ifndef DS3231_I2C_TIMEOUT
#    define DS3231_I2C_TIMEOUT 10
#endif

/**
 * @brief register definition
 */
#define DS3231_TIME_REG 0x00
#define DS3231_ALARM1_REG 0x07
#define DS3231_ALARM2_REG 0x0B
#define DS3231_CONTROL_REG 0x0E
#define DS3231_STATUS_REG 0x0F
#define DS3231_AGING_OFFSET_REG 0x10
#define DS3231_TEMPERATURE_REG 0x11

/**
 * @brief Functions Prototypes
 */
bool   ds3231_init(rtc_time_t *time);
bool   ds3231_task(rtc_time_t *time);
char  *ds3231_read_temp_imperial_str(void);
char  *ds3231_read_temp_str(void);
float  ds3231_get_temperature(void);
float  ds3231_read_temp(void);
bool   ds3231_has_lost_power(void);
int8_t ds3231_get_aging_offset(void);
void   ds3231_set_aging_offset(int8_t offset);

i2c_status_t ds3231_set_time(rtc_time_t t);
i2c_status_t ds3231_get_time(rtc_time_t *t);
