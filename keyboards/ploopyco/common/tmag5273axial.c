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

#include "tmag5273axial.h"
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include "wait.h"
#include "pointing_device_internal.h"
#include "print.h"

// Virtual CPI variable, since the device itself doesn't have one.
uint16_t tmag5273axial_cpi = 1024;

// The driver tracks sensor zero point drift during usage.
int16_t x_zeropoint_calibration = 0;
int16_t y_zeropoint_calibration = 0;

int16_t x_zeropoint_online_calibration = 0;
int16_t y_zeropoint_online_calibration = 0;

bool pointing_device_driver_init(void) {
    i2c_init();

    uint16_t addr;

    if (i2c_ping_address(TMAG5273A1_I2C_ADDRESS, 100) == I2C_STATUS_SUCCESS) {
        addr = TMAG5273A1_I2C_ADDRESS;
    } else if (i2c_ping_address(TMAG5273B1_I2C_ADDRESS, 100) == I2C_STATUS_SUCCESS) {
        addr = TMAG5273B1_I2C_ADDRESS;
    } else if (i2c_ping_address(TMAG5273C1_I2C_ADDRESS, 100) == I2C_STATUS_SUCCESS) {
        addr = TMAG5273C1_I2C_ADDRESS;
    } else if (i2c_ping_address(TMAG5273D1_I2C_ADDRESS, 100) == I2C_STATUS_SUCCESS) {
        addr = TMAG5273D1_I2C_ADDRESS;
    } else {
        // printf("No TMAG5273 device found; exiting\n");
        return false;
    }

    // Give found device the new device address
    uint8_t i2c_address = TMAG5273_AXIAL_I2C_ADDRESS | 0x1;
    i2c_write_register(addr, REG_I2C_ADDRESS, &i2c_address, 1, 100);

    uint8_t device_config_1 = 0;
    // 8x oversampling, 1.6ksps data rate
    device_config_1 |= 0b011 << 2;

    // Low noise mode
    // Operating Mode: Continuous Measure Mode
    uint8_t device_config_2 = (0b1 << 4) | (0b10);

    // X and Y channel enabled
    uint8_t sensor_config_1 = 0x30;

    // Enable X and Y angle calculation
    // X and Y magnetic ranges at +-80mT
    uint8_t sensor_config_2 = (0x1 << 2) | (0b10);

    uint8_t int_config = 0x1;

    i2c_write_register(i2c_address, REG_DEVICE_CONFIG_1, &device_config_1, 1, 100);
    i2c_write_register(i2c_address, REG_DEVICE_CONFIG_2, &device_config_2, 1, 100);
    i2c_write_register(i2c_address, REG_SENSOR_CONFIG_1, &sensor_config_1, 1, 100);
    i2c_write_register(i2c_address, REG_SENSOR_CONFIG_2, &sensor_config_2, 1, 100);
    i2c_write_register(i2c_address, REG_INT_CONFIG_1, &int_config, 1, 100);

    /* Get a baseline reading for zero calibration. */
    int32_t zero_calibration_accumulator_x = 0;
    int32_t zero_calibration_accumulator_y = 0;


    uint8_t raw_xy_data[4];
    int16_t x_data = 0;
    int16_t y_data = 0;

    for( int i = 0; i < 256; i++ ) {
        i2c_read_register(TMAG5273_AXIAL_I2C_ADDRESS, REG_X_MSB_RESULT, raw_xy_data, 4, 100);
        x_data = raw_xy_data[1] + (raw_xy_data[0] << 8);
        y_data = raw_xy_data[3] + (raw_xy_data[2] << 8);

        zero_calibration_accumulator_x += x_data;
        zero_calibration_accumulator_y += y_data;

        wait_ms(1);
    }

    x_zeropoint_calibration = zero_calibration_accumulator_x / 256;
    y_zeropoint_calibration = zero_calibration_accumulator_y / 256;

    return true;
}

void pointing_device_driver_set_cpi(uint16_t cpi) {
    tmag5273axial_cpi = cpi;
}

