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

#ifdef ENCODER_ENABLE
#    include "drashna.h"

#    ifndef NUMBER_OF_ENCODERS
static pin_t encoders_pad_a[] = ENCODERS_PAD_A;
#        if defined(SPLIT_KEYBOARD)
#            define NUMBER_OF_ENCODERS (2 * (sizeof(encoders_pad_a) / sizeof(pin_t)))
#        else
#            define NUMBER_OF_ENCODERS (sizeof(encoders_pad_a) / sizeof(pin_t))
#        endif
#    endif

#    ifndef ENCODER_LOCATION
#        error ENCODER_LOCATION array not defined
#    else
static keypos_t encoder_location[NUMBER_OF_ENCODERS] = ENCODER_LOCATION;
#    endif

extern const uint16_t PROGMEM encoder_map[][NUMBER_OF_ENCODERS][2];

void encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t  layer   = get_highest_layer(layer_state);
    uint16_t keycode = pgm_read_word(&encoder_map[layer][index][clockwise]);

    keyevent_t  encoder_event = (keyevent_t){.key = encoder_location[index], .pressed = true, .time = (timer_read() | 1)};
    keyrecord_t record        = {.event = encoder_event};

    while (keycode == KC_TRANSPARENT && layer > 0) {
        if (layer_state_is(layer--)) { keycode = pgm_read_word(&encoder_map[layer][index][clockwise]); }
    }
    if (keycode != KC_TRANSPARENT && keycode != KC_NO) {
        if (process_record_quantum_helper(keycode, &record)) {
            record.event.pressed = false;
            if (process_record_quantum_helper(keycode, &record)) {
                if (keycode <= QK_MODS_MAX)
                tap_code16(keycode);
            }
        }
    }
}

#endif
