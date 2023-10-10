// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/*******************************************************************************
  88888888888 888      d8b                .d888 d8b 888               d8b
      888     888      Y8P               d88P"  Y8P 888               Y8P
      888     888                        888        888
      888     88888b.  888 .d8888b       888888 888 888  .d88b.       888 .d8888b
      888     888 "88b 888 88K           888    888 888 d8P  Y8b      888 88K
      888     888  888 888 "Y8888b.      888    888 888 88888888      888 "Y8888b.
      888     888  888 888      X88      888    888 888 Y8b.          888      X88
      888     888  888 888  88888P'      888    888 888  "Y8888       888  88888P'
                                                        888                 888
                                                        888                 888
                                                        888                 888
     .d88b.   .d88b.  88888b.   .d88b.  888d888 8888b.  888888 .d88b.   .d88888
    d88P"88b d8P  Y8b 888 "88b d8P  Y8b 888P"      "88b 888   d8P  Y8b d88" 888
    888  888 88888888 888  888 88888888 888    .d888888 888   88888888 888  888
    Y88b 888 Y8b.     888  888 Y8b.     888    888  888 Y88b. Y8b.     Y88b 888
     "Y88888  "Y8888  888  888  "Y8888  888    "Y888888  "Y888 "Y8888   "Y88888
         888
    Y8b d88P
     "Y88P"
*******************************************************************************/

// clang-format off
extern "C" {
#include <keycode.h>
}
#include <map>
#include <string>
#include <cstdint>

