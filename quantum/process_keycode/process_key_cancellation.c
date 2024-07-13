// Copyright 2024 Harrison Chan (@xelus22)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_key_cancellation.h"
#include <string.h>
#include "keycodes.h"
#include "keycode_config.h"
#include "action_util.h"
#include "keymap_introspection.h"
#include "debug.h"

// Max 10 since we only have 10 fingers to press keys
#define KEYREPORT_BUFFER_SIZE 10

_Static_assert(KEYREPORT_BUFFER_SIZE <= 16, "KEYREPORT_BUFFER_SIZE must be less than or equal to 16 due to bitfield usage");

// key interrupt up stroke buffer
uint16_t buffer_keyreports[KEYREPORT_BUFFER_SIZE];

// track the next free index
int buffer_keyreport_count = 0;

/**
 * @brief function for querying the enabled state of key cancellation
 *
 * @return true if enabled
 * @return false if disabled
 */
bool key_cancellation_is_enabled(void) {
    return keymap_config.key_cancellation_enable;
}

/**
 * @brief Enables key cancellation and saves state to eeprom
 *
 */
void key_cancellation_enable(void) {
    keymap_config.key_cancellation_enable = true;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief Disables key cancellation and saves state to eeprom
 *
 */
void key_cancellation_disable(void) {
    keymap_config.key_cancellation_enable = false;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief Toggles key cancellation's status and save state to eeprom
 *
 */
void key_cancellation_toggle(void) {
    keymap_config.key_cancellation_enable = !keymap_config.key_cancellation_enable;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief function for querying the enabled state of key interrupt recovery
 *
 * @return true if enabled
 * @return false if disabled
 */
bool key_cancellation_recovery_is_enabled(void) {
    return keymap_config.key_cancellation_enable && keymap_config.key_cancellation_recovery_enable;
}

/**
 * @brief Enables key interrupt recovery and saves state to eeprom
 *
 */
void key_cancellation_recovery_enable(void) {
    keymap_config.key_cancellation_recovery_enable = true;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief Disables key interrupt recovery and saves state to eeprom
 *
 */
void key_cancellation_recovery_disable(void) {
    keymap_config.key_cancellation_recovery_enable = false;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief Toggles key interrupt recovery's status and save state to eeprom
 *
 */
void key_cancellation_recovery_toggle(void) {
    keymap_config.key_cancellation_recovery_enable = !keymap_config.key_cancellation_recovery_enable;
    eeconfig_update_keymap(keymap_config.raw);
}

/**
 * @brief handler for user to override whether key cancellation should process this keypress
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @return true Allow key cancellation
 * @return false Stop processing and escape from key cancellation
 */
__attribute__((weak)) bool process_key_cancellation_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

// check if key already in buffer
int get_key_index_in_buffer(uint16_t keycode) {
        for (int i = 0; i < buffer_keyreport_count; i++) {
        if (buffer_keyreports[i] == keycode) {
            ac_dprintf("Key Interrupt: Found Keycode <%d> index <%d>\n", keycode, i);
            return i;
        }
    }
    return -1;
}

void add_key_buffer(uint16_t keycode) {
    if (get_key_index_in_buffer(keycode) > 0) {
        ac_dprintf("Key Interrupt: %d Key already in buffer\n", keycode);
        return;
    }

    // sanity check don't write past the buffer size
    if (buffer_keyreport_count >= KEYREPORT_BUFFER_SIZE) {
        ac_dprintf("Key Interrupt: Buffer full\n");
        return;
    }

    buffer_keyreports[buffer_keyreport_count] = keycode;
    buffer_keyreport_count++;

    ac_dprintf("Key Interrupt: Added <%d>\n", keycode);
}

// remove keycode and shift buffer
void del_key_buffer(uint16_t keycode) {
    for (int i = 0; i < buffer_keyreport_count; i++) {
        if (buffer_keyreports[i] == keycode) {
            for (int j = i; j < buffer_keyreport_count - 1; j++) {
                buffer_keyreports[j] = buffer_keyreports[j + 1];
            }
            buffer_keyreport_count--;
            break;
        }
    }
    ac_dprintf("Key Interrupt: Added <%d>\n", keycode);
}

// check if keycode is in the interrupt press list
bool key_cancellation_is_key_in_press_list(uint16_t keycode) {
    for (int i = 0; i < key_cancellation_count(); i++) {
        if (key_cancellation_get(i).press == keycode) {
            ac_dprintf("Key Interrupt: Keycode <%d> in key_cancellation_list\n", keycode);
            return true;
        }
    }
    return false;
}

/**
 * @brief Process handler for key_cancellation feature
 *
 * @param keycode Keycode registered by matrix press, per keymap
 * @param record keyrecord_t structure
 * @return true Continue processing keycodes, and send to host
 * @return false Stop processing keycodes, and don't send to host
 */
bool process_key_cancellation(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case QK_KEY_CANCELLATION_ON:
                key_cancellation_enable();
                return false;
            case QK_KEY_CANCELLATION_OFF:
                key_cancellation_disable();
                return false;
            case QK_KEY_CANCELLATION_TOGGLE:
                key_cancellation_toggle();
                return false;
            case QK_KEY_CANCELLATION_RECOVERY_ON:
                key_cancellation_recovery_enable();
                return false;
            case QK_KEY_CANCELLATION_RECOVERY_OFF:
                key_cancellation_recovery_disable();
                return false;
            case QK_KEY_CANCELLATION_RECOVERY_TOGGLE:
                key_cancellation_recovery_toggle();
                return false;
            default:
                break;
        }
    }

    if (!keymap_config.key_cancellation_enable) {
        return true;
    }

    // only supports basic keycodes
    if (!IS_BASIC_KEYCODE(keycode)) {
        return true;
    }

    // custom user hook
    if (!process_key_cancellation_user(keycode, record)) {
        return true;
    }

   // if key interrupt recovery is not enabled then do not process key up events
    if (!keymap_config.key_cancellation_recovery_enable && !record->event.pressed) {
        return true;
    }

    // only key interrupt to buffer if required
    if (keymap_config.key_cancellation_recovery_enable) {
        if (key_cancellation_is_key_in_press_list(keycode)) {
            if (record->event.pressed) {
                add_key_buffer(keycode);
            } else {
                del_key_buffer(keycode);
            }
        }

        if (buffer_keyreport_count == 0) {
            return true;
        }
    }

    ac_dprintf("buffer_keyreport_count: %d\n", buffer_keyreport_count);

    if (record->event.pressed) {
        for (int i = 0; i < key_cancellation_count(); i++) {
            key_cancellation_t key_cancellation = key_cancellation_get(i);
            if (keycode == key_cancellation.press) {
                del_key(key_cancellation.unpress);
            }
        }
    } else {
        uint16_t bitfield_keyreports         = 0xFF << (16 - buffer_keyreport_count);
        uint16_t bitfield_keyreports_scratch = bitfield_keyreports;

        for (int j = buffer_keyreport_count - 1; j >= 0; j--) {
            uint16_t current_bitmask = 1 << (16 - j);
            // skip if bit is not set
            if (!(bitfield_keyreports_scratch & current_bitmask)) {
                continue;
            }
            for (int i = 0; i < key_cancellation_count(); i++) {
                key_cancellation_t key_cancellation = key_cancellation_get(i);
                // if key in buffer is the same as the key interrupt press
                if (key_cancellation.press == buffer_keyreports[j]) {
                    // if key interrupt unpress is in buffer
                    int index = get_key_index_in_buffer(key_cancellation.unpress);
                    if (index > 0) {
                        // remove key interrupt unpress from buffer
                        bitfield_keyreports_scratch &= ~(1 << (16 - index));
                    }
                }
            }
        }

        // compare buffer and temp buffer
        uint16_t comparison = bitfield_keyreports ^ bitfield_keyreports_scratch;

        // bits that are 1 means it is different
        // if there are differences and bit in bitfield_keyreports_scratch is 0, then del key
        // if there are no differences then add key

        // compare buffer and temp buffer
        for (int i = 0; i < buffer_keyreport_count; i++) {
            uint16_t bitmask = 1 << (16 - i);
            if (comparison & bitmask) {
                if (~(bitfield_keyreports_scratch & bitmask)) {
                    del_key(buffer_keyreports[i]);
                }
            } else {
                add_key(buffer_keyreports[i]);
            }
        }
    }

    return true;
}
