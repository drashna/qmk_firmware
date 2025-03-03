// Copyright 2025 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "paw3395.h"
#include "pointing_device_internal.h"
#include "progmem.h"
#include "spi_master.h"
#include "wait.h"

// clang-format off
#define PAW3395_REGISTER_PRODUCT_ID          0x00
#define PAW3395_REGISTER_REVISION_ID         0x01
#define PAW3395_REGISTER_MOTION              0x02
#define PAW3395_REGISTER_DELTA_X_L           0x03
#define PAW3395_REGISTER_DELTA_X_H           0x04
#define PAW3395_REGISTER_DELTA_Y_L           0x05
#define PAW3395_REGISTER_DELTA_Y_H           0x06
#define PAW3395_REGISTER_SQUAL               0x07
#define PAW3395_REGISTER_PIXEL_SUM           0x08
#define PAW3395_REGISTER_MAXIMUM_PIXEL       0x09
#define PAW3395_REGISTER_MINIMUM_PIXEL       0x0A
#define PAW3395_REGISTER_SHUTTER_LOWER       0x0B
#define PAW3395_REGISTER_SHUTTER_UPPER       0x0C
#define PAW3395_REGISTER_OBSERVATION         0x15
#define PAW3395_REGISTER_MOTION_BURST        0x16
#define PAW3395_REGISTER_POWERUPRESET        0x3A
#define PAW3395_REGISTER_SHUTDOWN            0x3B
#define PAW3395_REGISTER_PERFORMANCE         0x40
#define PAW3395_REGISTER_SET_RESOLUTION      0x47
#define PAW3395_REGISTER_RESOLUTION_X_LOW    0x48
#define PAW3395_REGISTER_RESOLUTION_X_HIGH   0x49
#define PAW3395_REGISTER_RESOLUTION_Y_LOW    0x4A
#define PAW3395_REGISTER_RESOLUTION_Y_HIGH   0x4B
#define PAW3395_REGISTER_ANGLE_SNAP          0x56
#define PAW3395_REGISTER_RAWDATA_OUTPUT      0x58
#define PAW3395_REGISTER_RAWDATA_STATUS      0x59
#define PAW3395_REGISTER_RIPPLE_CTRL         0x5A
#define PAW3395_REGISTER_AXIS_CTRL           0x5B
#define PAW3395_REGISTER_MOTION_CTRL         0x5C
#define PAW3395_REGISTER_INV_PRODUCT_ID      0x5F
#define PAW3395_REGISTER_RUN_DOWNSHIFT       0x77
#define PAW3395_REGISTER_REST1_PERIOD        0x78
#define PAW3395_REGISTER_REST1_DOWNSHIFT     0x79
#define PAW3395_REGISTER_REST2_PERIOD        0x7A
#define PAW3395_REGISTER_REST2_DOWNSHIFT     0x7B
#define PAW3395_REGISTER_REST3_PERIOD        0x7C
#define PAW3395_REGISTER_RUN_DOWNSHIFT_MULT  0x7D
#define PAW3395_REGISTER_REST_DOWNSHIFT_MULT 0x7E
#define PAW3395_REGISTER_ANGLE_TUNE1         0x0577
#define PAW3395_REGISTER_ANGLE_TUNE2         0x0578
#define PAW3395_REGISTER_LIFT_CONFIG         0x0C4E
// clang-format on

#define US_BETWEEN_WRITES 5
#define US_BETWEEN_READS 5
#define US_DELAY_AFTER_ADDR 5
#define US_BEFORE_MOTION 100