uint16_t pointing_device_driver_get_cpi(void) {
    return tmag5273axial_cpi;
}

report_tmag5273axial_t tmag5273axial_read(void) {
    report_tmag5273axial_t report = {0};

    uint8_t raw_xy_data[4];
    i2c_read_register(TMAG5273_AXIAL_I2C_ADDRESS, REG_X_MSB_RESULT, raw_xy_data, 4, 100);
    int16_t raw_x_data16 = raw_xy_data[1] + (raw_xy_data[0] << 8);
    int16_t raw_y_data16 = raw_xy_data[3] + (raw_xy_data[2] << 8);

    // Online calibration drift adjustment if trackpoint is near neutral position
    if( raw_x_data16 < (x_zeropoint_calibration + TMAG5273AXIAL_ONLINE_CAL_THRESH) &&
        raw_x_data16 > (x_zeropoint_calibration - TMAG5273AXIAL_ONLINE_CAL_THRESH) &&
        raw_y_data16 < (y_zeropoint_calibration + TMAG5273AXIAL_ONLINE_CAL_THRESH) &&
        raw_y_data16 > (y_zeropoint_calibration - TMAG5273AXIAL_ONLINE_CAL_THRESH) ) {

        // X Axis
        if( raw_x_data16 > (x_zeropoint_calibration + x_zeropoint_online_calibration) ) {
            x_zeropoint_online_calibration += 1;
        }
        else {
            x_zeropoint_online_calibration -= 1;
        }

        // Cap online calibration so it doesn't run away.
        if( x_zeropoint_online_calibration > TMAG5273AXIAL_ONLINE_CAL_THRESH ) {
            x_zeropoint_online_calibration = TMAG5273AXIAL_ONLINE_CAL_THRESH;
        }
        if( x_zeropoint_online_calibration < -TMAG5273AXIAL_ONLINE_CAL_THRESH ) {
            x_zeropoint_online_calibration = -TMAG5273AXIAL_ONLINE_CAL_THRESH;
        }

        // Y Axis
        if( raw_y_data16 > (y_zeropoint_calibration + y_zeropoint_online_calibration) ) {
            y_zeropoint_online_calibration += 1;
        }
        else {
            y_zeropoint_online_calibration -= 1;
        }

        // Cap online calibration so it doesn't run away.
        if( y_zeropoint_online_calibration > TMAG5273AXIAL_ONLINE_CAL_THRESH ) {
            y_zeropoint_online_calibration = TMAG5273AXIAL_ONLINE_CAL_THRESH;
        }
        if( y_zeropoint_online_calibration < -TMAG5273AXIAL_ONLINE_CAL_THRESH ) {
            y_zeropoint_online_calibration = -TMAG5273AXIAL_ONLINE_CAL_THRESH;
        }

        return report;
    }

    // Scale by configured CPI so the user has some control over the speed.
    static int16_t carry_x = 0;
    static int16_t carry_y = 0;
    int32_t x = raw_x_data16 - x_zeropoint_calibration - x_zeropoint_online_calibration + carry_x;
    int32_t y = raw_y_data16 - y_zeropoint_calibration - y_zeropoint_online_calibration + carry_y;

    report.dx = x / tmag5273axial_cpi;
    report.dy = y / tmag5273axial_cpi;
    carry_x = x % tmag5273axial_cpi;
    carry_y = y % tmag5273axial_cpi;

    // For debugging.
    //printf("x(r/c/a): %d %ld %d %d\n", raw_x_data16, x, report.dx, tmag5273axial_cpi);
    //printf("y(r/c/a): %d %ld %d\n", raw_y_data16, y, report.dy);

    return report;
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
    report_tmag5273axial_t data = tmag5273axial_read();

    if (data.dx != 0 || data.dy != 0) {
        mouse_report.x = CONSTRAIN_HID_XY(data.dx);
        mouse_report.y = CONSTRAIN_HID_XY(data.dy);
    }

    return mouse_report;
}
