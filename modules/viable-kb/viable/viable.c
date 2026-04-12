// Copyright 2025 Ira Cooper <ira@wakeful.net>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "viable.h"
#include "quantum.h"
#include "via.h"
#include "raw_hid.h"
#include "eeprom.h"
#include <string.h>
#include "print.h"
#include "version.h"
#include "eeconfig.h"
#include "nvm_eeprom_eeconfig_internal.h"
#include "nvm_eeprom_via_internal.h"
#include "keymap_introspection.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

// Magic position for keycode execution
#define VIABLE_MATRIX_MAGIC 240

// Global for keycode override during tap dance execution
uint16_t g_viable_magic_keycode_override;

// Internal EEPROM access functions - uses eeconfig_kb_datablock
__attribute__((weak)) void viable_read_eeprom(uint16_t offset, void *buf, uint16_t size) {
        void *ee_start = (void *)(uintptr_t)(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR + offset);
        void *ee_end   = (void *)(uintptr_t)(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR + MIN(VIABLE_EEPROM_SIZE_CALC, offset + size));
        // xprintf("EEPROM read: offset=%p size=%p\n", ee_start, ee_end);
        eeprom_read_block(buf, ee_start, ee_end - ee_start);
}

__attribute__((weak)) void viable_write_eeprom(uint16_t offset, const void *buf, uint16_t size) {
       void *ee_start = (void *)(uintptr_t)(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR + offset);
       void *ee_end   = (void *)(uintptr_t)(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR + MIN(VIABLE_EEPROM_SIZE_CALC, offset + size));
       eeprom_update_block(buf, ee_start, ee_end - ee_start);
}

// Magic header for EEPROM validation - derived from QMK_BUILDDATE
// QMK_BUILDDATE format: "2019-11-05-11:29:54"
// Use full timestamp (date + time) so every build gets unique magic
static void viable_get_magic(uint8_t *magic) {
    char *p = QMK_BUILDDATE;
    magic[0] = ((p[2] & 0x0F) << 4) | (p[3] & 0x0F);  // year low 2 digits
    magic[1] = ((p[5] & 0x0F) << 4) | (p[6] & 0x0F);  // month
    magic[2] = ((p[8] & 0x0F) << 4) | (p[9] & 0x0F);  // day
    magic[3] = ((p[11] & 0x0F) << 4) | (p[12] & 0x0F); // hour
    magic[4] = ((p[14] & 0x0F) << 4) | (p[15] & 0x0F); // minute
    magic[5] = ((p[17] & 0x0F) << 4) | (p[18] & 0x0F); // second
}

static bool viable_eeprom_is_valid(void) {
    uint8_t stored[VIABLE_MAGIC_SIZE];
    uint8_t expected[VIABLE_MAGIC_SIZE];
    viable_read_eeprom(VIABLE_MAGIC_OFFSET, stored, VIABLE_MAGIC_SIZE);
    viable_get_magic(expected);
    return memcmp(stored, expected, VIABLE_MAGIC_SIZE) == 0;
}

static void viable_eeprom_set_valid(void) {
    uint8_t magic[VIABLE_MAGIC_SIZE];
    viable_get_magic(magic);
    viable_write_eeprom(VIABLE_MAGIC_OFFSET, magic, VIABLE_MAGIC_SIZE);
}

void viable_init(void) {
    // Check if EEPROM data is valid (matches current firmware version)
    if (!viable_eeprom_is_valid()) {
        // Reset all viable data to defaults
        viable_reset();
        viable_qmk_settings_reset();
        // Mark as valid
        viable_eeprom_set_valid();
    }

    viable_reload_tap_dance();
    viable_reload_combo();
    viable_reload_key_override();
    viable_reload_alt_repeat_key();
    viable_qmk_settings_init();
}

// Weak keyboard post-init hook
__attribute__((weak)) void keyboard_post_init_viable_kb(void) {}

// Module hook for post-init
void keyboard_post_init_viable(void) {
    keyboard_post_init_viable_kb();
    viable_init();
}

