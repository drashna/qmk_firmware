// Copyright 2026 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "pmw3610.h"

#include "gpio.h"
#include "pointing_device_internal.h"
#include "wait.h"

#define PMW3610_MSB1 0x80
#define PMW3610_MSB0 0x7F

#define PMW3610_REG_PRODUCT_ID         0x00
#define PMW3610_REG_INVERSE_PRODUCT_ID 0x3F
#define PMW3610_REG_MOTION             0x02
#define PMW3610_REG_DELTA_X            0x03
#define PMW3610_REG_DELTA_Y            0x04
#define PMW3610_REG_SOFT_RESET         0x06
#define PMW3610_REG_WRITE_PROTECT      0x09
#define PMW3610_REG_CPI_X              0x0D
#define PMW3610_REG_CPI_Y              0x0E

#define PMW3610_T_NCS_SCLK_US          1
#define PMW3610_T_SRAD_US              180
#define PMW3610_T_SCLK_NCS_US          1
#define PMW3610_T_SRR_US               20

const pointing_device_driver_t pmw3610_pointing_device_driver = {
    .init       = pmw3610_init,
    .get_report = pmw3610_get_report,
    .set_cpi    = pmw3610_set_cpi,
    .get_cpi    = pmw3610_get_cpi,
};

static uint16_t pmw3610_cpi = PMW3610_CPI;

static void pmw3610_cs_select(void) {
    gpio_write_pin_low(PMW3610_CS_PIN);
}

static void pmw3610_cs_deselect(void) {
    gpio_write_pin_high(PMW3610_CS_PIN);
}

static uint8_t pmw3610_serial_read(void) {
    gpio_set_pin_input(PMW3610_SDIO_PIN);
    uint8_t byte = 0;

    for (uint8_t i = 0; i < 8; ++i) {
        gpio_write_pin_low(PMW3610_SCLK_PIN);
        wait_us(1);

        gpio_write_pin_high(PMW3610_SCLK_PIN);
        wait_us(1);

        // PMW3610 uses mode-3 style timing; sample SDIO after rising edge.
        byte = (byte << 1) | gpio_read_pin(PMW3610_SDIO_PIN);
    }

    return byte;
}

static void pmw3610_serial_write(uint8_t data) {
    gpio_set_pin_output(PMW3610_SDIO_PIN);

    for (int8_t b = 7; b >= 0; b--) {
        gpio_write_pin_low(PMW3610_SCLK_PIN);

        if (data & (1 << b)) {
            gpio_write_pin_high(PMW3610_SDIO_PIN);
        } else {
            gpio_write_pin_low(PMW3610_SDIO_PIN);
        }

        wait_us(2);

        gpio_write_pin_high(PMW3610_SCLK_PIN);
    }

    wait_us(4);
}

static void pmw3610_write(uint8_t reg_addr, uint8_t data) {
    pmw3610_cs_select();
    wait_us(PMW3610_T_NCS_SCLK_US);

    pmw3610_serial_write(reg_addr | PMW3610_MSB1);
    wait_us(PMW3610_T_SRAD_US);

    pmw3610_serial_write(data);
    wait_us(PMW3610_T_SCLK_NCS_US);

    pmw3610_cs_deselect();
    wait_us(PMW3610_T_SRR_US);
}

static uint8_t pmw3610_read(uint8_t reg_addr) {
    pmw3610_cs_select();
    wait_us(PMW3610_T_NCS_SCLK_US);

    pmw3610_serial_write(reg_addr & PMW3610_MSB0);
    wait_us(PMW3610_T_SRAD_US);

    uint8_t data = pmw3610_serial_read();
    wait_us(PMW3610_T_SCLK_NCS_US);

    pmw3610_cs_deselect();
    wait_us(PMW3610_T_SRR_US);

    return data;
}

