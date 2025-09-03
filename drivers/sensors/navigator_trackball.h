// Copyright 2025 ZSA Technology Labs, Inc <contact@zsa.io>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "pointing_device.h"

#ifndef NAVIGATOR_TRACKBALL_ADDRESS
#    define NAVIGATOR_TRACKBALL_ADDRESS 0x50
#endif

#ifndef NAVIGATOR_TRACKBALL_TIMEOUT
#    define NAVIGATOR_TRACKBALL_TIMEOUT 100
#endif

#define NAVIGATOR_TRACKBALL_READ 7
#define NAVIGATOR_TRACKBALL_PROBE 1000

#define NCS_PIN 0x01
#define PAW3805EK_ID 0x31

#define SCI18IS606_CONF 0xDC //00001110b // MSB first, Mode 3, 155kHz

#define SCI18IS606_RW_SPI 0x00
#define SCI18IS606_CONF_SPI 0xF0
#define SCI18IS606_CLR_INT 0xF1
#define SCI18IS606_GET_ID 0xFE

#define WRITE_REG_BIT 0x80
/*
The PAW3805EK datasheet suggests the following CPI values for the X and Y axes:
CPI    X-axis  Y-axis
800    0x1F    0x22
1000   0x26    0x2A
1200   0x2E    0x32
1600   0x3C    0x43
2000   0x4C    0x54
2400   0x5B    0x64
3000   0x70    0x7B
*/
#define CPI_TICKS 7
#define DEFAULT_CPI_TICK 1
#define CPI_X_800  0x1F
#define CPI_Y_800  0x22
#define CPI_X_1000 0x26
#define CPI_Y_1000 0x2A
#define CPI_X_1200 0x2E
#define CPI_Y_1200 0x32
#define CPI_X_1600 0x3C
#define CPI_Y_1600 0x43
#define CPI_X_2000 0x4C
#define CPI_Y_2000 0x54
#define CPI_X_2400 0x5B
#define CPI_Y_2400 0x64
#define CPI_X_3000 0x70
#define CPI_Y_3000 0x7B

typedef struct {
    uint8_t reg;
    uint8_t data;
} paw3805ek_reg_seq_t;

const pointing_device_driver_t navigator_trackball_pointing_device_driver;

void           navigator_trackball_device_init(void);
report_mouse_t navigator_trackball_get_report(report_mouse_t mouse_report);
uint16_t       navigator_trackball_get_cpi(void);
void           navigator_trackball_set_cpi(uint16_t cpi);
void           restore_cpi(uint8_t cpi);
