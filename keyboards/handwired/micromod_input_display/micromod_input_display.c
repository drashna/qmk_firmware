// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdint.h>
#include "quantum.h"
#include "i2c_master.h"

#define BUTTON_I2C_ADDRESS 0x71
#ifndef BUTTON_I2C_TIMEOUT
#define BUTTON_I2C_TIMEOUT 100
#endif

#define BUTTON_ID                0x00
#define BUTTON_VERSION1          0x01
#define BUTTON_VERSION2          0x02
#define BUTTON_PRESSED           0x03
#define BUTTON_CLICKED           0x04
#define BUTTON_INTERRUPT         0x05
#define BUTTON_DEBOUNCE          0x06
#define BUTTON_CHANGE_ADDREESS   0x1F


static bool is_connected = false;

void matrix_init_custom(void) {
    i2c_init();
    uint8_t data = 0;
    i2c_status_t status = i2c_readReg(BUTTON_I2C_ADDRESS << 1, 0, &data, 1, BUTTON_I2C_TIMEOUT);
    is_connected = (status == I2C_STATUS_SUCCESS);
}

uint8_t button_get_pressed(void) {
    uint8_t data = 0;
    i2c_readReg(BUTTON_I2C_ADDRESS << 1, BUTTON_PRESSED, &data, 1, BUTTON_I2C_TIMEOUT);
    return data;
}

uint8_t button_get_clicked(void) {
    uint8_t data = 0;
    i2c_readReg(BUTTON_I2C_ADDRESS << 1, BUTTON_CLICKED, &data, 1, BUTTON_I2C_TIMEOUT);
    return data;
}

uint16_t button_get_debounce(void) {
    uint8_t data[2] = {0};
    i2c_readReg(BUTTON_I2C_ADDRESS << 1, BUTTON_DEBOUNCE, data, 2, BUTTON_I2C_TIMEOUT);
    return (data[0] << 8) | data[1];
}

bool button_get_pressed_interrupt(void) {
    uint8_t data = 0;
    i2c_status_t status = i2c_readReg(BUTTON_I2C_ADDRESS << 1, BUTTON_INTERRUPT, &data, 1, BUTTON_I2C_TIMEOUT);
    return (status == I2C_STATUS_SUCCESS) && ((data & (1 << 1)) >> 1);
}

bool button_get_clicked_interrupt(void) {
    uint8_t data = 0;
    i2c_status_t status = i2c_readReg(BUTTON_I2C_ADDRESS << 1, BUTTON_INTERRUPT, &data, 1, BUTTON_I2C_TIMEOUT);
    return (status == I2C_STATUS_SUCCESS) && ((data & (1 << 0)) >> 0);
}


bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    if (!is_connected) {
        return false;
    }

    uint8_t pressed = button_get_pressed();
    if (pressed) {
        current_matrix[0] |= pressed;
        matrix_has_changed = true;
        wait_us(200);
    }

    uint8_t clicked = button_get_clicked();
    if (clicked) {
        current_matrix[0] &= ~(clicked);
        matrix_has_changed = true;
        wait_us(10);
    }

    return matrix_has_changed;
}