// Override QMK's get_oneshot_timeout for runtime configuration
// TEMPORARILY DISABLED - may be called before EEPROM ready
// uint16_t get_oneshot_timeout(void) {
//     viable_one_shot_t settings;
//     viable_get_one_shot(&settings);
//     return settings.timeout;
// }

// Get feature flags based on what's enabled
uint8_t viable_get_feature_flags(void) {
    uint8_t flags = 0;
#ifdef CAPS_WORD_ENABLE
    flags |= viable_flag_caps_word;
#endif
#ifdef LAYER_LOCK_ENABLE
    flags |= viable_flag_layer_lock;
#endif
#ifdef ONESHOT_ENABLE
    flags |= viable_flag_oneshot;
#endif
    return flags;
}

// Storage functions - Tap Dance
int viable_get_tap_dance(uint8_t index, viable_tap_dance_entry_t *entry) {
    if (index >= VIABLE_TAP_DANCE_ENTRIES) return -1;
    viable_read_eeprom(VIABLE_TAP_DANCE_OFFSET + index * sizeof(viable_tap_dance_entry_t),
                       entry, sizeof(viable_tap_dance_entry_t));
    return 0;
}

int viable_set_tap_dance(uint8_t index, const viable_tap_dance_entry_t *entry) {
    if (index >= VIABLE_TAP_DANCE_ENTRIES) return -1;
    viable_write_eeprom(VIABLE_TAP_DANCE_OFFSET + index * sizeof(viable_tap_dance_entry_t),
                        entry, sizeof(viable_tap_dance_entry_t));
    return 0;
}

// Storage functions - Combo
int viable_get_combo(uint8_t index, viable_combo_entry_t *entry) {
    if (index >= VIABLE_COMBO_ENTRIES) return -1;
    viable_read_eeprom(VIABLE_COMBO_OFFSET + index * sizeof(viable_combo_entry_t),
                       entry, sizeof(viable_combo_entry_t));
    return 0;
}

int viable_set_combo(uint8_t index, const viable_combo_entry_t *entry) {
    if (index >= VIABLE_COMBO_ENTRIES) return -1;
    viable_write_eeprom(VIABLE_COMBO_OFFSET + index * sizeof(viable_combo_entry_t),
                        entry, sizeof(viable_combo_entry_t));
    return 0;
}

// Storage functions - Key Override
int viable_get_key_override(uint8_t index, viable_key_override_entry_t *entry) {
    if (index >= VIABLE_KEY_OVERRIDE_ENTRIES) return -1;
    viable_read_eeprom(VIABLE_KEY_OVERRIDE_OFFSET + index * sizeof(viable_key_override_entry_t),
                       entry, sizeof(viable_key_override_entry_t));
    return 0;
}

int viable_set_key_override(uint8_t index, const viable_key_override_entry_t *entry) {
    if (index >= VIABLE_KEY_OVERRIDE_ENTRIES) return -1;
    viable_write_eeprom(VIABLE_KEY_OVERRIDE_OFFSET + index * sizeof(viable_key_override_entry_t),
                        entry, sizeof(viable_key_override_entry_t));
    return 0;
}

// Storage functions - Alt Repeat Key
int viable_get_alt_repeat_key(uint8_t index, viable_alt_repeat_key_entry_t *entry) {
    if (index >= VIABLE_ALT_REPEAT_KEY_ENTRIES) return -1;
    viable_read_eeprom(VIABLE_ALT_REPEAT_KEY_OFFSET + index * sizeof(viable_alt_repeat_key_entry_t),
                       entry, sizeof(viable_alt_repeat_key_entry_t));
    return 0;
}

int viable_set_alt_repeat_key(uint8_t index, const viable_alt_repeat_key_entry_t *entry) {
    if (index >= VIABLE_ALT_REPEAT_KEY_ENTRIES) return -1;
    viable_write_eeprom(VIABLE_ALT_REPEAT_KEY_OFFSET + index * sizeof(viable_alt_repeat_key_entry_t),
                        entry, sizeof(viable_alt_repeat_key_entry_t));
    return 0;
}

// Storage functions - One-Shot
void viable_get_one_shot(viable_one_shot_t *settings) {
    viable_read_eeprom(VIABLE_ONE_SHOT_OFFSET, settings, sizeof(viable_one_shot_t));
}

