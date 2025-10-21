// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(GP20);
    gpio_write_pin_high(GP20);
    keyboard_pre_init_user();
}
#endif
