/* Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "tractyl_manuform.h"
#ifdef POINTING_DEVICE_ENABLE
#    include "pointing_device.h"
#endif

#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif // CONSOLE_ENABLE

#ifdef POINTING_DEVICE_ENABLE
void matrix_power_up(void) {
    pointing_device_task();
}
#endif // POINTING_DEVICE_ENABLE

__attribute__((weak)) void user_button_init(void) {
#ifdef USER_BUTTON_PIN
    gpio_set_pin_input_high(USER_BUTTON_PIN);
#endif // USER_BUTTON_PIN
}

__attribute__((weak)) bool check_user_button_state(void) {
#ifdef USER_BUTTON_PIN
    return !gpio_read_pin(USER_BUTTON_PIN);
#endif // USER_BUTTON_PIN
    return false;
}

void keyboard_post_init_kb(void) {
#ifdef DEBUG_LED_PIN
    gpio_set_pin_output(DEBUG_LED_PIN);
    gpio_write_pin_low(DEBUG_LED_PIN);
#endif // DEBUG_LED_PIN
    keyboard_post_init_user();
}

void keyboard_pre_init_kb(void) {
    user_button_init();
    keyboard_pre_init_user();
}

__attribute__((weak)) void execute_user_button_action(bool state) {
    if (state) {
        if (is_keyboard_master()) {
            reset_keyboard();
        } else {
            soft_reset_keyboard();
        }
    }
}

void housekeeping_task_kb(void) {
    static bool last_state = false;
    bool        state      = check_user_button_state();
    if (state != last_state) {
        last_state = state;
        execute_user_button_action(state);
    }
    // no need for user function, is called already
}

#ifdef USER_BUTTON_PIN
/**
 * @brief Replace and add upon the default bootmagic reset function.
 * In this case, we also check the user button.
 *
 * @return true if the user button is pressed, or normal bootmagic key position.
 * @return false if the user button is not pressed and normal bootmagic key position is not pressed.
 */
__attribute__((weak)) bool bootmagic_should_reset(void) {
    uint8_t row = BOOTMAGIC_ROW;
    uint8_t col = BOOTMAGIC_COLUMN;

#    if defined(SPLIT_KEYBOARD) && defined(BOOTMAGIC_ROW_RIGHT) && defined(BOOTMAGIC_COLUMN_RIGHT)
    if (!is_keyboard_left()) {
        row = BOOTMAGIC_ROW_RIGHT;
        col = BOOTMAGIC_COLUMN_RIGHT;
    }
#    endif

    return matrix_get_row(row) & (1 << col) || check_user_button_state();
}
#endif // USER_BUTTON_PIN

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }
#ifdef RGB_MATRIX_ENABLE
    void rgb_matrix_update_pwm_buffers(void);
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif // RGB_MATRIX_ENABLE
    return true;
}

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
bool is_mouse_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case KB_KEYCODE_RANGE:
        case POINTER_DEFAULT_DPI_FORWARD:
        case POINTER_DEFAULT_DPI_REVERSE:
        case POINTER_SNIPING_DPI_FORWARD:
        case POINTER_SNIPING_DPI_REVERSE:
        case SNIPING_MODE:
        case SNIPING_MODE_TOGGLE:
            return true;
        default:
            return is_mouse_record_user(keycode, record);
    }
}
#endif // POINTING_DEVICE_AUTO_MOUSE_ENABLE
