// Copyright 2024 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


#define ULPI_PIN_MODE (PAL_MODE_ALTERNATE(10) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST | PAL_STM32_PUPDR_FLOATING)

#define ULPI_STP_PIN C0
#define ULPI_DIR_PIN C2
#define ULPI_NXT_PIN C3
#define ULPI_CLK_PIN A5
#define ULPI_D0_PIN A3
#define ULPI_D1_PIN B0
#define ULPI_D2_PIN B1
#define ULPI_D3_PIN B10
#define ULPI_D4_PIN B11
#define ULPI_D5_PIN B12
#define ULPI_D6_PIN B13
#define ULPI_D7_PIN B5

#define ULPI_RST_PIN A6

void board_init(void) {
    palSetLineMode(ULPI_STP_PIN, ULPI_PIN_MODE);
    palSetLineMode(ULPI_DIR_PIN, ULPI_PIN_MODE);
    palSetLineMode(ULPI_NXT_PIN, ULPI_PIN_MODE);
    palSetLineMode(ULPI_CLK_PIN, ULPI_PIN_MODE);
    palSetLineMode(ULPI_D0_PIN, ULPI_PIN_MODE);
    palSetLineMode(ULPI_D1_PIN, ULPI_PIN_MODE);
    palSetLineMode(ULPI_D2_PIN, ULPI_PIN_MODE);
    palSetLineMode(ULPI_D3_PIN, ULPI_PIN_MODE);
    palSetLineMode(ULPI_D4_PIN, ULPI_PIN_MODE);
    palSetLineMode(ULPI_D5_PIN, ULPI_PIN_MODE);
    palSetLineMode(ULPI_D6_PIN, ULPI_PIN_MODE);
    palSetLineMode(ULPI_D7_PIN, ULPI_PIN_MODE);

    gpio_set_pin_output(ULPI_RST_PIN);
    gpio_write_pin_low(ULPI_RST_PIN);
}