void viable_set_one_shot(const viable_one_shot_t *settings) {
    viable_write_eeprom(VIABLE_ONE_SHOT_OFFSET, settings, sizeof(viable_one_shot_t));
}

void viable_save(void) {
    // Data is written directly to EEPROM, nothing additional to flush
}

void viable_reset(void) {
    // Zero out all EEPROM storage
    uint8_t zero[16] = {0};
    for (uint16_t i = 0; i < VIABLE_EEPROM_SIZE; i += sizeof(zero)) {
        uint16_t chunk = sizeof(zero);
        if (i + chunk > VIABLE_EEPROM_SIZE) {
            chunk = VIABLE_EEPROM_SIZE - i;
        }
        viable_write_eeprom(i, zero, chunk);
    }
    viable_reload_tap_dance();
    viable_reload_combo();
    viable_reload_key_override();
    viable_reload_alt_repeat_key();
}

// Keycode execution helpers
void viable_keycode_down(uint16_t keycode) {
    g_viable_magic_keycode_override = keycode;

    if (keycode <= QK_MODS_MAX) {
        register_code16(keycode);
    } else {
        action_exec((keyevent_t){
            .type = KEY_EVENT,
            .key = (keypos_t){.row = VIABLE_MATRIX_MAGIC, .col = VIABLE_MATRIX_MAGIC},
            .pressed = 1,
            .time = (timer_read() | 1)
        });
    }
}

void viable_keycode_up(uint16_t keycode) {
    g_viable_magic_keycode_override = keycode;

    if (keycode <= QK_MODS_MAX) {
        unregister_code16(keycode);
    } else {
        action_exec((keyevent_t){
            .type = KEY_EVENT,
            .key = (keypos_t){.row = VIABLE_MATRIX_MAGIC, .col = VIABLE_MATRIX_MAGIC},
            .pressed = 0,
            .time = (timer_read() | 1)
        });
    }
}

void viable_keycode_tap(uint16_t keycode) {
    viable_keycode_down(keycode);
    wait_ms(TAP_CODE_DELAY);
    viable_keycode_up(keycode);
}

