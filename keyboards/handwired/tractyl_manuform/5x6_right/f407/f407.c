/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#ifdef USB_VBUS_PIN
bool usb_vbus_state(void) {
    gpio_set_pin_input_low(USB_VBUS_PIN);
    wait_us(5);
    return gpio_read_pin(USB_VBUS_PIN);
}
#endif

__attribute__((weak)) void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int32_t i = 0; i < 20; i++) {
        __asm__ volatile("nop" ::: "memory");
    }
}

void user_button_init(void) {
    gpio_set_pin_output(DEBUG_LED_PIN);
    // Pin needs to be configured as input low
#ifdef USER_BUTTON_PIN
    gpio_set_pin_input_high(USER_BUTTON_PIN);
#endif // USER_BUTTON_PIN
}

bool check_user_button_state(void) {
#ifdef DEBUG_LED_PIN
    gpio_write_pin(DEBUG_LED_PIN, !is_keyboard_master());
#endif // DEBUG_LED_PIN
#ifdef USER_BUTTON_PIN
    return !gpio_read_pin(USER_BUTTON_PIN);
#endif // USER_BUTTON_PIN
    return false;
}
