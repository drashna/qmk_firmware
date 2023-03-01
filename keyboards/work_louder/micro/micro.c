// Copyright 2022 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#if defined(ENCODER_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code_delay(KC_WH_U, 10);
        } else {
            tap_code_delay(KC_WH_D, 10);
        }
    }
    return true;
}
#endif

void work_louder_micro_led_1_on(void) {
    setPinOutput(WORK_LOUDER_LED_PIN_1);
    writePin(WORK_LOUDER_LED_PIN_1, true);
}
void work_louder_micro_led_2_on(void) {
    setPinOutput(WORK_LOUDER_LED_PIN_2);
    writePin(WORK_LOUDER_LED_PIN_2, true);
}
void work_louder_micro_led_3_on(void) {
    setPinOutput(WORK_LOUDER_LED_PIN_3);
    writePin(WORK_LOUDER_LED_PIN_3, true);
}

void work_louder_micro_led_1_off(void) {
    setPinInput(WORK_LOUDER_LED_PIN_1);
    writePin(WORK_LOUDER_LED_PIN_1, false);
}
void work_louder_micro_led_2_off(void) {
    setPinInput(WORK_LOUDER_LED_PIN_2);
    writePin(WORK_LOUDER_LED_PIN_2, false);
}
void work_louder_micro_led_3_off(void) {
    setPinInput(WORK_LOUDER_LED_PIN_3);
    writePin(WORK_LOUDER_LED_PIN_3, false);
}

void work_louder_micro_led_all_on(void) {
    work_louder_micro_led_1_on();
    work_louder_micro_led_2_on();
    work_louder_micro_led_3_on();
}

void work_louder_micro_led_all_off(void) {
    work_louder_micro_led_1_off();
    work_louder_micro_led_2_off();
    work_louder_micro_led_3_off();
}

void work_louder_micro_led_1_set(uint8_t n) {
#if WORK_LOUDER_LED_PIN_1 == B6
    OCR1B = n;
#else
    n ? work_louder_micro_led_1_on() : work_louder_micro_led_1_off();
#endif
}
void work_louder_micro_led_2_set(uint8_t n) {
#if WORK_LOUDER_LED_PIN_2 == B7
    OCR1C = n;
#else
    n ? work_louder_micro_led_2_on() : work_louder_micro_led_2_off();
#endif
}
void work_louder_micro_led_3_set(uint8_t n) {
#if WORK_LOUDER_LED_PIN_3 == B5
    OCR1A = n;
#else
    n ? work_louder_micro_led_3_on() : work_louder_micro_led_3_off();
#endif
}

void work_louder_micro_led_all_set(uint8_t n) {
    work_louder_micro_led_1_set(n);
    work_louder_micro_led_2_set(n);
    work_louder_micro_led_3_set(n);
}

void work_louder_led_init_animation(void) {
    work_louder_micro_led_all_off();

    wait_ms(500);
    work_louder_micro_led_1_on();
    wait_ms(100);
    work_louder_micro_led_2_on();
    wait_ms(100);
    work_louder_micro_led_3_on();
    wait_ms(100);
    work_louder_micro_led_1_off();
    wait_ms(100);
    work_louder_micro_led_2_off();
    wait_ms(100);
    work_louder_micro_led_3_off();
    wait_ms(200);
}


void suspend_power_down_kb(void) {
    suspend_power_down_user();
    work_louder_micro_led_all_off();
}

void suspend_wakeup_init_kb(void) {
    work_louder_led_init_animation();
    layer_state_set_kb(layer_state);
    suspend_wakeup_init_user();
}



work_louder_config_t work_louder_config;

#define WL_LED_MAX_BRIGHT 75

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_work_rgb(keycode, record) || !process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case QK_KB_9:
            if (record->event.pressed) {
                work_louder_config.led_level++;
                if (work_louder_config.led_level > 4) {
                    work_louder_config.led_level = 1;
                }
                work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * WL_LED_MAX_BRIGHT / 4));
                eeconfig_update_kb(work_louder_config.raw);
                layer_state_set_kb(layer_state);
            }
            break;
    }
    return true;
}


layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    layer_state_cmp(state, 1) ? work_louder_micro_led_1_on(): work_louder_micro_led_1_off();
    layer_state_cmp(state, 2) ? work_louder_micro_led_2_on(): work_louder_micro_led_2_off();
    layer_state_cmp(state, 3) ? work_louder_micro_led_3_on(): work_louder_micro_led_3_off();

    return state;
}

void eeconfig_init_kb(void) {
    work_louder_config.raw = 0;
    work_louder_config.led_level = 1;
    work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * WL_LED_MAX_BRIGHT / 4));
    eeconfig_update_kb(work_louder_config.raw);
    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    TCCR1A = 0b10101001;  // set and configure fast PWM
    TCCR1B = 0b00001001;  // set and configure fast PWM

    keyboard_post_init_user();

    work_louder_config.raw = eeconfig_read_kb();
    work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * WL_LED_MAX_BRIGHT / 4));
}

#ifdef VIA_ENABLE
enum via_indicator_value {
    id_wl_brightness = 1,
    id_wl_layer, // placeholder
};

void wl_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_wl_brightness:
            work_louder_config.led_level = (uint8_t)*value_data;
            work_louder_micro_led_all_set((uint8_t)(work_louder_config.led_level * WL_LED_MAX_BRIGHT / 4));
            layer_state_set_kb(layer_state);
            break;
        // case id_wl_layer:
        //     layer_move(*value_data);
        //     break;
    }
}

void wl_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_wl_brightness:
            *value_data = work_louder_config.led_level;
            break;
        // case id_wl_layer:
        //     *value_data = get_highest_layer(layer_state);
        //     break;
    }
}

void wl_config_save(void) {
    eeconfig_update_kb(work_louder_config.raw);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                wl_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                wl_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                wl_config_save();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }
    *command_id = id_unhandled;
}
#endif