// 0xDF Protocol handler
// This function should be called from via_command_kb() in the keyboard code
bool viable_handle_command(uint8_t *data, uint8_t length) {
    // data[0] = 0xDF (VIABLE_PREFIX) - already verified by caller
    // data[1] = command_id
    // data[2...] = payload

    uint8_t command_id = data[1];

    switch (command_id) {
        case viable_cmd_get_info: {
            // Response: [0xDF] [0x00] [ver0-3] [td_count] [combo_count] [ko_count] [ark_count] [flags] [uid0-7]
            uint8_t uid[] = VIABLE_KEYBOARD_UID;
            data[2] = VIABLE_PROTOCOL_VERSION & 0xFF;
            data[3] = (VIABLE_PROTOCOL_VERSION >> 8) & 0xFF;
            data[4] = (VIABLE_PROTOCOL_VERSION >> 16) & 0xFF;
            data[5] = (VIABLE_PROTOCOL_VERSION >> 24) & 0xFF;
            data[6] = VIABLE_TAP_DANCE_ENTRIES;
            data[7] = VIABLE_COMBO_ENTRIES;
            data[8] = VIABLE_KEY_OVERRIDE_ENTRIES;
            data[9] = VIABLE_ALT_REPEAT_KEY_ENTRIES;
            data[10] = viable_get_feature_flags();
            memcpy(&data[11], uid, 8);
            break;
        }

        case viable_cmd_tap_dance_get: {
            // Request: [0xDF] [0x01] [index]
            // Response: [0xDF] [0x01] [index] [10 bytes entry]
            uint8_t idx = data[2];
            viable_tap_dance_entry_t entry = {0};
            viable_get_tap_dance(idx, &entry);
            memcpy(&data[3], &entry, sizeof(entry));
            break;
        }

        case viable_cmd_tap_dance_set: {
            // Request: [0xDF] [0x02] [index] [10 bytes entry]
            // Response: [0xDF] [0x02] [status]
            uint8_t idx = data[2];
            viable_tap_dance_entry_t entry;
            memcpy(&entry, &data[3], sizeof(entry));
            data[2] = viable_set_tap_dance(idx, &entry) == 0 ? 0 : 1;
            viable_reload_tap_dance();
            break;
        }

        case viable_cmd_combo_get: {
            // Request: [0xDF] [0x03] [index]
            // Response: [0xDF] [0x03] [index] [12 bytes entry]
            uint8_t idx = data[2];
            viable_combo_entry_t entry = {0};
            viable_get_combo(idx, &entry);
            memcpy(&data[3], &entry, sizeof(entry));
            break;
        }

        case viable_cmd_combo_set: {
            // Request: [0xDF] [0x04] [index] [12 bytes entry]
            // Response: [0xDF] [0x04] [status]
            uint8_t idx = data[2];
            viable_combo_entry_t entry;
            memcpy(&entry, &data[3], sizeof(entry));
            data[2] = viable_set_combo(idx, &entry) == 0 ? 0 : 1;
            viable_reload_combo();
            break;
        }

        case viable_cmd_key_override_get: {
            // Request: [0xDF] [0x05] [index]
            // Response: [0xDF] [0x05] [index] [12 bytes entry]
            uint8_t idx = data[2];
            viable_key_override_entry_t entry = {0};
            viable_get_key_override(idx, &entry);
            memcpy(&data[3], &entry, sizeof(entry));
            break;
        }

        case viable_cmd_key_override_set: {
            // Request: [0xDF] [0x06] [index] [12 bytes entry]
            // Response: [0xDF] [0x06] [status]
            uint8_t idx = data[2];
            viable_key_override_entry_t entry;
            memcpy(&entry, &data[3], sizeof(entry));
            data[2] = viable_set_key_override(idx, &entry) == 0 ? 0 : 1;
            viable_reload_key_override();
            break;
        }

        case viable_cmd_alt_repeat_key_get: {
            // Request: [0xDF] [0x07] [index]
            // Response: [0xDF] [0x07] [index] [6 bytes entry]
            uint8_t idx = data[2];
            viable_alt_repeat_key_entry_t entry = {0};
            viable_get_alt_repeat_key(idx, &entry);
            memcpy(&data[3], &entry, sizeof(entry));
            break;
        }

        case viable_cmd_alt_repeat_key_set: {
            // Request: [0xDF] [0x08] [index] [6 bytes entry]
            // Response: [0xDF] [0x08] [status]
            uint8_t idx = data[2];
            viable_alt_repeat_key_entry_t entry;
            memcpy(&entry, &data[3], sizeof(entry));
            data[2] = viable_set_alt_repeat_key(idx, &entry) == 0 ? 0 : 1;
            viable_reload_alt_repeat_key();
            break;
        }

        case viable_cmd_one_shot_get: {
            // Request: [0xDF] [0x09]
            // Response: [0xDF] [0x09] [timeout_lo] [timeout_hi] [tap_toggle]
            viable_one_shot_t settings = {0};
            viable_get_one_shot(&settings);
            data[2] = settings.timeout & 0xFF;
            data[3] = (settings.timeout >> 8) & 0xFF;
            data[4] = settings.tap_toggle;
            break;
        }

        case viable_cmd_one_shot_set: {
            // Request: [0xDF] [0x0A] [timeout_lo] [timeout_hi] [tap_toggle]
            // Response: [0xDF] [0x0A]
            viable_one_shot_t settings;
            settings.timeout = data[2] | (data[3] << 8);
            settings.tap_toggle = data[4];
            viable_set_one_shot(&settings);
            break;
        }

        case viable_cmd_save: {
            // Request: [0xDF] [0x0B]
            // Response: [0xDF] [0x0B]
            viable_save();
            break;
        }

        case viable_cmd_reset: {
            // Request: [0xDF] [0x0C]
            // Response: [0xDF] [0x0C]
            viable_reset();
            break;
        }

        case viable_cmd_definition_size: {
            // Request: [0xDF] [0x0D]
            // Response: [0xDF] [0x0D] [size0] [size1] [size2] [size3]
            uint32_t size = viable_get_definition_size();
            data[2] = size & 0xFF;
            data[3] = (size >> 8) & 0xFF;
            data[4] = (size >> 16) & 0xFF;
            data[5] = (size >> 24) & 0xFF;
            break;
        }

        case viable_cmd_definition_chunk: {
            // Request: [0xDF] [0x0E] [offset_lo] [offset_hi]
            // Response: [0xDF] [0x0E] [offset_lo] [offset_hi] [28 bytes data]
            uint16_t offset = data[2] | (data[3] << 8);
            viable_get_definition_chunk(offset, &data[4]);
            break;
        }

        case viable_cmd_qmk_settings_query: {
            // Request: [0xDF] [0x10] [qsid_lo] [qsid_hi]
            // Response: [0xDF] [0x10] [qsid1_lo] [qsid1_hi] [qsid2_lo] ... [0xFF] [0xFF]
            uint16_t qsid_gt = data[2] | (data[3] << 8);
            viable_qmk_settings_query(qsid_gt, &data[2], length - 2);
            break;
        }

        case viable_cmd_qmk_settings_get: {
            // Request: [0xDF] [0x11] [qsid_lo] [qsid_hi]
            // Response: [0xDF] [0x11] [status] [value bytes...]
            uint16_t qsid = data[2] | (data[3] << 8);
            data[2] = viable_qmk_settings_get(qsid, &data[3], length - 3);
            break;
        }

        case viable_cmd_qmk_settings_set: {
            // Request: [0xDF] [0x12] [qsid_lo] [qsid_hi] [value bytes...]
            // Response: [0xDF] [0x12] [status]
            uint16_t qsid = data[2] | (data[3] << 8);
            data[2] = viable_qmk_settings_set(qsid, &data[4], length - 4);
            break;
        }

        case viable_cmd_qmk_settings_reset: {
            // Request: [0xDF] [0x13]
            // Response: [0xDF] [0x13]
            viable_qmk_settings_reset();
            break;
        }

        default:
            // Unknown command - set error response
            data[1] = viable_cmd_error;
            return false;
    }

    return true;
}

