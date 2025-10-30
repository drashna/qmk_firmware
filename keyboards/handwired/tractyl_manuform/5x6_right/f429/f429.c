// Copyright 2025 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-3.0-or-later


#include "tractyl_manuform.h"

void user_button_init(void) {
    // Pin needs to be configured as input low
#ifdef USER_BUTTON_PIN
    gpio_set_pin_input_high(USER_BUTTON_PIN);
#endif // USER_BUTTON_PIN
    gpio_set_pin_output(F7);
    gpio_write_pin_low(F7);
    gpio_set_pin_output(F8);
    gpio_write_pin_low(F8);
    gpio_set_pin_output(F9);
    gpio_write_pin_low(F9);
}

__attribute__((weak)) void housekeeping_task_sdram(void) {}

bool check_user_button_state(void) {
    housekeeping_task_sdram();
#ifdef DEBUG_LED_PIN
    gpio_write_pin(DEBUG_LED_PIN, is_keyboard_master());
#endif
#ifdef USER_BUTTON_PIN
    gpio_write_pin(F8, !gpio_read_pin(USER_BUTTON_PIN));
    return !gpio_read_pin(USER_BUTTON_PIN);
#endif // USER_BUTTON_PIN
    return false;
}
