/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
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
#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MS_BTN5, KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2, LT(1,KC_MS_BTN7),
        KC_MS_BTN4
    ),
    [1] = LAYOUT(
        QK_KB_0, QK_KB_1, KC_NO, QK_BOOT, KC_TRNS,
        KC_NO
    ),
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] =  { ENCODER_CCW_CW(KC_WH_D, KC_WH_U) },
    [1] =  { ENCODER_CCW_CW(_______, _______) },
};