// Override via_command_kb to intercept Viable protocol commands
bool via_command_kb(uint8_t *data, uint8_t length) {
    // Check for Viable prefix (0xDF)
    if (data[0] == VIABLE_PREFIX) {
        viable_handle_command(data, length);
        raw_hid_send(data, length);
        return true;  // Command was handled
    }
    return false;  // Let VIA handle other commands
}

// Process record hook for Viable features
bool process_record_viable(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_viable_tap_dance(keycode, record)) {
        return false;
    }
    return true;
}

// Override keymap_key_to_keycode to handle magic position for tap dance/combo execution
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
     if (key.row == VIABLE_MATRIX_MAGIC && key.col == VIABLE_MATRIX_MAGIC) {
        return g_viable_magic_keycode_override;
    } else  if (key.row < MATRIX_ROWS && key.col < MATRIX_COLS) {
        return keycode_at_keymap_location(layer, key.row, key.col);
    }
#ifdef ENCODER_MAP_ENABLE
    else if (key.row == KEYLOC_ENCODER_CW && key.col < NUM_ENCODERS) {
        return keycode_at_encodermap_location(layer, key.col, true);
    } else if (key.row == KEYLOC_ENCODER_CCW && key.col < NUM_ENCODERS) {
        return keycode_at_encodermap_location(layer, key.col, false);
    }
#endif // ENCODER_MAP_ENABLE
#ifdef DIP_SWITCH_MAP_ENABLE
    else if (key.row == KEYLOC_DIP_SWITCH_ON && key.col < NUM_DIP_SWITCHES) {
        return keycode_at_dip_switch_map_location(key.col, true);
    } else if (key.row == KEYLOC_DIP_SWITCH_OFF && key.col < NUM_DIP_SWITCHES) {
        return keycode_at_dip_switch_map_location(key.col, false);
    }
#endif // DIP_SWITCH_MAP_ENABLE

    // Use dynamic keymap for normal keys
    return KC_NO;
}
