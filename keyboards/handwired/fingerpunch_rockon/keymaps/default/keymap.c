

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _COLEMAK,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
    QWERTY = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_QWERTY] = LAYOUT_rockon_bp(
    KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_LPRN,                            KC_RPRN,   KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_BSPC,
    KC_TAB,    KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,      KC_LBRC,                            KC_RBRC,   KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,      KC_BSLS,
    KC_CAPS,   KC_A,      KC_S,      KC_D,      KC_F,      KC_G,      KC_LCBR,                            KC_RCBR,   KC_H,      KC_J,      KC_K,      KC_L,      KC_SCLN,   KC_QUOT,
    KC_LSFT,   KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,      ADJUST,                             ADJUST,    KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_ENT,
                          KC_LCTL,   KC_LGUI,   LOWER,     KC_SPC,    KC_LALT,   KC_MUTE, LCTL(KC_BSPC),  KC_RALT,   KC_SPC,    RAISE,     KC_RGUI,   KC_RCTL
),


[_COLEMAK] = LAYOUT_rockon_bp(
    KC_ESC,    KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_LPRN,                            KC_RPRN,   KC_6,      KC_7,      KC_8,      KC_9,      KC_0,      KC_BSPC,
    KC_TAB,    KC_Q,      KC_W,      KC_F,      KC_P,      KC_B,      KC_LBRC,                            KC_RBRC,   KC_J,      KC_L,      KC_U,      KC_Y,      KC_SCLN,   KC_BSLS,
    KC_CAPS,   KC_A,      KC_R,      KC_S,      KC_T,      KC_G,      KC_LCBR,                            KC_RCBR,   KC_M,      KC_N,      KC_E,      KC_I,      KC_O,      KC_QUOT,
    KC_LSFT,   KC_Z,      KC_X,      KC_C,      KC_D,      KC_V,      ADJUST,                             ADJUST,    KC_K,      KC_H,      KC_COMM,   KC_DOT,    KC_SLSH,   KC_ENT,
                          KC_LCTL,   KC_LGUI,   LOWER,     KC_SPC,    KC_LALT,   KC_MUTE, LCTL(KC_BSPC),  KC_RALT,   KC_SPC,    RAISE,     KC_RGUI,   KC_RCTL
),


[_LOWER] = LAYOUT_rockon_bp(
    KC_GRV,        _______,       _______,       _______,       _______,       _______,       _______,                              _______,       _______,       _______,       _______,       KC_MINS,       KC_EQL,        _______,
    _______,       _______,       _______,       _______,       _______,       _______,       _______,                              _______,       _______,       _______,       _______,       _______,       _______,       _______,
    _______,       _______,       _______,       _______,       _______,       _______,       _______,                              _______,       _______,       _______,       _______,       _______,       _______,       _______,
    _______,       _______,       _______,       _______,       _______,       _______,       _______,                              _______,       _______,       _______,       _______,       _______,       _______,       _______,
                                  _______,       _______,       _______,       _______,       _______,    _______,       _______,   _______,       _______,       _______,       _______,       _______
),

[_RAISE] = LAYOUT_rockon_bp(
    KC_GRV,        _______,       _______,       _______,       _______,       _______,       _______,                              _______,       _______,       _______,       _______,       KC_MINS,       KC_EQL,        _______,
    _______,       KC_PGUP,       KC_UP,         KC_PGDN,       _______,       _______,       _______,                              _______,       _______,       _______,       _______,       _______,       _______,       _______,
    KC_HOME,       KC_LEFT,       KC_DOWN,       KC_RGHT,       KC_END,        _______,       _______,                              _______,       _______,       _______,       _______,       _______,       _______,       _______,
    _______,       _______,       _______,       _______,       _______,       _______,       _______,                              _______,       _______,       _______,       _______,       _______,       _______,       _______,
                                  _______,       _______,       _______,       _______,       _______,    _______,       _______,   _______,       _______,       _______,       _______,       _______
),

[_ADJUST] =  LAYOUT_rockon_bp(
    RESET,         KC_F1,         KC_F2,         KC_F3,         KC_F4,         KC_F5,         _______,                              _______,       KC_F6,         KC_F7,         KC_F8,         KC_F9,         KC_F10,        _______,
    _______,       RGB_TOG,       RGB_RMOD,      RGB_MOD,       _______,       TG(_QWERTY),   _______,                              _______,       _______,       _______,       _______,       KC_F11,        KC_F12,        _______,
    _______,       RGB_SPI,       RGB_HUI,       RGB_SAI,       RGB_VAI,       TG(_COLEMAK),  _______,                              _______,       _______,       _______,       _______,       _______,       _______,       _______,
    _______,       RGB_SPD,       RGB_HUD,       RGB_SAD,       RGB_VAD,       _______,       _______,                              _______,       _______,       _______,       _______,       _______,       _______,       _______,
                                  _______,       _______,       _______,       _______,       _______,    _______,       _______,   _______,       _______,       _______,       _______,       _______
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
        default:
            break;
    }

    return true;
}
