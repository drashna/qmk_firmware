// Copyright 2025 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "pointing_device.h"
#include "keyboard.h"

#ifndef PAW3395_CS_PIN
#    ifdef POINTING_DEVICE_CS_PIN
#        define PAW3395_CS_PIN POINTING_DEVICE_CS_PIN
#    else
#        error "No clock pin defined -- missing POINTING_DEVICE_CS_PIN or PAW3395_CS_PIN"
#    endif
#endif
#ifndef PAW3395_CLOCK_SPEED
#    define PAW3395_CLOCK_SPEED 10000000
#endif

#ifndef PAW3395_SPI_LSBFIRST
#    define PAW3395_SPI_LSBFIRST false
#endif

#ifndef PAW3395_SPI_MODE
#    define PAW3395_SPI_MODE 3
#endif

#ifndef PAW3395_SPI_DIVISOR
#    ifdef __AVR__
#        define PAW3395_SPI_DIVISOR (F_CPU / PAW3395_CLOCK_SPEED)
#    else
#        define PAW3395_SPI_DIVISOR 64
#    endif
#endif

#if !defined(PAW3395_LIFT_CONFIG)
#    define PAW3395_LIFT_CONFIG 0x00
#endif

#if !defined(ROTATIONAL_TRANSFORM_ANGLE)
#    define ROTATIONAL_TRANSFORM_ANGLE 0x00
#endif

#if ROTATIONAL_TRANSFORM_ANGLE > 127 || ROTATIONAL_TRANSFORM_ANGLE < (-127)
#    error ROTATIONAL_TRANSFORM_ANGLE has to be in the range of +/- 127 for all PMW33XX sensors.
#endif

#if !defined(PAW3395_CPI)
#    define PAW3395_CPI 5000U
#endif

typedef struct __attribute__((packed)) {
    union {
        struct {
            uint8_t operation_mode : 2;
            uint8_t _reserved1 : 1;
            bool    is_lifted : 1;
            uint8_t _reserved2 : 3;
            bool    is_motion : 1;
        } b;
        uint8_t w;
    } motion;
    uint8_t observation;
    int16_t delta_x;
    int16_t delta_y;
    uint8_t squal;
    uint8_t pixel_sum;
    uint8_t maximum_pixel;
    uint8_t minimum_pixel;
    uint8_t shutter_upper;
    uint8_t shutter_lower;
} paw3395_report_t;

_Static_assert(sizeof(paw3395_report_t) == 12, "pmw33xx_report_t must be 6 bytes in size");
_Static_assert(sizeof((paw3395_report_t){0}.motion) == 1, "pmw33xx_report_t.motion must be 1 byte in size");

const pointing_device_driver_t paw3395_pointing_device_driver;

void             paw3395_init(void);
void             paw3395_shutdown(void);
uint8_t          paw3395_read_register(uint8_t reg_addr);
bool             paw3395_write_register(uint8_t reg_addr, uint8_t data);
void             paw3395_set_mode(uint8_t mode);
uint16_t         paw3395_get_cpi(void);
void             paw3395_set_cpi(uint16_t cpi);
paw3395_report_t paw3395_read_burst(void);
report_mouse_t   paw3395_get_report(report_mouse_t mouse_report);