std::map<uint16_t, std::string> KEYCODE_ID_TABLE = {
    {KC_NO, "KC_NO"},
    {KC_TRANSPARENT, "KC_TRANSPARENT"},
    {KC_A, "KC_A"},
    {KC_B, "KC_B"},
    {KC_C, "KC_C"},
    {KC_D, "KC_D"},
    {KC_E, "KC_E"},
    {KC_F, "KC_F"},
    {KC_G, "KC_G"},
    {KC_H, "KC_H"},
    {KC_I, "KC_I"},
    {KC_J, "KC_J"},
    {KC_K, "KC_K"},
    {KC_L, "KC_L"},
    {KC_M, "KC_M"},
    {KC_N, "KC_N"},
    {KC_O, "KC_O"},
    {KC_P, "KC_P"},
    {KC_Q, "KC_Q"},
    {KC_R, "KC_R"},
    {KC_S, "KC_S"},
    {KC_T, "KC_T"},
    {KC_U, "KC_U"},
    {KC_V, "KC_V"},
    {KC_W, "KC_W"},
    {KC_X, "KC_X"},
    {KC_Y, "KC_Y"},
    {KC_Z, "KC_Z"},
    {KC_1, "KC_1"},
    {KC_2, "KC_2"},
    {KC_3, "KC_3"},
    {KC_4, "KC_4"},
    {KC_5, "KC_5"},
    {KC_6, "KC_6"},
    {KC_7, "KC_7"},
    {KC_8, "KC_8"},
    {KC_9, "KC_9"},
    {KC_0, "KC_0"},
    {KC_ENTER, "KC_ENTER"},
    {KC_ESCAPE, "KC_ESCAPE"},
    {KC_BACKSPACE, "KC_BACKSPACE"},
    {KC_TAB, "KC_TAB"},
    {KC_SPACE, "KC_SPACE"},
    {KC_MINUS, "KC_MINUS"},
    {KC_EQUAL, "KC_EQUAL"},
    {KC_LEFT_BRACKET, "KC_LEFT_BRACKET"},
    {KC_RIGHT_BRACKET, "KC_RIGHT_BRACKET"},
    {KC_BACKSLASH, "KC_BACKSLASH"},
    {KC_NONUS_HASH, "KC_NONUS_HASH"},
    {KC_SEMICOLON, "KC_SEMICOLON"},
    {KC_QUOTE, "KC_QUOTE"},
    {KC_GRAVE, "KC_GRAVE"},
    {KC_COMMA, "KC_COMMA"},
    {KC_DOT, "KC_DOT"},
    {KC_SLASH, "KC_SLASH"},
    {KC_CAPS_LOCK, "KC_CAPS_LOCK"},
    {KC_F1, "KC_F1"},
    {KC_F2, "KC_F2"},
    {KC_F3, "KC_F3"},
    {KC_F4, "KC_F4"},
    {KC_F5, "KC_F5"},
    {KC_F6, "KC_F6"},
    {KC_F7, "KC_F7"},
    {KC_F8, "KC_F8"},
    {KC_F9, "KC_F9"},
    {KC_F10, "KC_F10"},
    {KC_F11, "KC_F11"},
    {KC_F12, "KC_F12"},
    {KC_PRINT_SCREEN, "KC_PRINT_SCREEN"},
    {KC_SCROLL_LOCK, "KC_SCROLL_LOCK"},
    {KC_PAUSE, "KC_PAUSE"},
    {KC_INSERT, "KC_INSERT"},
    {KC_HOME, "KC_HOME"},
    {KC_PAGE_UP, "KC_PAGE_UP"},
    {KC_DELETE, "KC_DELETE"},
    {KC_END, "KC_END"},
    {KC_PAGE_DOWN, "KC_PAGE_DOWN"},
    {KC_RIGHT, "KC_RIGHT"},
    {KC_LEFT, "KC_LEFT"},
    {KC_DOWN, "KC_DOWN"},
    {KC_UP, "KC_UP"},
    {KC_NUM_LOCK, "KC_NUM_LOCK"},
    {KC_KP_SLASH, "KC_KP_SLASH"},
    {KC_KP_ASTERISK, "KC_KP_ASTERISK"},
    {KC_KP_MINUS, "KC_KP_MINUS"},
    {KC_KP_PLUS, "KC_KP_PLUS"},
    {KC_KP_ENTER, "KC_KP_ENTER"},
    {KC_KP_1, "KC_KP_1"},
    {KC_KP_2, "KC_KP_2"},
    {KC_KP_3, "KC_KP_3"},
    {KC_KP_4, "KC_KP_4"},
    {KC_KP_5, "KC_KP_5"},
    {KC_KP_6, "KC_KP_6"},
    {KC_KP_7, "KC_KP_7"},
    {KC_KP_8, "KC_KP_8"},
    {KC_KP_9, "KC_KP_9"},
    {KC_KP_0, "KC_KP_0"},
    {KC_KP_DOT, "KC_KP_DOT"},
    {KC_NONUS_BACKSLASH, "KC_NONUS_BACKSLASH"},
    {KC_APPLICATION, "KC_APPLICATION"},
    {KC_KB_POWER, "KC_KB_POWER"},
    {KC_KP_EQUAL, "KC_KP_EQUAL"},
    {KC_F13, "KC_F13"},
    {KC_F14, "KC_F14"},
    {KC_F15, "KC_F15"},
    {KC_F16, "KC_F16"},
    {KC_F17, "KC_F17"},
    {KC_F18, "KC_F18"},
    {KC_F19, "KC_F19"},
    {KC_F20, "KC_F20"},
    {KC_F21, "KC_F21"},
    {KC_F22, "KC_F22"},
    {KC_F23, "KC_F23"},
    {KC_F24, "KC_F24"},
    {KC_EXECUTE, "KC_EXECUTE"},
    {KC_HELP, "KC_HELP"},
    {KC_MENU, "KC_MENU"},
    {KC_SELECT, "KC_SELECT"},
    {KC_STOP, "KC_STOP"},
    {KC_AGAIN, "KC_AGAIN"},
    {KC_UNDO, "KC_UNDO"},
    {KC_CUT, "KC_CUT"},
    {KC_COPY, "KC_COPY"},
    {KC_PASTE, "KC_PASTE"},
    {KC_FIND, "KC_FIND"},
    {KC_KB_MUTE, "KC_KB_MUTE"},
    {KC_KB_VOLUME_UP, "KC_KB_VOLUME_UP"},
    {KC_KB_VOLUME_DOWN, "KC_KB_VOLUME_DOWN"},
    {KC_LOCKING_CAPS_LOCK, "KC_LOCKING_CAPS_LOCK"},
    {KC_LOCKING_NUM_LOCK, "KC_LOCKING_NUM_LOCK"},
    {KC_LOCKING_SCROLL_LOCK, "KC_LOCKING_SCROLL_LOCK"},
    {KC_KP_COMMA, "KC_KP_COMMA"},
    {KC_KP_EQUAL_AS400, "KC_KP_EQUAL_AS400"},
    {KC_INTERNATIONAL_1, "KC_INTERNATIONAL_1"},
    {KC_INTERNATIONAL_2, "KC_INTERNATIONAL_2"},
    {KC_INTERNATIONAL_3, "KC_INTERNATIONAL_3"},
    {KC_INTERNATIONAL_4, "KC_INTERNATIONAL_4"},
    {KC_INTERNATIONAL_5, "KC_INTERNATIONAL_5"},
    {KC_INTERNATIONAL_6, "KC_INTERNATIONAL_6"},
    {KC_INTERNATIONAL_7, "KC_INTERNATIONAL_7"},
    {KC_INTERNATIONAL_8, "KC_INTERNATIONAL_8"},
    {KC_INTERNATIONAL_9, "KC_INTERNATIONAL_9"},
    {KC_LANGUAGE_1, "KC_LANGUAGE_1"},
    {KC_LANGUAGE_2, "KC_LANGUAGE_2"},
    {KC_LANGUAGE_3, "KC_LANGUAGE_3"},
    {KC_LANGUAGE_4, "KC_LANGUAGE_4"},
    {KC_LANGUAGE_5, "KC_LANGUAGE_5"},
    {KC_LANGUAGE_6, "KC_LANGUAGE_6"},
    {KC_LANGUAGE_7, "KC_LANGUAGE_7"},
    {KC_LANGUAGE_8, "KC_LANGUAGE_8"},
    {KC_LANGUAGE_9, "KC_LANGUAGE_9"},
    {KC_ALTERNATE_ERASE, "KC_ALTERNATE_ERASE"},
    {KC_SYSTEM_REQUEST, "KC_SYSTEM_REQUEST"},
    {KC_CANCEL, "KC_CANCEL"},
    {KC_CLEAR, "KC_CLEAR"},
    {KC_PRIOR, "KC_PRIOR"},
    {KC_RETURN, "KC_RETURN"},
    {KC_SEPARATOR, "KC_SEPARATOR"},
    {KC_OUT, "KC_OUT"},
    {KC_OPER, "KC_OPER"},
    {KC_CLEAR_AGAIN, "KC_CLEAR_AGAIN"},
    {KC_CRSEL, "KC_CRSEL"},
    {KC_EXSEL, "KC_EXSEL"},
    {KC_SYSTEM_POWER, "KC_SYSTEM_POWER"},
    {KC_SYSTEM_SLEEP, "KC_SYSTEM_SLEEP"},
    {KC_SYSTEM_WAKE, "KC_SYSTEM_WAKE"},
    {KC_AUDIO_MUTE, "KC_AUDIO_MUTE"},
    {KC_AUDIO_VOL_UP, "KC_AUDIO_VOL_UP"},
    {KC_AUDIO_VOL_DOWN, "KC_AUDIO_VOL_DOWN"},
    {KC_MEDIA_NEXT_TRACK, "KC_MEDIA_NEXT_TRACK"},
    {KC_MEDIA_PREV_TRACK, "KC_MEDIA_PREV_TRACK"},
    {KC_MEDIA_STOP, "KC_MEDIA_STOP"},
    {KC_MEDIA_PLAY_PAUSE, "KC_MEDIA_PLAY_PAUSE"},
    {KC_MEDIA_SELECT, "KC_MEDIA_SELECT"},
    {KC_MEDIA_EJECT, "KC_MEDIA_EJECT"},
    {KC_MAIL, "KC_MAIL"},
    {KC_CALCULATOR, "KC_CALCULATOR"},
    {KC_MY_COMPUTER, "KC_MY_COMPUTER"},
    {KC_WWW_SEARCH, "KC_WWW_SEARCH"},
    {KC_WWW_HOME, "KC_WWW_HOME"},
    {KC_WWW_BACK, "KC_WWW_BACK"},
    {KC_WWW_FORWARD, "KC_WWW_FORWARD"},
    {KC_WWW_STOP, "KC_WWW_STOP"},
    {KC_WWW_REFRESH, "KC_WWW_REFRESH"},
    {KC_WWW_FAVORITES, "KC_WWW_FAVORITES"},
    {KC_MEDIA_FAST_FORWARD, "KC_MEDIA_FAST_FORWARD"},
    {KC_MEDIA_REWIND, "KC_MEDIA_REWIND"},
    {KC_BRIGHTNESS_UP, "KC_BRIGHTNESS_UP"},
    {KC_BRIGHTNESS_DOWN, "KC_BRIGHTNESS_DOWN"},
    {KC_CONTROL_PANEL, "KC_CONTROL_PANEL"},
    {KC_ASSISTANT, "KC_ASSISTANT"},
    {KC_MISSION_CONTROL, "KC_MISSION_CONTROL"},
    {KC_LAUNCHPAD, "KC_LAUNCHPAD"},
    {KC_GLOBE, "KC_GLOBE"},
    {KC_MS_UP, "KC_MS_UP"},
    {KC_MS_DOWN, "KC_MS_DOWN"},
    {KC_MS_LEFT, "KC_MS_LEFT"},
    {KC_MS_RIGHT, "KC_MS_RIGHT"},
    {KC_MS_BTN1, "KC_MS_BTN1"},
    {KC_MS_BTN2, "KC_MS_BTN2"},
    {KC_MS_BTN3, "KC_MS_BTN3"},
    {KC_MS_BTN4, "KC_MS_BTN4"},
    {KC_MS_BTN5, "KC_MS_BTN5"},
    {KC_MS_BTN6, "KC_MS_BTN6"},
    {KC_MS_BTN7, "KC_MS_BTN7"},
    {KC_MS_BTN8, "KC_MS_BTN8"},
    {KC_MS_WH_UP, "KC_MS_WH_UP"},
    {KC_MS_WH_DOWN, "KC_MS_WH_DOWN"},
    {KC_MS_WH_LEFT, "KC_MS_WH_LEFT"},
    {KC_MS_WH_RIGHT, "KC_MS_WH_RIGHT"},
    {KC_MS_ACCEL0, "KC_MS_ACCEL0"},
    {KC_MS_ACCEL1, "KC_MS_ACCEL1"},
    {KC_MS_ACCEL2, "KC_MS_ACCEL2"},
    {KC_LEFT_CTRL, "KC_LEFT_CTRL"},
    {KC_LEFT_SHIFT, "KC_LEFT_SHIFT"},
    {KC_LEFT_ALT, "KC_LEFT_ALT"},
    {KC_LEFT_GUI, "KC_LEFT_GUI"},
    {KC_RIGHT_CTRL, "KC_RIGHT_CTRL"},
    {KC_RIGHT_SHIFT, "KC_RIGHT_SHIFT"},
    {KC_RIGHT_ALT, "KC_RIGHT_ALT"},
    {KC_RIGHT_GUI, "KC_RIGHT_GUI"},
    {QK_SWAP_HANDS_TOGGLE, "QK_SWAP_HANDS_TOGGLE"},
    {QK_SWAP_HANDS_TAP_TOGGLE, "QK_SWAP_HANDS_TAP_TOGGLE"},
    {QK_SWAP_HANDS_MOMENTARY_ON, "QK_SWAP_HANDS_MOMENTARY_ON"},
    {QK_SWAP_HANDS_MOMENTARY_OFF, "QK_SWAP_HANDS_MOMENTARY_OFF"},
    {QK_SWAP_HANDS_OFF, "QK_SWAP_HANDS_OFF"},
    {QK_SWAP_HANDS_ON, "QK_SWAP_HANDS_ON"},
    {QK_SWAP_HANDS_ONE_SHOT, "QK_SWAP_HANDS_ONE_SHOT"},
    {QK_MAGIC_SWAP_CONTROL_CAPS_LOCK, "QK_MAGIC_SWAP_CONTROL_CAPS_LOCK"},
    {QK_MAGIC_UNSWAP_CONTROL_CAPS_LOCK, "QK_MAGIC_UNSWAP_CONTROL_CAPS_LOCK"},
    {QK_MAGIC_TOGGLE_CONTROL_CAPS_LOCK, "QK_MAGIC_TOGGLE_CONTROL_CAPS_LOCK"},
    {QK_MAGIC_CAPS_LOCK_AS_CONTROL_OFF, "QK_MAGIC_CAPS_LOCK_AS_CONTROL_OFF"},
    {QK_MAGIC_CAPS_LOCK_AS_CONTROL_ON, "QK_MAGIC_CAPS_LOCK_AS_CONTROL_ON"},
    {QK_MAGIC_SWAP_LALT_LGUI, "QK_MAGIC_SWAP_LALT_LGUI"},
    {QK_MAGIC_UNSWAP_LALT_LGUI, "QK_MAGIC_UNSWAP_LALT_LGUI"},
    {QK_MAGIC_SWAP_RALT_RGUI, "QK_MAGIC_SWAP_RALT_RGUI"},
    {QK_MAGIC_UNSWAP_RALT_RGUI, "QK_MAGIC_UNSWAP_RALT_RGUI"},
    {QK_MAGIC_GUI_ON, "QK_MAGIC_GUI_ON"},
    {QK_MAGIC_GUI_OFF, "QK_MAGIC_GUI_OFF"},
    {QK_MAGIC_TOGGLE_GUI, "QK_MAGIC_TOGGLE_GUI"},
    {QK_MAGIC_SWAP_GRAVE_ESC, "QK_MAGIC_SWAP_GRAVE_ESC"},
    {QK_MAGIC_UNSWAP_GRAVE_ESC, "QK_MAGIC_UNSWAP_GRAVE_ESC"},
    {QK_MAGIC_SWAP_BACKSLASH_BACKSPACE, "QK_MAGIC_SWAP_BACKSLASH_BACKSPACE"},
    {QK_MAGIC_UNSWAP_BACKSLASH_BACKSPACE, "QK_MAGIC_UNSWAP_BACKSLASH_BACKSPACE"},
    {QK_MAGIC_TOGGLE_BACKSLASH_BACKSPACE, "QK_MAGIC_TOGGLE_BACKSLASH_BACKSPACE"},
    {QK_MAGIC_NKRO_ON, "QK_MAGIC_NKRO_ON"},
    {QK_MAGIC_NKRO_OFF, "QK_MAGIC_NKRO_OFF"},
    {QK_MAGIC_TOGGLE_NKRO, "QK_MAGIC_TOGGLE_NKRO"},
    {QK_MAGIC_SWAP_ALT_GUI, "QK_MAGIC_SWAP_ALT_GUI"},
    {QK_MAGIC_UNSWAP_ALT_GUI, "QK_MAGIC_UNSWAP_ALT_GUI"},
    {QK_MAGIC_TOGGLE_ALT_GUI, "QK_MAGIC_TOGGLE_ALT_GUI"},
    {QK_MAGIC_SWAP_LCTL_LGUI, "QK_MAGIC_SWAP_LCTL_LGUI"},
    {QK_MAGIC_UNSWAP_LCTL_LGUI, "QK_MAGIC_UNSWAP_LCTL_LGUI"},
    {QK_MAGIC_SWAP_RCTL_RGUI, "QK_MAGIC_SWAP_RCTL_RGUI"},
    {QK_MAGIC_UNSWAP_RCTL_RGUI, "QK_MAGIC_UNSWAP_RCTL_RGUI"},
    {QK_MAGIC_SWAP_CTL_GUI, "QK_MAGIC_SWAP_CTL_GUI"},
    {QK_MAGIC_UNSWAP_CTL_GUI, "QK_MAGIC_UNSWAP_CTL_GUI"},
    {QK_MAGIC_TOGGLE_CTL_GUI, "QK_MAGIC_TOGGLE_CTL_GUI"},
    {QK_MAGIC_EE_HANDS_LEFT, "QK_MAGIC_EE_HANDS_LEFT"},
    {QK_MAGIC_EE_HANDS_RIGHT, "QK_MAGIC_EE_HANDS_RIGHT"},
    {QK_MAGIC_SWAP_ESCAPE_CAPS_LOCK, "QK_MAGIC_SWAP_ESCAPE_CAPS_LOCK"},
    {QK_MAGIC_UNSWAP_ESCAPE_CAPS_LOCK, "QK_MAGIC_UNSWAP_ESCAPE_CAPS_LOCK"},
    {QK_MAGIC_TOGGLE_ESCAPE_CAPS_LOCK, "QK_MAGIC_TOGGLE_ESCAPE_CAPS_LOCK"},
    {QK_MIDI_ON, "QK_MIDI_ON"},
    {QK_MIDI_OFF, "QK_MIDI_OFF"},
    {QK_MIDI_TOGGLE, "QK_MIDI_TOGGLE"},
    {QK_MIDI_NOTE_C_0, "QK_MIDI_NOTE_C_0"},
    {QK_MIDI_NOTE_C_SHARP_0, "QK_MIDI_NOTE_C_SHARP_0"},
    {QK_MIDI_NOTE_D_0, "QK_MIDI_NOTE_D_0"},
    {QK_MIDI_NOTE_D_SHARP_0, "QK_MIDI_NOTE_D_SHARP_0"},
    {QK_MIDI_NOTE_E_0, "QK_MIDI_NOTE_E_0"},
    {QK_MIDI_NOTE_F_0, "QK_MIDI_NOTE_F_0"},
    {QK_MIDI_NOTE_F_SHARP_0, "QK_MIDI_NOTE_F_SHARP_0"},
    {QK_MIDI_NOTE_G_0, "QK_MIDI_NOTE_G_0"},
    {QK_MIDI_NOTE_G_SHARP_0, "QK_MIDI_NOTE_G_SHARP_0"},
    {QK_MIDI_NOTE_A_0, "QK_MIDI_NOTE_A_0"},
    {QK_MIDI_NOTE_A_SHARP_0, "QK_MIDI_NOTE_A_SHARP_0"},
    {QK_MIDI_NOTE_B_0, "QK_MIDI_NOTE_B_0"},
    {QK_MIDI_NOTE_C_1, "QK_MIDI_NOTE_C_1"},
    {QK_MIDI_NOTE_C_SHARP_1, "QK_MIDI_NOTE_C_SHARP_1"},
    {QK_MIDI_NOTE_D_1, "QK_MIDI_NOTE_D_1"},
    {QK_MIDI_NOTE_D_SHARP_1, "QK_MIDI_NOTE_D_SHARP_1"},
    {QK_MIDI_NOTE_E_1, "QK_MIDI_NOTE_E_1"},
    {QK_MIDI_NOTE_F_1, "QK_MIDI_NOTE_F_1"},
    {QK_MIDI_NOTE_F_SHARP_1, "QK_MIDI_NOTE_F_SHARP_1"},
    {QK_MIDI_NOTE_G_1, "QK_MIDI_NOTE_G_1"},
    {QK_MIDI_NOTE_G_SHARP_1, "QK_MIDI_NOTE_G_SHARP_1"},
    {QK_MIDI_NOTE_A_1, "QK_MIDI_NOTE_A_1"},
    {QK_MIDI_NOTE_A_SHARP_1, "QK_MIDI_NOTE_A_SHARP_1"},
    {QK_MIDI_NOTE_B_1, "QK_MIDI_NOTE_B_1"},
    {QK_MIDI_NOTE_C_2, "QK_MIDI_NOTE_C_2"},
    {QK_MIDI_NOTE_C_SHARP_2, "QK_MIDI_NOTE_C_SHARP_2"},
    {QK_MIDI_NOTE_D_2, "QK_MIDI_NOTE_D_2"},
    {QK_MIDI_NOTE_D_SHARP_2, "QK_MIDI_NOTE_D_SHARP_2"},
    {QK_MIDI_NOTE_E_2, "QK_MIDI_NOTE_E_2"},
    {QK_MIDI_NOTE_F_2, "QK_MIDI_NOTE_F_2"},
    {QK_MIDI_NOTE_F_SHARP_2, "QK_MIDI_NOTE_F_SHARP_2"},
    {QK_MIDI_NOTE_G_2, "QK_MIDI_NOTE_G_2"},
    {QK_MIDI_NOTE_G_SHARP_2, "QK_MIDI_NOTE_G_SHARP_2"},
    {QK_MIDI_NOTE_A_2, "QK_MIDI_NOTE_A_2"},
    {QK_MIDI_NOTE_A_SHARP_2, "QK_MIDI_NOTE_A_SHARP_2"},
    {QK_MIDI_NOTE_B_2, "QK_MIDI_NOTE_B_2"},
    {QK_MIDI_NOTE_C_3, "QK_MIDI_NOTE_C_3"},
    {QK_MIDI_NOTE_C_SHARP_3, "QK_MIDI_NOTE_C_SHARP_3"},
    {QK_MIDI_NOTE_D_3, "QK_MIDI_NOTE_D_3"},
    {QK_MIDI_NOTE_D_SHARP_3, "QK_MIDI_NOTE_D_SHARP_3"},
    {QK_MIDI_NOTE_E_3, "QK_MIDI_NOTE_E_3"},
    {QK_MIDI_NOTE_F_3, "QK_MIDI_NOTE_F_3"},
    {QK_MIDI_NOTE_F_SHARP_3, "QK_MIDI_NOTE_F_SHARP_3"},
    {QK_MIDI_NOTE_G_3, "QK_MIDI_NOTE_G_3"},
    {QK_MIDI_NOTE_G_SHARP_3, "QK_MIDI_NOTE_G_SHARP_3"},
    {QK_MIDI_NOTE_A_3, "QK_MIDI_NOTE_A_3"},
    {QK_MIDI_NOTE_A_SHARP_3, "QK_MIDI_NOTE_A_SHARP_3"},
    {QK_MIDI_NOTE_B_3, "QK_MIDI_NOTE_B_3"},
    {QK_MIDI_NOTE_C_4, "QK_MIDI_NOTE_C_4"},
    {QK_MIDI_NOTE_C_SHARP_4, "QK_MIDI_NOTE_C_SHARP_4"},
    {QK_MIDI_NOTE_D_4, "QK_MIDI_NOTE_D_4"},
    {QK_MIDI_NOTE_D_SHARP_4, "QK_MIDI_NOTE_D_SHARP_4"},
    {QK_MIDI_NOTE_E_4, "QK_MIDI_NOTE_E_4"},
    {QK_MIDI_NOTE_F_4, "QK_MIDI_NOTE_F_4"},
    {QK_MIDI_NOTE_F_SHARP_4, "QK_MIDI_NOTE_F_SHARP_4"},
    {QK_MIDI_NOTE_G_4, "QK_MIDI_NOTE_G_4"},
    {QK_MIDI_NOTE_G_SHARP_4, "QK_MIDI_NOTE_G_SHARP_4"},
    {QK_MIDI_NOTE_A_4, "QK_MIDI_NOTE_A_4"},
    {QK_MIDI_NOTE_A_SHARP_4, "QK_MIDI_NOTE_A_SHARP_4"},
    {QK_MIDI_NOTE_B_4, "QK_MIDI_NOTE_B_4"},
    {QK_MIDI_NOTE_C_5, "QK_MIDI_NOTE_C_5"},
    {QK_MIDI_NOTE_C_SHARP_5, "QK_MIDI_NOTE_C_SHARP_5"},
    {QK_MIDI_NOTE_D_5, "QK_MIDI_NOTE_D_5"},
    {QK_MIDI_NOTE_D_SHARP_5, "QK_MIDI_NOTE_D_SHARP_5"},
    {QK_MIDI_NOTE_E_5, "QK_MIDI_NOTE_E_5"},
    {QK_MIDI_NOTE_F_5, "QK_MIDI_NOTE_F_5"},
    {QK_MIDI_NOTE_F_SHARP_5, "QK_MIDI_NOTE_F_SHARP_5"},
    {QK_MIDI_NOTE_G_5, "QK_MIDI_NOTE_G_5"},
    {QK_MIDI_NOTE_G_SHARP_5, "QK_MIDI_NOTE_G_SHARP_5"},
    {QK_MIDI_NOTE_A_5, "QK_MIDI_NOTE_A_5"},
    {QK_MIDI_NOTE_A_SHARP_5, "QK_MIDI_NOTE_A_SHARP_5"},
    {QK_MIDI_NOTE_B_5, "QK_MIDI_NOTE_B_5"},
    {QK_MIDI_OCTAVE_N2, "QK_MIDI_OCTAVE_N2"},
    {QK_MIDI_OCTAVE_N1, "QK_MIDI_OCTAVE_N1"},
    {QK_MIDI_OCTAVE_0, "QK_MIDI_OCTAVE_0"},
    {QK_MIDI_OCTAVE_1, "QK_MIDI_OCTAVE_1"},
    {QK_MIDI_OCTAVE_2, "QK_MIDI_OCTAVE_2"},
    {QK_MIDI_OCTAVE_3, "QK_MIDI_OCTAVE_3"},
    {QK_MIDI_OCTAVE_4, "QK_MIDI_OCTAVE_4"},
    {QK_MIDI_OCTAVE_5, "QK_MIDI_OCTAVE_5"},
    {QK_MIDI_OCTAVE_6, "QK_MIDI_OCTAVE_6"},
    {QK_MIDI_OCTAVE_7, "QK_MIDI_OCTAVE_7"},
    {QK_MIDI_OCTAVE_DOWN, "QK_MIDI_OCTAVE_DOWN"},
    {QK_MIDI_OCTAVE_UP, "QK_MIDI_OCTAVE_UP"},
    {QK_MIDI_TRANSPOSE_N6, "QK_MIDI_TRANSPOSE_N6"},
    {QK_MIDI_TRANSPOSE_N5, "QK_MIDI_TRANSPOSE_N5"},
    {QK_MIDI_TRANSPOSE_N4, "QK_MIDI_TRANSPOSE_N4"},
    {QK_MIDI_TRANSPOSE_N3, "QK_MIDI_TRANSPOSE_N3"},
    {QK_MIDI_TRANSPOSE_N2, "QK_MIDI_TRANSPOSE_N2"},
    {QK_MIDI_TRANSPOSE_N1, "QK_MIDI_TRANSPOSE_N1"},
    {QK_MIDI_TRANSPOSE_0, "QK_MIDI_TRANSPOSE_0"},
    {QK_MIDI_TRANSPOSE_1, "QK_MIDI_TRANSPOSE_1"},
    {QK_MIDI_TRANSPOSE_2, "QK_MIDI_TRANSPOSE_2"},
    {QK_MIDI_TRANSPOSE_3, "QK_MIDI_TRANSPOSE_3"},
    {QK_MIDI_TRANSPOSE_4, "QK_MIDI_TRANSPOSE_4"},
    {QK_MIDI_TRANSPOSE_5, "QK_MIDI_TRANSPOSE_5"},
    {QK_MIDI_TRANSPOSE_6, "QK_MIDI_TRANSPOSE_6"},
    {QK_MIDI_TRANSPOSE_DOWN, "QK_MIDI_TRANSPOSE_DOWN"},
    {QK_MIDI_TRANSPOSE_UP, "QK_MIDI_TRANSPOSE_UP"},
    {QK_MIDI_VELOCITY_0, "QK_MIDI_VELOCITY_0"},
    {QK_MIDI_VELOCITY_1, "QK_MIDI_VELOCITY_1"},
    {QK_MIDI_VELOCITY_2, "QK_MIDI_VELOCITY_2"},
    {QK_MIDI_VELOCITY_3, "QK_MIDI_VELOCITY_3"},
    {QK_MIDI_VELOCITY_4, "QK_MIDI_VELOCITY_4"},
    {QK_MIDI_VELOCITY_5, "QK_MIDI_VELOCITY_5"},
    {QK_MIDI_VELOCITY_6, "QK_MIDI_VELOCITY_6"},
    {QK_MIDI_VELOCITY_7, "QK_MIDI_VELOCITY_7"},
    {QK_MIDI_VELOCITY_8, "QK_MIDI_VELOCITY_8"},
    {QK_MIDI_VELOCITY_9, "QK_MIDI_VELOCITY_9"},
    {QK_MIDI_VELOCITY_10, "QK_MIDI_VELOCITY_10"},
    {QK_MIDI_VELOCITY_DOWN, "QK_MIDI_VELOCITY_DOWN"},
    {QK_MIDI_VELOCITY_UP, "QK_MIDI_VELOCITY_UP"},
    {QK_MIDI_CHANNEL_1, "QK_MIDI_CHANNEL_1"},
    {QK_MIDI_CHANNEL_2, "QK_MIDI_CHANNEL_2"},
    {QK_MIDI_CHANNEL_3, "QK_MIDI_CHANNEL_3"},
    {QK_MIDI_CHANNEL_4, "QK_MIDI_CHANNEL_4"},
    {QK_MIDI_CHANNEL_5, "QK_MIDI_CHANNEL_5"},
    {QK_MIDI_CHANNEL_6, "QK_MIDI_CHANNEL_6"},
    {QK_MIDI_CHANNEL_7, "QK_MIDI_CHANNEL_7"},
    {QK_MIDI_CHANNEL_8, "QK_MIDI_CHANNEL_8"},
    {QK_MIDI_CHANNEL_9, "QK_MIDI_CHANNEL_9"},
    {QK_MIDI_CHANNEL_10, "QK_MIDI_CHANNEL_10"},
    {QK_MIDI_CHANNEL_11, "QK_MIDI_CHANNEL_11"},
    {QK_MIDI_CHANNEL_12, "QK_MIDI_CHANNEL_12"},
    {QK_MIDI_CHANNEL_13, "QK_MIDI_CHANNEL_13"},
    {QK_MIDI_CHANNEL_14, "QK_MIDI_CHANNEL_14"},
    {QK_MIDI_CHANNEL_15, "QK_MIDI_CHANNEL_15"},
    {QK_MIDI_CHANNEL_16, "QK_MIDI_CHANNEL_16"},
    {QK_MIDI_CHANNEL_DOWN, "QK_MIDI_CHANNEL_DOWN"},
    {QK_MIDI_CHANNEL_UP, "QK_MIDI_CHANNEL_UP"},
    {QK_MIDI_ALL_NOTES_OFF, "QK_MIDI_ALL_NOTES_OFF"},
    {QK_MIDI_SUSTAIN, "QK_MIDI_SUSTAIN"},
    {QK_MIDI_PORTAMENTO, "QK_MIDI_PORTAMENTO"},
    {QK_MIDI_SOSTENUTO, "QK_MIDI_SOSTENUTO"},
    {QK_MIDI_SOFT, "QK_MIDI_SOFT"},
    {QK_MIDI_LEGATO, "QK_MIDI_LEGATO"},
    {QK_MIDI_MODULATION, "QK_MIDI_MODULATION"},
    {QK_MIDI_MODULATION_SPEED_DOWN, "QK_MIDI_MODULATION_SPEED_DOWN"},
    {QK_MIDI_MODULATION_SPEED_UP, "QK_MIDI_MODULATION_SPEED_UP"},
    {QK_MIDI_PITCH_BEND_DOWN, "QK_MIDI_PITCH_BEND_DOWN"},
    {QK_MIDI_PITCH_BEND_UP, "QK_MIDI_PITCH_BEND_UP"},
    {QK_SEQUENCER_ON, "QK_SEQUENCER_ON"},
    {QK_SEQUENCER_OFF, "QK_SEQUENCER_OFF"},
    {QK_SEQUENCER_TOGGLE, "QK_SEQUENCER_TOGGLE"},
    {QK_SEQUENCER_TEMPO_DOWN, "QK_SEQUENCER_TEMPO_DOWN"},
    {QK_SEQUENCER_TEMPO_UP, "QK_SEQUENCER_TEMPO_UP"},
    {QK_SEQUENCER_RESOLUTION_DOWN, "QK_SEQUENCER_RESOLUTION_DOWN"},
    {QK_SEQUENCER_RESOLUTION_UP, "QK_SEQUENCER_RESOLUTION_UP"},
    {QK_SEQUENCER_STEPS_ALL, "QK_SEQUENCER_STEPS_ALL"},
    {QK_SEQUENCER_STEPS_CLEAR, "QK_SEQUENCER_STEPS_CLEAR"},
    {QK_JOYSTICK_BUTTON_0, "QK_JOYSTICK_BUTTON_0"},
    {QK_JOYSTICK_BUTTON_1, "QK_JOYSTICK_BUTTON_1"},
    {QK_JOYSTICK_BUTTON_2, "QK_JOYSTICK_BUTTON_2"},
    {QK_JOYSTICK_BUTTON_3, "QK_JOYSTICK_BUTTON_3"},
    {QK_JOYSTICK_BUTTON_4, "QK_JOYSTICK_BUTTON_4"},
    {QK_JOYSTICK_BUTTON_5, "QK_JOYSTICK_BUTTON_5"},
    {QK_JOYSTICK_BUTTON_6, "QK_JOYSTICK_BUTTON_6"},
    {QK_JOYSTICK_BUTTON_7, "QK_JOYSTICK_BUTTON_7"},
    {QK_JOYSTICK_BUTTON_8, "QK_JOYSTICK_BUTTON_8"},
    {QK_JOYSTICK_BUTTON_9, "QK_JOYSTICK_BUTTON_9"},
    {QK_JOYSTICK_BUTTON_10, "QK_JOYSTICK_BUTTON_10"},
    {QK_JOYSTICK_BUTTON_11, "QK_JOYSTICK_BUTTON_11"},
    {QK_JOYSTICK_BUTTON_12, "QK_JOYSTICK_BUTTON_12"},
    {QK_JOYSTICK_BUTTON_13, "QK_JOYSTICK_BUTTON_13"},
    {QK_JOYSTICK_BUTTON_14, "QK_JOYSTICK_BUTTON_14"},
    {QK_JOYSTICK_BUTTON_15, "QK_JOYSTICK_BUTTON_15"},
    {QK_JOYSTICK_BUTTON_16, "QK_JOYSTICK_BUTTON_16"},
    {QK_JOYSTICK_BUTTON_17, "QK_JOYSTICK_BUTTON_17"},
    {QK_JOYSTICK_BUTTON_18, "QK_JOYSTICK_BUTTON_18"},
    {QK_JOYSTICK_BUTTON_19, "QK_JOYSTICK_BUTTON_19"},
    {QK_JOYSTICK_BUTTON_20, "QK_JOYSTICK_BUTTON_20"},
    {QK_JOYSTICK_BUTTON_21, "QK_JOYSTICK_BUTTON_21"},
    {QK_JOYSTICK_BUTTON_22, "QK_JOYSTICK_BUTTON_22"},
    {QK_JOYSTICK_BUTTON_23, "QK_JOYSTICK_BUTTON_23"},
    {QK_JOYSTICK_BUTTON_24, "QK_JOYSTICK_BUTTON_24"},
    {QK_JOYSTICK_BUTTON_25, "QK_JOYSTICK_BUTTON_25"},
    {QK_JOYSTICK_BUTTON_26, "QK_JOYSTICK_BUTTON_26"},
    {QK_JOYSTICK_BUTTON_27, "QK_JOYSTICK_BUTTON_27"},
    {QK_JOYSTICK_BUTTON_28, "QK_JOYSTICK_BUTTON_28"},
    {QK_JOYSTICK_BUTTON_29, "QK_JOYSTICK_BUTTON_29"},
    {QK_JOYSTICK_BUTTON_30, "QK_JOYSTICK_BUTTON_30"},
    {QK_JOYSTICK_BUTTON_31, "QK_JOYSTICK_BUTTON_31"},
    {QK_PROGRAMMABLE_BUTTON_1, "QK_PROGRAMMABLE_BUTTON_1"},
    {QK_PROGRAMMABLE_BUTTON_2, "QK_PROGRAMMABLE_BUTTON_2"},
    {QK_PROGRAMMABLE_BUTTON_3, "QK_PROGRAMMABLE_BUTTON_3"},
    {QK_PROGRAMMABLE_BUTTON_4, "QK_PROGRAMMABLE_BUTTON_4"},
    {QK_PROGRAMMABLE_BUTTON_5, "QK_PROGRAMMABLE_BUTTON_5"},
    {QK_PROGRAMMABLE_BUTTON_6, "QK_PROGRAMMABLE_BUTTON_6"},
    {QK_PROGRAMMABLE_BUTTON_7, "QK_PROGRAMMABLE_BUTTON_7"},
    {QK_PROGRAMMABLE_BUTTON_8, "QK_PROGRAMMABLE_BUTTON_8"},
    {QK_PROGRAMMABLE_BUTTON_9, "QK_PROGRAMMABLE_BUTTON_9"},
    {QK_PROGRAMMABLE_BUTTON_10, "QK_PROGRAMMABLE_BUTTON_10"},
    {QK_PROGRAMMABLE_BUTTON_11, "QK_PROGRAMMABLE_BUTTON_11"},
    {QK_PROGRAMMABLE_BUTTON_12, "QK_PROGRAMMABLE_BUTTON_12"},
    {QK_PROGRAMMABLE_BUTTON_13, "QK_PROGRAMMABLE_BUTTON_13"},
    {QK_PROGRAMMABLE_BUTTON_14, "QK_PROGRAMMABLE_BUTTON_14"},
    {QK_PROGRAMMABLE_BUTTON_15, "QK_PROGRAMMABLE_BUTTON_15"},
    {QK_PROGRAMMABLE_BUTTON_16, "QK_PROGRAMMABLE_BUTTON_16"},
    {QK_PROGRAMMABLE_BUTTON_17, "QK_PROGRAMMABLE_BUTTON_17"},
    {QK_PROGRAMMABLE_BUTTON_18, "QK_PROGRAMMABLE_BUTTON_18"},
    {QK_PROGRAMMABLE_BUTTON_19, "QK_PROGRAMMABLE_BUTTON_19"},
    {QK_PROGRAMMABLE_BUTTON_20, "QK_PROGRAMMABLE_BUTTON_20"},
    {QK_PROGRAMMABLE_BUTTON_21, "QK_PROGRAMMABLE_BUTTON_21"},
    {QK_PROGRAMMABLE_BUTTON_22, "QK_PROGRAMMABLE_BUTTON_22"},
    {QK_PROGRAMMABLE_BUTTON_23, "QK_PROGRAMMABLE_BUTTON_23"},
    {QK_PROGRAMMABLE_BUTTON_24, "QK_PROGRAMMABLE_BUTTON_24"},
    {QK_PROGRAMMABLE_BUTTON_25, "QK_PROGRAMMABLE_BUTTON_25"},
    {QK_PROGRAMMABLE_BUTTON_26, "QK_PROGRAMMABLE_BUTTON_26"},
    {QK_PROGRAMMABLE_BUTTON_27, "QK_PROGRAMMABLE_BUTTON_27"},
    {QK_PROGRAMMABLE_BUTTON_28, "QK_PROGRAMMABLE_BUTTON_28"},
    {QK_PROGRAMMABLE_BUTTON_29, "QK_PROGRAMMABLE_BUTTON_29"},
    {QK_PROGRAMMABLE_BUTTON_30, "QK_PROGRAMMABLE_BUTTON_30"},
    {QK_PROGRAMMABLE_BUTTON_31, "QK_PROGRAMMABLE_BUTTON_31"},
    {QK_PROGRAMMABLE_BUTTON_32, "QK_PROGRAMMABLE_BUTTON_32"},
    {QK_AUDIO_ON, "QK_AUDIO_ON"},
    {QK_AUDIO_OFF, "QK_AUDIO_OFF"},
    {QK_AUDIO_TOGGLE, "QK_AUDIO_TOGGLE"},
    {QK_AUDIO_CLICKY_TOGGLE, "QK_AUDIO_CLICKY_TOGGLE"},
    {QK_AUDIO_CLICKY_ON, "QK_AUDIO_CLICKY_ON"},
    {QK_AUDIO_CLICKY_OFF, "QK_AUDIO_CLICKY_OFF"},
    {QK_AUDIO_CLICKY_UP, "QK_AUDIO_CLICKY_UP"},
    {QK_AUDIO_CLICKY_DOWN, "QK_AUDIO_CLICKY_DOWN"},
    {QK_AUDIO_CLICKY_RESET, "QK_AUDIO_CLICKY_RESET"},
    {QK_MUSIC_ON, "QK_MUSIC_ON"},
    {QK_MUSIC_OFF, "QK_MUSIC_OFF"},
    {QK_MUSIC_TOGGLE, "QK_MUSIC_TOGGLE"},
    {QK_MUSIC_MODE_NEXT, "QK_MUSIC_MODE_NEXT"},
    {QK_AUDIO_VOICE_NEXT, "QK_AUDIO_VOICE_NEXT"},
    {QK_AUDIO_VOICE_PREVIOUS, "QK_AUDIO_VOICE_PREVIOUS"},
    {QK_STENO_BOLT, "QK_STENO_BOLT"},
    {QK_STENO_GEMINI, "QK_STENO_GEMINI"},
    {QK_STENO_COMB, "QK_STENO_COMB"},
    {QK_STENO_COMB_MAX, "QK_STENO_COMB_MAX"},
    {QK_MACRO_0, "QK_MACRO_0"},
    {QK_MACRO_1, "QK_MACRO_1"},
    {QK_MACRO_2, "QK_MACRO_2"},
    {QK_MACRO_3, "QK_MACRO_3"},
    {QK_MACRO_4, "QK_MACRO_4"},
    {QK_MACRO_5, "QK_MACRO_5"},
    {QK_MACRO_6, "QK_MACRO_6"},
    {QK_MACRO_7, "QK_MACRO_7"},
    {QK_MACRO_8, "QK_MACRO_8"},
    {QK_MACRO_9, "QK_MACRO_9"},
    {QK_MACRO_10, "QK_MACRO_10"},
    {QK_MACRO_11, "QK_MACRO_11"},
    {QK_MACRO_12, "QK_MACRO_12"},
    {QK_MACRO_13, "QK_MACRO_13"},
    {QK_MACRO_14, "QK_MACRO_14"},
    {QK_MACRO_15, "QK_MACRO_15"},
    {QK_MACRO_16, "QK_MACRO_16"},
    {QK_MACRO_17, "QK_MACRO_17"},
    {QK_MACRO_18, "QK_MACRO_18"},
    {QK_MACRO_19, "QK_MACRO_19"},
    {QK_MACRO_20, "QK_MACRO_20"},
    {QK_MACRO_21, "QK_MACRO_21"},
    {QK_MACRO_22, "QK_MACRO_22"},
    {QK_MACRO_23, "QK_MACRO_23"},
    {QK_MACRO_24, "QK_MACRO_24"},
    {QK_MACRO_25, "QK_MACRO_25"},
    {QK_MACRO_26, "QK_MACRO_26"},
    {QK_MACRO_27, "QK_MACRO_27"},
    {QK_MACRO_28, "QK_MACRO_28"},
    {QK_MACRO_29, "QK_MACRO_29"},
    {QK_MACRO_30, "QK_MACRO_30"},
    {QK_MACRO_31, "QK_MACRO_31"},
    {QK_BACKLIGHT_ON, "QK_BACKLIGHT_ON"},
    {QK_BACKLIGHT_OFF, "QK_BACKLIGHT_OFF"},
    {QK_BACKLIGHT_TOGGLE, "QK_BACKLIGHT_TOGGLE"},
    {QK_BACKLIGHT_DOWN, "QK_BACKLIGHT_DOWN"},
    {QK_BACKLIGHT_UP, "QK_BACKLIGHT_UP"},
    {QK_BACKLIGHT_STEP, "QK_BACKLIGHT_STEP"},
    {QK_BACKLIGHT_TOGGLE_BREATHING, "QK_BACKLIGHT_TOGGLE_BREATHING"},
    {QK_LED_MATRIX_ON, "QK_LED_MATRIX_ON"},
    {QK_LED_MATRIX_OFF, "QK_LED_MATRIX_OFF"},
    {QK_LED_MATRIX_TOGGLE, "QK_LED_MATRIX_TOGGLE"},
    {QK_LED_MATRIX_MODE_NEXT, "QK_LED_MATRIX_MODE_NEXT"},
    {QK_LED_MATRIX_MODE_PREVIOUS, "QK_LED_MATRIX_MODE_PREVIOUS"},
    {QK_LED_MATRIX_BRIGHTNESS_UP, "QK_LED_MATRIX_BRIGHTNESS_UP"},
    {QK_LED_MATRIX_BRIGHTNESS_DOWN, "QK_LED_MATRIX_BRIGHTNESS_DOWN"},
    {QK_LED_MATRIX_SPEED_UP, "QK_LED_MATRIX_SPEED_UP"},
    {QK_LED_MATRIX_SPEED_DOWN, "QK_LED_MATRIX_SPEED_DOWN"},
    {QK_UNDERGLOW_TOGGLE, "QK_UNDERGLOW_TOGGLE"},
    {QK_UNDERGLOW_MODE_NEXT, "QK_UNDERGLOW_MODE_NEXT"},
    {QK_UNDERGLOW_MODE_PREVIOUS, "QK_UNDERGLOW_MODE_PREVIOUS"},
    {QK_UNDERGLOW_HUE_UP, "QK_UNDERGLOW_HUE_UP"},
    {QK_UNDERGLOW_HUE_DOWN, "QK_UNDERGLOW_HUE_DOWN"},
    {QK_UNDERGLOW_SATURATION_UP, "QK_UNDERGLOW_SATURATION_UP"},
    {QK_UNDERGLOW_SATURATION_DOWN, "QK_UNDERGLOW_SATURATION_DOWN"},
    {QK_UNDERGLOW_VALUE_UP, "QK_UNDERGLOW_VALUE_UP"},
    {QK_UNDERGLOW_VALUE_DOWN, "QK_UNDERGLOW_VALUE_DOWN"},
    {QK_UNDERGLOW_SPEED_UP, "QK_UNDERGLOW_SPEED_UP"},
    {QK_UNDERGLOW_SPEED_DOWN, "QK_UNDERGLOW_SPEED_DOWN"},
    {RGB_MODE_PLAIN, "RGB_MODE_PLAIN"},
    {RGB_MODE_BREATHE, "RGB_MODE_BREATHE"},
    {RGB_MODE_RAINBOW, "RGB_MODE_RAINBOW"},
    {RGB_MODE_SWIRL, "RGB_MODE_SWIRL"},
    {RGB_MODE_SNAKE, "RGB_MODE_SNAKE"},
    {RGB_MODE_KNIGHT, "RGB_MODE_KNIGHT"},
    {RGB_MODE_XMAS, "RGB_MODE_XMAS"},
    {RGB_MODE_GRADIENT, "RGB_MODE_GRADIENT"},
    {RGB_MODE_RGBTEST, "RGB_MODE_RGBTEST"},
    {RGB_MODE_TWINKLE, "RGB_MODE_TWINKLE"},
    {QK_RGB_MATRIX_ON, "QK_RGB_MATRIX_ON"},
    {QK_RGB_MATRIX_OFF, "QK_RGB_MATRIX_OFF"},
    {QK_RGB_MATRIX_TOGGLE, "QK_RGB_MATRIX_TOGGLE"},
    {QK_RGB_MATRIX_MODE_NEXT, "QK_RGB_MATRIX_MODE_NEXT"},
    {QK_RGB_MATRIX_MODE_PREVIOUS, "QK_RGB_MATRIX_MODE_PREVIOUS"},
    {QK_RGB_MATRIX_HUE_UP, "QK_RGB_MATRIX_HUE_UP"},
    {QK_RGB_MATRIX_HUE_DOWN, "QK_RGB_MATRIX_HUE_DOWN"},
    {QK_RGB_MATRIX_SATURATION_UP, "QK_RGB_MATRIX_SATURATION_UP"},
    {QK_RGB_MATRIX_SATURATION_DOWN, "QK_RGB_MATRIX_SATURATION_DOWN"},
    {QK_RGB_MATRIX_VALUE_UP, "QK_RGB_MATRIX_VALUE_UP"},
    {QK_RGB_MATRIX_VALUE_DOWN, "QK_RGB_MATRIX_VALUE_DOWN"},
    {QK_RGB_MATRIX_SPEED_UP, "QK_RGB_MATRIX_SPEED_UP"},
    {QK_RGB_MATRIX_SPEED_DOWN, "QK_RGB_MATRIX_SPEED_DOWN"},
    {QK_BOOTLOADER, "QK_BOOTLOADER"},
    {QK_REBOOT, "QK_REBOOT"},
    {QK_DEBUG_TOGGLE, "QK_DEBUG_TOGGLE"},
    {QK_CLEAR_EEPROM, "QK_CLEAR_EEPROM"},
    {QK_MAKE, "QK_MAKE"},
    {QK_AUTO_SHIFT_DOWN, "QK_AUTO_SHIFT_DOWN"},
    {QK_AUTO_SHIFT_UP, "QK_AUTO_SHIFT_UP"},
    {QK_AUTO_SHIFT_REPORT, "QK_AUTO_SHIFT_REPORT"},
    {QK_AUTO_SHIFT_ON, "QK_AUTO_SHIFT_ON"},
    {QK_AUTO_SHIFT_OFF, "QK_AUTO_SHIFT_OFF"},
    {QK_AUTO_SHIFT_TOGGLE, "QK_AUTO_SHIFT_TOGGLE"},
    {QK_GRAVE_ESCAPE, "QK_GRAVE_ESCAPE"},
    {QK_VELOCIKEY_TOGGLE, "QK_VELOCIKEY_TOGGLE"},
    {QK_SPACE_CADET_LEFT_CTRL_PARENTHESIS_OPEN, "QK_SPACE_CADET_LEFT_CTRL_PARENTHESIS_OPEN"},
    {QK_SPACE_CADET_RIGHT_CTRL_PARENTHESIS_CLOSE, "QK_SPACE_CADET_RIGHT_CTRL_PARENTHESIS_CLOSE"},
    {QK_SPACE_CADET_LEFT_SHIFT_PARENTHESIS_OPEN, "QK_SPACE_CADET_LEFT_SHIFT_PARENTHESIS_OPEN"},
    {QK_SPACE_CADET_RIGHT_SHIFT_PARENTHESIS_CLOSE, "QK_SPACE_CADET_RIGHT_SHIFT_PARENTHESIS_CLOSE"},
    {QK_SPACE_CADET_LEFT_ALT_PARENTHESIS_OPEN, "QK_SPACE_CADET_LEFT_ALT_PARENTHESIS_OPEN"},
    {QK_SPACE_CADET_RIGHT_ALT_PARENTHESIS_CLOSE, "QK_SPACE_CADET_RIGHT_ALT_PARENTHESIS_CLOSE"},
    {QK_SPACE_CADET_RIGHT_SHIFT_ENTER, "QK_SPACE_CADET_RIGHT_SHIFT_ENTER"},
    {QK_OUTPUT_AUTO, "QK_OUTPUT_AUTO"},
    {QK_OUTPUT_USB, "QK_OUTPUT_USB"},
    {QK_OUTPUT_BLUETOOTH, "QK_OUTPUT_BLUETOOTH"},
    {QK_UNICODE_MODE_NEXT, "QK_UNICODE_MODE_NEXT"},
    {QK_UNICODE_MODE_PREVIOUS, "QK_UNICODE_MODE_PREVIOUS"},
    {QK_UNICODE_MODE_MACOS, "QK_UNICODE_MODE_MACOS"},
    {QK_UNICODE_MODE_LINUX, "QK_UNICODE_MODE_LINUX"},
    {QK_UNICODE_MODE_WINDOWS, "QK_UNICODE_MODE_WINDOWS"},
    {QK_UNICODE_MODE_BSD, "QK_UNICODE_MODE_BSD"},
    {QK_UNICODE_MODE_WINCOMPOSE, "QK_UNICODE_MODE_WINCOMPOSE"},
    {QK_UNICODE_MODE_EMACS, "QK_UNICODE_MODE_EMACS"},
    {QK_HAPTIC_ON, "QK_HAPTIC_ON"},
    {QK_HAPTIC_OFF, "QK_HAPTIC_OFF"},
    {QK_HAPTIC_TOGGLE, "QK_HAPTIC_TOGGLE"},
    {QK_HAPTIC_RESET, "QK_HAPTIC_RESET"},
    {QK_HAPTIC_FEEDBACK_TOGGLE, "QK_HAPTIC_FEEDBACK_TOGGLE"},
    {QK_HAPTIC_BUZZ_TOGGLE, "QK_HAPTIC_BUZZ_TOGGLE"},
    {QK_HAPTIC_MODE_NEXT, "QK_HAPTIC_MODE_NEXT"},
    {QK_HAPTIC_MODE_PREVIOUS, "QK_HAPTIC_MODE_PREVIOUS"},
    {QK_HAPTIC_CONTINUOUS_TOGGLE, "QK_HAPTIC_CONTINUOUS_TOGGLE"},
    {QK_HAPTIC_CONTINUOUS_UP, "QK_HAPTIC_CONTINUOUS_UP"},
    {QK_HAPTIC_CONTINUOUS_DOWN, "QK_HAPTIC_CONTINUOUS_DOWN"},
    {QK_HAPTIC_DWELL_UP, "QK_HAPTIC_DWELL_UP"},
    {QK_HAPTIC_DWELL_DOWN, "QK_HAPTIC_DWELL_DOWN"},
    {QK_COMBO_ON, "QK_COMBO_ON"},
    {QK_COMBO_OFF, "QK_COMBO_OFF"},
    {QK_COMBO_TOGGLE, "QK_COMBO_TOGGLE"},
    {QK_DYNAMIC_MACRO_RECORD_START_1, "QK_DYNAMIC_MACRO_RECORD_START_1"},
    {QK_DYNAMIC_MACRO_RECORD_START_2, "QK_DYNAMIC_MACRO_RECORD_START_2"},
    {QK_DYNAMIC_MACRO_RECORD_STOP, "QK_DYNAMIC_MACRO_RECORD_STOP"},
    {QK_DYNAMIC_MACRO_PLAY_1, "QK_DYNAMIC_MACRO_PLAY_1"},
    {QK_DYNAMIC_MACRO_PLAY_2, "QK_DYNAMIC_MACRO_PLAY_2"},
    {QK_LEADER, "QK_LEADER"},
    {QK_LOCK, "QK_LOCK"},
    {QK_ONE_SHOT_ON, "QK_ONE_SHOT_ON"},
    {QK_ONE_SHOT_OFF, "QK_ONE_SHOT_OFF"},
    {QK_ONE_SHOT_TOGGLE, "QK_ONE_SHOT_TOGGLE"},
    {QK_KEY_OVERRIDE_TOGGLE, "QK_KEY_OVERRIDE_TOGGLE"},
    {QK_KEY_OVERRIDE_ON, "QK_KEY_OVERRIDE_ON"},
    {QK_KEY_OVERRIDE_OFF, "QK_KEY_OVERRIDE_OFF"},
    {QK_SECURE_LOCK, "QK_SECURE_LOCK"},
    {QK_SECURE_UNLOCK, "QK_SECURE_UNLOCK"},
    {QK_SECURE_TOGGLE, "QK_SECURE_TOGGLE"},
    {QK_SECURE_REQUEST, "QK_SECURE_REQUEST"},
    {QK_DYNAMIC_TAPPING_TERM_PRINT, "QK_DYNAMIC_TAPPING_TERM_PRINT"},
    {QK_DYNAMIC_TAPPING_TERM_UP, "QK_DYNAMIC_TAPPING_TERM_UP"},
    {QK_DYNAMIC_TAPPING_TERM_DOWN, "QK_DYNAMIC_TAPPING_TERM_DOWN"},
    {QK_CAPS_WORD_TOGGLE, "QK_CAPS_WORD_TOGGLE"},
    {QK_AUTOCORRECT_ON, "QK_AUTOCORRECT_ON"},
    {QK_AUTOCORRECT_OFF, "QK_AUTOCORRECT_OFF"},
    {QK_AUTOCORRECT_TOGGLE, "QK_AUTOCORRECT_TOGGLE"},
    {QK_TRI_LAYER_LOWER, "QK_TRI_LAYER_LOWER"},
    {QK_TRI_LAYER_UPPER, "QK_TRI_LAYER_UPPER"},
    {QK_REPEAT_KEY, "QK_REPEAT_KEY"},
    {QK_ALT_REPEAT_KEY, "QK_ALT_REPEAT_KEY"},
    {QK_KB_0, "QK_KB_0"},
    {QK_KB_1, "QK_KB_1"},
    {QK_KB_2, "QK_KB_2"},
    {QK_KB_3, "QK_KB_3"},
    {QK_KB_4, "QK_KB_4"},
    {QK_KB_5, "QK_KB_5"},
    {QK_KB_6, "QK_KB_6"},
    {QK_KB_7, "QK_KB_7"},
    {QK_KB_8, "QK_KB_8"},
    {QK_KB_9, "QK_KB_9"},
    {QK_KB_10, "QK_KB_10"},
    {QK_KB_11, "QK_KB_11"},
    {QK_KB_12, "QK_KB_12"},
    {QK_KB_13, "QK_KB_13"},
    {QK_KB_14, "QK_KB_14"},
    {QK_KB_15, "QK_KB_15"},
    {QK_KB_16, "QK_KB_16"},
    {QK_KB_17, "QK_KB_17"},
    {QK_KB_18, "QK_KB_18"},
    {QK_KB_19, "QK_KB_19"},
    {QK_KB_20, "QK_KB_20"},
    {QK_KB_21, "QK_KB_21"},
    {QK_KB_22, "QK_KB_22"},
    {QK_KB_23, "QK_KB_23"},
    {QK_KB_24, "QK_KB_24"},
    {QK_KB_25, "QK_KB_25"},
    {QK_KB_26, "QK_KB_26"},
    {QK_KB_27, "QK_KB_27"},
    {QK_KB_28, "QK_KB_28"},
    {QK_KB_29, "QK_KB_29"},
    {QK_KB_30, "QK_KB_30"},
    {QK_KB_31, "QK_KB_31"},
    {QK_USER_0, "QK_USER_0"},
    {QK_USER_1, "QK_USER_1"},
    {QK_USER_2, "QK_USER_2"},
    {QK_USER_3, "QK_USER_3"},
    {QK_USER_4, "QK_USER_4"},
    {QK_USER_5, "QK_USER_5"},
    {QK_USER_6, "QK_USER_6"},
    {QK_USER_7, "QK_USER_7"},
    {QK_USER_8, "QK_USER_8"},
    {QK_USER_9, "QK_USER_9"},
    {QK_USER_10, "QK_USER_10"},
    {QK_USER_11, "QK_USER_11"},
    {QK_USER_12, "QK_USER_12"},
    {QK_USER_13, "QK_USER_13"},
    {QK_USER_14, "QK_USER_14"},
    {QK_USER_15, "QK_USER_15"},
    {QK_USER_16, "QK_USER_16"},
    {QK_USER_17, "QK_USER_17"},
    {QK_USER_18, "QK_USER_18"},
    {QK_USER_19, "QK_USER_19"},
    {QK_USER_20, "QK_USER_20"},
    {QK_USER_21, "QK_USER_21"},
    {QK_USER_22, "QK_USER_22"},
    {QK_USER_23, "QK_USER_23"},
    {QK_USER_24, "QK_USER_24"},
    {QK_USER_25, "QK_USER_25"},
    {QK_USER_26, "QK_USER_26"},
    {QK_USER_27, "QK_USER_27"},
    {QK_USER_28, "QK_USER_28"},
    {QK_USER_29, "QK_USER_29"},
    {QK_USER_30, "QK_USER_30"},
    {QK_USER_31, "QK_USER_31"},
};
