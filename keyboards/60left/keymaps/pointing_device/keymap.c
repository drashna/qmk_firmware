/* Copyright 2021 Quasar
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
#include "analog.h"
#include "pointing_device.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

// Joystick
// Set Pins
// uint8_t xPin  = 8;   // VRx / /B4
// uint8_t yPin  = 7;   // VRy // B5
uint8_t swPin = E6;  // SW

// Set Parameters
uint16_t minAxisValue = 0;
uint16_t maxAxisValue = 1023;

uint8_t maxCursorSpeed = 2;
uint8_t precisionSpeed = 1;
uint8_t speedRegulator = 20;  // Lower Values Create Faster Movement

int8_t xPolarity = 1;
int8_t yPolarity = 1;

uint8_t cursorTimeout = 10;

int16_t xOrigin, yOrigin;

uint16_t lastCursor = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,
        KC_TAB,  KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,
        KC_CAPS, KC_A,    KC_S,    KC_D,   KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,
        KC_LCTL, KC_LWIN, KC_LALT,         KC_LEFT, KC_UP,
                                   KC_SPC, KC_DOWN, KC_RGHT
    )
};


int16_t axisCoordinate(uint8_t pin, uint16_t origin) {
    int8_t  direction;
    int16_t distanceFromOrigin;
    int16_t range;

    int16_t position = analogReadPin(pin);

    if (origin == position) {
        return 0;
    } else if (origin > position) {
        distanceFromOrigin = origin - position;
        range              = origin - minAxisValue;
        direction          = -1;
    } else {
        distanceFromOrigin = position - origin;
        range              = maxAxisValue - origin;
        direction          = 1;
    }

    float   percent    = (float)distanceFromOrigin / range;
    int16_t coordinate = (int16_t)(percent * 100);
    if (coordinate < 0) {
        return 0;
    } else if (coordinate > 100) {
        return 100 * direction;
    } else {
        return coordinate * direction;
    }
}

int8_t axisToMouseComponent(uint8_t pin, int16_t origin, uint8_t maxSpeed, int8_t polarity) {
    int coordinate = axisCoordinate(pin, origin);
    if (coordinate == 0) {
        return 0;
    } else {
        float percent = (float)coordinate / 100;
        if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
            return percent * precisionSpeed * polarity * (abs(coordinate) / speedRegulator);
        } else {
            return percent * maxCursorSpeed * polarity * (abs(coordinate) / speedRegulator);
        }
    }
}


void pointing_device_task(void) {
    report_mouse_t report = pointing_device_get_report();

    // todo read as one vector
    if (timer_elapsed(lastCursor) > cursorTimeout) {
        lastCursor = timer_read();
        report.x   = axisToMouseComponent(B6, xOrigin, maxCursorSpeed, xPolarity);
        report.y   = axisToMouseComponent(B5, yOrigin, maxCursorSpeed, yPolarity);
    }

    static bool pin_state = false;

    if (readPin(C6) != pin_state) {
        pin_state = readPin(C6);
        if (pin_state) {
            report.buttons |= MOUSE_BTN1;
        } else {
            report.buttons &= ~MOUSE_BTN1;
        }
    }

    pointing_device_set_report(report);
    pointing_device_send();
}


void pointing_device_init(void) {
    // init pin? Is needed?
    setPinInputHigh(C6);
    // Account for drift
    xOrigin = analogReadPin(B6);
    yOrigin = analogReadPin(B5);
}
