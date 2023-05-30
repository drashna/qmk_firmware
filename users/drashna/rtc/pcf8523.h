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
#define PCF8523_I2C_ADDRESS 0x68

#ifndef PCF8523_I2C_TIMEOUT
#    define PCF8523_I2C_TIMEOUT 10
#endif

typedef enum {
  PCF8523_TwoHours = 0x00, /**< Offset made every two hours */
  PCF8523_OneMinute = 0x80 /**< Offset made every minute */
} pcf8523_offset_mode_t;


/**
 * @brief Chip register definition
 */
#define PCF8523_CONTROL_1_REG 0x00     // Control and status register 1
#define PCF8523_CONTROL_2_REG 0x01     // Control and status register 2
#define PCF8523_CONTROL_3_REG 0x02     // Control and status register 3
#define PCF8523_TIME_REG 0x03          // Date/Time Register
#define PCF8523_STATUS_REG 0x03        // Status register
#define PCF8523_OFFSET_REG 0x0E        // Offset register
#define PCF8523_CLKOUTCONTROL 0x0F     // Timer and CLKOUT control register
#define PCF8523_TIMER_B_FRCTL_REG 0x12 // Timer B source clock frequency control
#define PCF8523_TIMER_B_VALUE_REG 0x13 // Timer B value (number clock periods)

/**
 * @brief Functions Prototypes
 */
bool  pcf8523_init(rtc_time_t *time);
bool  pcf8523_task(rtc_time_t *time);
bool  pcf8523_has_lost_power(void);

i2c_status_t pcf8523_set_time(rtc_time_t t);
i2c_status_t pcf8523_get_time(rtc_time_t *t);
i2c_status_t pcf8523_calibate(pcf8523_offset_mode_t mode, int8_t offset);
