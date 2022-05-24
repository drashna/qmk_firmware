// Copyright 2022 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#undef LAYOUT
#define LAYOUT( \
    keA, keB, keC, keD, \
    k0A, k0B, k0C, k0D, \
    k1A, k1B, k1C, k1D, \
    k2A, k2B, k2C, k2D, \
    k3A, k3B, k3C) { \
     {k0A, k0B, k0C, k0D}, \
     {k1A, k1B, k1C, k1D}, \
     {k2A, k2B, k2C, k2D}, \
     {k3A, k3B, k3C, KC_NO}, \
     {keA, keB, keC, keD} \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        KC_VOLD, KC_VOLU, KC_WH_D, KC_WH_U,
        KC_1,    KC_2,    KC_3,    KC_4,
        KC_5,    KC_6,    KC_7,    KC_8,
        KC_9,    KC_0,    KC_A,    KC_B,
        TO(1),   KC_C,    KC_D
    ),
    LAYOUT(
        _______, _______, _______, _______,
        KC_1,    KC_2,    KC_3,    KC_4,
        KC_5,    KC_6,    KC_7,    KC_8,
        KC_9,    KC_0,    KC_A,    KC_B,
        TO(2),   KC_C,    KC_D
    ),
    LAYOUT(
        _______, _______, _______, _______,
        KC_1,    KC_2,    KC_3,    KC_4,
        KC_5,    KC_6,    KC_7,    KC_8,
        KC_9,    KC_0,    KC_A,    KC_B,
        TO(3),   KC_C,    KC_D
    ),
    LAYOUT(
        _______, _______, _______, _______,
        KC_1,    KC_2,    KC_3,    KC_4,
        KC_5,    KC_6,    KC_7,    KC_8,
        KC_9,    KC_0,    KC_A,    KC_B,
        TO(0),   KC_C,    USER00
    )
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t led_level : 3;
    };
} work_louder_config_t;

work_louder_config_t work_louder_config;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %b, time: %5u, int: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif

    switch (keycode) {
        case USER00:
            if (record->event.pressed) {
                work_louder_config.led_level++;
                if (work_louder_config.led_level > 4) {
                    work_louder_config.led_level = 0;
                }
                work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * 255 / 4));
                eeconfig_update_user(work_louder_config.raw);
                layer_state_set_kb(layer_state);
            }
            break;
    }
    return true;
}


layer_state_t layer_state_set_user(layer_state_t state) {
    layer_state_cmp(state, 1) ? work_louder_micro_led_1_on(): work_louder_micro_led_1_off();
    layer_state_cmp(state, 2) ? work_louder_micro_led_2_on(): work_louder_micro_led_2_off();
    layer_state_cmp(state, 3) ? work_louder_micro_led_3_on(): work_louder_micro_led_3_off();

    return state;
}

void eeconfig_init_user(void) {
    work_louder_config.raw = 0;
    work_louder_config.led_level = 1;
    eeconfig_update_user(work_louder_config.raw);
}

void matrix_init_user(void) {
    work_louder_config.raw = eeconfig_read_user();
    work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * 255 / 4));
}
