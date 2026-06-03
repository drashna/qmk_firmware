/* Copyright 2026 Phil Lam (Ploopy Corporation)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "pointing_device.h"
#include "i2c_master.h"

/* We perform online calibration when the input data is small (i.e.
   when the trackpoint is likely to be in the neutral position). */
#ifndef TMAG5273AXIAL_ONLINE_CAL_THRESH
#    define TMAG5273AXIAL_ONLINE_CAL_THRESH 1024
#endif

/* There are four types of TMAG chips, all with different I2C addresses.
   These are listed below for discovery on the bus. */
#define TMAG5273A1_I2C_ADDRESS (0x35 << 1)
#define TMAG5273B1_I2C_ADDRESS (0x22 << 1)
#define TMAG5273C1_I2C_ADDRESS (0x78 << 1)
#define TMAG5273D1_I2C_ADDRESS (0x44 << 1)

/* Once we find a TMAG chip on the bus, we give it a fixed address to
   simplify the code. */
#define TMAG5273_AXIAL_I2C_ADDRESS (0x60 << 1)

#define TMAG5273_MAX_SENSOR_VALUE 5760

#define REG_DEVICE_CONFIG_1         0x00
#define REG_DEVICE_CONFIG_2         0x01
#define REG_SENSOR_CONFIG_1         0x02
#define REG_SENSOR_CONFIG_2         0x03
#define REG_X_THR_CONFIG            0x04
#define REG_Y_THR_CONFIG            0x05
#define REG_Z_THR_CONFIG            0x06
#define REG_T_CONFIG                0x07
#define REG_INT_CONFIG_1            0x08
#define REG_MAG_GAIN_CONFIG         0x09
#define REG_MAG_OFFSET_CONFIG_1     0x0A
#define REG_MAG_OFFSET_CONFIG_2     0x0B
#define REG_I2C_ADDRESS             0x0C
#define REG_DEVICE_ID               0x0D
#define REG_MANUFACTURER_ID_LSB     0x0E
#define REG_MANUFACTURER_ID_MSB     0x0F
#define REG_T_MSB_RESULT            0x10
#define REG_T_LSB_RESULT            0x11
#define REG_X_MSB_RESULT            0x12
#define REG_X_LSB_RESULT            0x13
#define REG_Y_MSB_RESULT            0x14
#define REG_Y_LSB_RESULT            0x15
#define REG_Z_MSB_RESULT            0x16
#define REG_Z_LSB_RESULT            0x17
#define REG_CONV_STATUS             0x18
#define REG_ANGLE_RESULT_MSB        0x19
#define REG_ANGLE_RESULT_LSB        0x1A
#define REG_MAGNITUDE_RESULT        0x1B
#define REG_DEVICE_STATUS           0x1C

typedef struct {
    int16_t dx;
    int16_t dy;
} report_tmag5273axial_t;

report_tmag5273axial_t  tmag5273axial_read_burst(void);
bool                    tmag5273axial_check_signature(void);
