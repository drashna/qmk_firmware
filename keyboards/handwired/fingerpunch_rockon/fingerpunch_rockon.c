/* Copyright 2021 Sadek Baroudi <sadekbaroudi@gmail.com>
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
#include "quantum.h"

void matrix_init_kb(void) {
    setPinInputHigh(A0);
    matrix_init_user();
}

void matrix_scan_kb(void) {
    if (!readPin(A0)) {
        reset_keyboard();
    }
    matrix_scan_user();
}

void matrix_output_unselect_delay(uint8_t line, bool key_pressed) {
    for (int32_t i = 0; i < 40; i++) {
        __asm__ volatile("nop" ::: "memory");
    }
}

#ifdef SWAP_HANDS_ENABLE
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    {{3, 5}, {8, 0}, {7, 0}, {6, 0}, {5, 0}, {4, 0}, {3, 0}, {2, 0}, {1, 0}},
    {{5, 5}, {8, 1}, {7, 1}, {6, 1}, {5, 1}, {4, 1}, {3, 1}, {2, 1}, {1, 1}},
    {{6, 5}, {8, 2}, {7, 2}, {6, 2}, {5, 2}, {4, 2}, {3, 2}, {2, 2}, {1, 2}},
    {{7, 5}, {8, 3}, {7, 3}, {6, 3}, {5, 3}, {4, 3}, {3, 3}, {2, 3}, {1, 3}},
    {{8, 5}, {8, 4}, {7, 4}, {6, 4}, {5, 4}, {4, 4}, {3, 4}, {2, 4}, {1, 4}},
    {{8, 6}, {2, 5}, {1, 5}, {0, 0}, {4, 5}, {0, 1}, {0, 2}, {0, 3}, {0, 4}},
    {{8, 7}, {1, 6}, {5, 6}, {6, 6}, {4, 6}, {2, 6}, {3, 6}, {0, 7}, {0, 5}},
    {{7, 6}, {7, 7}, {5, 7}, {6, 7}, {4, 7}, {2, 7}, {3, 7}, {1, 7}, {0, 6}},
};

#    ifdef ENCODER_MAP_ENABLE
const uint8_t PROGMEM encoder_hand_swap_config[NUM_ENCODERS] = {1, 0};
#    endif
#endif
