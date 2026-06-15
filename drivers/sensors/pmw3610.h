// Copyright 2026 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "pointing_device.h"

#ifndef PMW3610_CS_PIN
#    ifdef POINTING_DEVICE_CS_PIN
#        define PMW3610_CS_PIN POINTING_DEVICE_CS_PIN
#    else
#        error "No chip select pin defined -- missing POINTING_DEVICE_CS_PIN or PMW3610_CS_PIN define"
#    endif
#endif

#ifndef PMW3610_SCLK_PIN
#    ifdef POINTING_DEVICE_SCLK_PIN
#        define PMW3610_SCLK_PIN POINTING_DEVICE_SCLK_PIN
#    else
#        error "No clock pin defined -- missing POINTING_DEVICE_SCLK_PIN or PMW3610_SCLK_PIN"
#    endif
#endif

#ifndef PMW3610_SDIO_PIN
#    ifdef POINTING_DEVICE_SDIO_PIN
#        define PMW3610_SDIO_PIN POINTING_DEVICE_SDIO_PIN
#    else
#        error "No data pin defined -- missing POINTING_DEVICE_SDIO_PIN or PMW3610_SDIO_PIN"
#    endif
#endif

#ifndef PMW3610_NRESET_PIN
#    error "No nRESET pin defined -- missing PMW3610_NRESET_PIN"
#endif

#if !defined(PMW3610_CPI)
#    define PMW3610_CPI 1600
#endif

#define PMW3610_CPI_MIN 200
#define PMW3610_CPI_MAX 3200
#define PMW3610_CPI_STEP 200

#define CONSTRAIN(amt, low, high) ((amt) < (low) ? (low) : ((amt) > (high) ? (high) : (amt)))

typedef struct {
    int8_t dx;
    int8_t dy;
} report_pmw3610_t;

extern const pointing_device_driver_t pmw3610_pointing_device_driver;

bool             pmw3610_init(void);
report_pmw3610_t pmw3610_read_burst(void);
void             pmw3610_set_cpi(uint16_t cpi);
uint16_t         pmw3610_get_cpi(void);
report_mouse_t   pmw3610_get_report(report_mouse_t mouse_report);
bool             pmw3610_check_signature(void);