static const uint8_t paw3395_startup_sequence[][2] PROGMEM = {
    {0x7F, 0x07}, {0x40, 0x41}, {0x7F, 0x00}, {0x40, 0x80}, {0x7F, 0x0E}, {0x55, 0x0D}, {0x56, 0x1B}, {0x57, 0xE8}, {0x58, 0xD5}, {0x7F, 0x14}, {0x42, 0xBC}, {0x43, 0x74}, {0x4B, 0x20}, {0x4D, 0x00}, {0x53, 0x0E}, {0x7F, 0x05}, {0x44, 0x04}, {0x4D, 0x06}, {0x51, 0x40}, {0x53, 0x40}, {0x55, 0xCA}, {0x5A, 0xE8}, {0x5B, 0xEA}, {0x61, 0x31}, {0x62, 0x64}, {0x6D, 0xB8}, {0x6E, 0x0F}, {0x70, 0x02}, {0x4A, 0x2A}, {0x60, 0x26}, {0x7F, 0x06}, {0x6D, 0x70}, {0x6E, 0x60}, {0x6F, 0x04}, {0x53, 0x02}, {0x55, 0x11}, {0x7A, 0x01}, {0x7D, 0x51}, {0x7F, 0x07}, {0x41, 0x10}, {0x42, 0x32}, {0x43, 0x00}, {0x7F, 0x08}, {0x71, 0x4F}, {0x7F, 0x09}, {0x62, 0x1F}, {0x63, 0x1F}, {0x65, 0x03}, {0x66, 0x03}, {0x67, 0x1F}, {0x68, 0x1F}, {0x69, 0x03}, {0x6A, 0x03}, {0x6C, 0x1F}, {0x6D, 0x1F}, {0x51, 0x04}, {0x53, 0x20}, {0x54, 0x20}, {0x71, 0x0C}, {0x72, 0x07}, {0x73, 0x07}, {0x7F, 0x0A}, {0x4A, 0x14}, {0x4C, 0x14}, {0x55, 0x19}, {0x7F, 0x14}, {0x4B, 0x30}, {0x4C, 0x03}, {0x61, 0x0B},
    {0x62, 0x0A}, {0x63, 0x02}, {0x7F, 0x15}, {0x4C, 0x02}, {0x56, 0x02}, {0x41, 0x91}, {0x4D, 0x0A}, {0x7F, 0x0C}, {0x4A, 0x10}, {0x4B, 0x0C}, {0x4C, 0x40}, {0x41, 0x25}, {0x55, 0x18}, {0x56, 0x14}, {0x49, 0x0A}, {0x42, 0x00}, {0x43, 0x2D}, {0x44, 0x0C}, {0x54, 0x1A}, {0x5A, 0x0D}, {0x5F, 0x1E}, {0x5B, 0x05}, {0x5E, 0x0F}, {0x7F, 0x0D}, {0x48, 0xDD}, {0x4F, 0x03}, {0x52, 0x49}, {0x51, 0x00}, {0x54, 0x5B}, {0x53, 0x00}, {0x56, 0x64}, {0x55, 0x00}, {0x58, 0xA5}, {0x57, 0x02}, {0x5A, 0x29}, {0x5B, 0x47}, {0x5C, 0x81}, {0x5D, 0x40}, {0x71, 0xDC}, {0x70, 0x07}, {0x73, 0x00}, {0x72, 0x08}, {0x75, 0xDC}, {0x74, 0x07}, {0x77, 0x00}, {0x76, 0x08}, {0x7F, 0x10}, {0x4C, 0xD0}, {0x7F, 0x00}, {0x4F, 0x63}, {0x4E, 0x00}, {0x52, 0x63}, {0x51, 0x00}, {0x54, 0x54}, {0x5A, 0x10}, {0x77, 0x4F}, {0x47, 0x01}, {0x5B, 0x40}, {0x64, 0x60}, {0x65, 0x06}, {0x66, 0x13}, {0x67, 0x0F}, {0x78, 0x01}, {0x79, 0x9C}, {0x40, 0x00}, {0x55, 0x02}, {0x23, 0x70}, {0x22, 0x01},
};

const pointing_device_driver_t paw3395_pointing_device_driver = {
    .init       = paw3395_init,
    .get_report = paw3395_get_report_driver,
    .set_cpi    = paw3395_set_cpi,
    .get_cpi    = paw3395_get_cpi,
};

void paw3395_spi_start(void) {
    spi_start(PAW3395_CS_PIN, false, PAW3395_SPI_MODE, PAW3395_SPI_DIVISOR);
}

void paw3395_write_register(uint8_t reg_addr, uint8_t data) {
    paw3395_spi_start();
    spi_write(reg_addr + 0x80);
    spi_write(data);
    spi_stop();
    wait_us(US_BETWEEN_WRITES);
}

uint8_t paw3395_read_register(uint8_t reg_addr) {
    paw3395_spi_start();
    spi_write(reg_addr + 0x00);
    wait_us(US_DELAY_AFTER_ADDR);
    uint8_t data = spi_read();
    spi_stop();

    return data;
}

void paw3395_init(void) {
    gpio_set_pin_output(PAW3395_CS_PIN);

    spi_init();

    for (uint8_t i = 0; i < ARRAY_SIZE(paw3395_startup_sequence); i++) {
        paw3395_write_register(pgm_read_byte(&paw3395_startup_sequence[i][0]), pgm_read_byte(&paw3395_startup_sequence[i][1]));
    }
    wait_ms(1);

    uint8_t count = 0;

    for (count = 0; count < 60; count++) {
        if (paw3395_read_register(0x6C) == 0x80) {
            break;
        }
        wait_ms(1);
    }
    if (count == 60) {
        paw3395_write_register(0x7F, 0x14);
        paw3395_write_register(0x6C, 0x00);
        paw3395_write_register(0x7F, 0x00);
    }
    paw3395_write_register(0x22, 0x00);
    paw3395_write_register(0x55, 0x00);
    paw3395_write_register(0x7F, 0x07);
    paw3395_write_register(0x40, 0x40);
    paw3395_write_register(0x7F, 0x00);
}

void paw3395_burst_motion_read(uint8_t *buffer) {
    paw3395_spi_start();
    wait_us(1);
    paw3395_write_register(PAW3395_REGISTER_MOTION_BURST, 0x00);
    wait_us(2);
    for (uint8_t i = 0; i < 12; i++) {
        buffer[i] = spi_read();
    }
    spi_stop();
    wait_us(4);
}

void paw3395_set_cpi(uint16_t cpi) {
    uint8_t temp;

    paw3395_spi_start();
    wait_us(1);
    paw3395_write_register(PAW3395_REGISTER_MOTION_CTRL, 0x00);
    temp = (uint8_t)(((cpi / 50) << 8) >> 8);
    paw3395_write_register(PAW3395_REGISTER_RESOLUTION_X_LOW, temp);
    temp = (uint8_t)((cpi / 50) >> 8);
    paw3395_write_register(PAW3395_REGISTER_RESOLUTION_X_HIGH, temp);
    paw3395_write_register(PAW3395_REGISTER_SET_RESOLUTION, 0x01);

    spi_stop();
    wait_us(4);
}

uint16_t paw3395_get_cpi(void) {
    return 5000;
}

paw3395_report_t  paw3395_get_report(void) {
    paw3395_report_t report = {0};
    return report;
}
report_mouse_t    paw3395_get_report_driver(report_mouse_t mouse_report) {
    return mouse_report;
}
