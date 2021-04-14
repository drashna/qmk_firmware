/*
Copyright 2021 Drashna Jael're

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID    0xDECE
#define PRODUCT_ID   0x001F
#define DEVICE_VER   0x0001
#define MANUFACTURER Drashna Jaelre
#define PRODUCT      for_saurabh

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 3

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { D3 }
#define MATRIX_COL_PINS { D5 }
#define UNUSED_PINS
#define MATRIX_MASKED

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { C6 }
#define ENCODERS_PAD_B { D6 }

#define RGB_DI_PIN B3
#define RGBLED_NUM 30
#define RGBLIGHT_ANIMATIONS

#define VIA_ENCODERS 1


#define ENCODERS_CW_KEY  { { 0, 1 } }
#define ENCODERS_CCW_KEY { { 0, 2 } }