bool pmw3610_init(void) {
    gpio_set_pin_output(PMW3610_SCLK_PIN);
    gpio_set_pin_output(PMW3610_SDIO_PIN);
    gpio_set_pin_output(PMW3610_CS_PIN);
    gpio_set_pin_output(PMW3610_NRESET_PIN);

    gpio_write_pin_high(PMW3610_SCLK_PIN);
    gpio_write_pin_high(PMW3610_SDIO_PIN);
    pmw3610_cs_deselect();

    // nRESET is active-low: pulse low, then release high.
    gpio_write_pin_high(PMW3610_NRESET_PIN);
    wait_us(20);
    gpio_write_pin_low(PMW3610_NRESET_PIN);
    wait_ms(1);
    gpio_write_pin_high(PMW3610_NRESET_PIN);
    wait_ms(55);

    // Reboot and let internal calibration settle.
    pmw3610_write(PMW3610_REG_SOFT_RESET, 0x80);
    wait_ms(55);

    if (!pmw3610_check_signature()) {
        pd_dprintf("PMW3610: signature check failed\n");
        return false;
    }

    pmw3610_set_cpi(PMW3610_CPI);

    // Prime motion registers once after init.
    pmw3610_read(PMW3610_REG_MOTION);
    pmw3610_read(PMW3610_REG_DELTA_X);
    pmw3610_read(PMW3610_REG_DELTA_Y);

    return true;
}

report_pmw3610_t pmw3610_read_burst(void) {
    report_pmw3610_t report = {0};

    if ((pmw3610_read(PMW3610_REG_MOTION) & PMW3610_MSB1) == PMW3610_MSB1) {
        report.dx = (int8_t)pmw3610_read(PMW3610_REG_DELTA_X);
        report.dy = (int8_t)pmw3610_read(PMW3610_REG_DELTA_Y);
    }

    return report;
}

void pmw3610_set_cpi(uint16_t cpi) {
    uint8_t cpival = CONSTRAIN((cpi / PMW3610_CPI_STEP), (PMW3610_CPI_MIN / PMW3610_CPI_STEP), (PMW3610_CPI_MAX / PMW3610_CPI_STEP));

    // Typical PMW register lock/unlock sequence around config writes.
    pmw3610_write(PMW3610_REG_WRITE_PROTECT, 0x5A);
    pmw3610_write(PMW3610_REG_CPI_X, cpival);
    pmw3610_write(PMW3610_REG_CPI_Y, cpival);
    pmw3610_write(PMW3610_REG_WRITE_PROTECT, 0x00);

    pmw3610_cpi = (uint16_t)cpival * PMW3610_CPI_STEP;
}

uint16_t pmw3610_get_cpi(void) {
    return pmw3610_cpi;
}

report_mouse_t pmw3610_get_report(report_mouse_t mouse_report) {
    report_pmw3610_t data = pmw3610_read_burst();

    if (data.dx != 0 || data.dy != 0) {
        pd_dprintf("Raw ] X: %d, Y: %d\n", data.dx, data.dy);
        mouse_report.x = (mouse_xy_report_t)data.dx;
        mouse_report.y = (mouse_xy_report_t)data.dy;
    }

    return mouse_report;
}

bool pmw3610_check_signature(void) {
    uint8_t pid  = pmw3610_read(PMW3610_REG_PRODUCT_ID);
    uint8_t ipid = pmw3610_read(PMW3610_REG_INVERSE_PRODUCT_ID);

    pd_dprintf("PMW3610: product id: 0x%02X inverse id: 0x%02X\n", pid, ipid);

#if defined(PMW3610_PRODUCT_ID) && defined(PMW3610_INVERSE_PRODUCT_ID)
    return (pid == PMW3610_PRODUCT_ID && ipid == PMW3610_INVERSE_PRODUCT_ID);
#else
    // If no fixed IDs are configured, at least require sane communication:
    // IDs must not be floating-bus values and inverse must match one's complement.
    return (pid != 0x00 && pid != 0xFF && ipid == (uint8_t)~pid);
#endif
}
