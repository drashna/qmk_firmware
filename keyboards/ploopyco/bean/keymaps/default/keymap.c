/* Copyright 2026 Colin Lam (Ploopy Corporation)
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

// Button order in matrix: bottom left, top left, top right, bottom right
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( MS_BTN1, MS_BTN3, DRAG_SCROLL, MS_BTN2 ),
};

// Set up a few combos to do things with multiple buttons.
enum combos {
  BACK,
  FORWARD
};

// Top right button, followed by top left.
const uint16_t PROGMEM back_combo[] = {DRAG_SCROLL, MS_BTN3, COMBO_END};
// Top left button, followed by top right.
const uint16_t PROGMEM forward_combo[] = {MS_BTN3, DRAG_SCROLL, COMBO_END};

combo_t key_combos[] = {
  [BACK] = COMBO(back_combo, MS_BTN4),
  [FORWARD] = COMBO(forward_combo, MS_BTN5),
};

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    //debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;
}
