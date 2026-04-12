// Copyright 2025 Ira Cooper <ira@wakeful.net>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#include "viable_qmk_settings.h"

// Viable protocol version
#define VIABLE_PROTOCOL_VERSION 0x00000001

// Keyboard UID - use VIAL_KEYBOARD_UID for backwards compatibility with .vil files
#ifndef VIABLE_KEYBOARD_UID
#   ifdef VIAL_KEYBOARD_UID
#       define VIABLE_KEYBOARD_UID VIAL_KEYBOARD_UID
#   else
#       define VIABLE_KEYBOARD_UID {0, 0, 0, 0, 0, 0, 0, 0}
#   endif
#endif

// Protocol prefix for 0xDF direct protocol
#define VIABLE_PREFIX 0xDF

// USB serial number magic for GUI/web detection
#ifndef SERIAL_NUMBER
#    define SERIAL_NUMBER "viable:12345-00"
#endif

// Viable command IDs (0xDF protocol v2)
enum viable_command_id {
    viable_cmd_get_info          = 0x00,
    viable_cmd_tap_dance_get     = 0x01,
    viable_cmd_tap_dance_set     = 0x02,
    viable_cmd_combo_get         = 0x03,
    viable_cmd_combo_set         = 0x04,
    viable_cmd_key_override_get  = 0x05,
    viable_cmd_key_override_set  = 0x06,
    viable_cmd_alt_repeat_key_get = 0x07,
    viable_cmd_alt_repeat_key_set = 0x08,
    viable_cmd_one_shot_get      = 0x09,
    viable_cmd_one_shot_set      = 0x0A,
    viable_cmd_save              = 0x0B,
    viable_cmd_reset             = 0x0C,
    viable_cmd_definition_size   = 0x0D,
    viable_cmd_definition_chunk  = 0x0E,
    // QMK Settings commands
    viable_cmd_qmk_settings_query = 0x10,
    viable_cmd_qmk_settings_get   = 0x11,
    viable_cmd_qmk_settings_set   = 0x12,
    viable_cmd_qmk_settings_reset = 0x13,
    viable_cmd_error             = 0xFF,
};

// Feature capability flags (returned in protocol info)
enum viable_feature_flags {
    viable_flag_caps_word   = (1 << 0),
    viable_flag_layer_lock  = (1 << 1),
    viable_flag_oneshot     = (1 << 2),
    // bits 3-7 reserved
};

// Keyboard definition chunk size (fits in 32-byte HID packet with header)
#define VIABLE_DEFINITION_CHUNK_SIZE 28

// Entry counts - default values, can be overridden
#ifndef VIABLE_TAP_DANCE_ENTRIES
#    define VIABLE_TAP_DANCE_ENTRIES 16
#endif

#ifndef VIABLE_COMBO_ENTRIES
#    define VIABLE_COMBO_ENTRIES 16
#endif

#ifndef VIABLE_KEY_OVERRIDE_ENTRIES
#    define VIABLE_KEY_OVERRIDE_ENTRIES 16
#endif

#ifndef VIABLE_ALT_REPEAT_KEY_ENTRIES
#    define VIABLE_ALT_REPEAT_KEY_ENTRIES 16
#endif

// Tap Dance entry structure (10 bytes)
// Enabled when custom_tapping_term bit 15 = 1
typedef struct __attribute__((packed)) {
    uint16_t on_tap;
    uint16_t on_hold;
    uint16_t on_double_tap;
    uint16_t on_tap_hold;
    uint16_t custom_tapping_term;  // bit 15 = enabled, bits 0-14 = timing (ms)
} viable_tap_dance_entry_t;
_Static_assert(sizeof(viable_tap_dance_entry_t) == 10, "viable_tap_dance_entry_t must be 10 bytes");

// Combo entry structure (12 bytes)
// Enabled when custom_combo_term bit 15 = 1
typedef struct __attribute__((packed)) {
    uint16_t input[4];             // Up to 4 trigger keys (0x0000 = unused)
    uint16_t output;               // Output keycode
    uint16_t custom_combo_term;    // bit 15 = enabled, bits 0-14 = timing (ms)
} viable_combo_entry_t;
_Static_assert(sizeof(viable_combo_entry_t) == 12, "viable_combo_entry_t must be 12 bytes");

// Key Override entry structure (12 bytes)
// Enabled when options bit 7 = 1
typedef struct __attribute__((packed)) {
    uint16_t trigger;              // Trigger keycode
    uint16_t replacement;          // Replacement keycode
    uint32_t layers;               // Layer mask (bit per layer, 32 layers)
    uint8_t  trigger_mods;         // Required modifiers
    uint8_t  negative_mod_mask;    // Modifiers that cancel override
    uint8_t  suppressed_mods;      // Modifiers to suppress
    uint8_t  options;              // Option flags (bit 7 = enabled)
} viable_key_override_entry_t;
_Static_assert(sizeof(viable_key_override_entry_t) == 12, "viable_key_override_entry_t must be 12 bytes");

// Key override option bits
enum viable_key_override_options {
    viable_ko_option_activation_trigger_down         = (1 << 0),
    viable_ko_option_activation_required_mod_down    = (1 << 1),
    viable_ko_option_activation_negative_mod_up      = (1 << 2),
    viable_ko_option_one_mod                         = (1 << 3),
    viable_ko_option_no_reregister_trigger           = (1 << 4),
    viable_ko_option_no_unregister_on_other_key_down = (1 << 5),
    // bit 6 reserved
    viable_ko_enabled                                = (1 << 7),
};

// Alt Repeat Key entry structure (6 bytes)
// Enabled when options bit 3 = 1
typedef struct __attribute__((packed)) {
    uint16_t keycode;              // Original keycode to match
    uint16_t alt_keycode;          // Alternate keycode to send on repeat
    uint8_t  allowed_mods;         // Modifier mask for matching
    uint8_t  options;              // Option flags (bit 3 = enabled)
} viable_alt_repeat_key_entry_t;
_Static_assert(sizeof(viable_alt_repeat_key_entry_t) == 6, "viable_alt_repeat_key_entry_t must be 6 bytes");

// Alt repeat key option bits
enum viable_alt_repeat_key_options {
    viable_ark_option_default_to_alt       = (1 << 0),
    viable_ark_option_bidirectional        = (1 << 1),
    viable_ark_option_ignore_mod_handedness = (1 << 2),
    viable_ark_enabled                     = (1 << 3),
    // bits 4-7 reserved
};

// One-shot settings structure (3 bytes)
typedef struct __attribute__((packed)) {
    uint16_t timeout;      // One-shot timeout in ms (0 = disabled)
    uint8_t  tap_toggle;   // Number of taps to toggle (0 = disabled)
} viable_one_shot_t;
_Static_assert(sizeof(viable_one_shot_t) == 3, "viable_one_shot_t must be 3 bytes");

// EEPROM layout constants - shared across all viable modules
#define VIABLE_TAP_DANCE_OFFSET      0
#define VIABLE_TAP_DANCE_SIZE        (VIABLE_TAP_DANCE_ENTRIES * sizeof(viable_tap_dance_entry_t))

#define VIABLE_COMBO_OFFSET          (VIABLE_TAP_DANCE_OFFSET + VIABLE_TAP_DANCE_SIZE)
#define VIABLE_COMBO_SIZE            (VIABLE_COMBO_ENTRIES * sizeof(viable_combo_entry_t))

#define VIABLE_KEY_OVERRIDE_OFFSET   (VIABLE_COMBO_OFFSET + VIABLE_COMBO_SIZE)
#define VIABLE_KEY_OVERRIDE_SIZE     (VIABLE_KEY_OVERRIDE_ENTRIES * sizeof(viable_key_override_entry_t))

#define VIABLE_ALT_REPEAT_KEY_OFFSET (VIABLE_KEY_OVERRIDE_OFFSET + VIABLE_KEY_OVERRIDE_SIZE)
#define VIABLE_ALT_REPEAT_KEY_SIZE   (VIABLE_ALT_REPEAT_KEY_ENTRIES * sizeof(viable_alt_repeat_key_entry_t))

#define VIABLE_ONE_SHOT_OFFSET       (VIABLE_ALT_REPEAT_KEY_OFFSET + VIABLE_ALT_REPEAT_KEY_SIZE)
#define VIABLE_ONE_SHOT_SIZE         sizeof(viable_one_shot_t)

#define VIABLE_MAGIC_SIZE            6
#define VIABLE_MAGIC_OFFSET          (VIABLE_ONE_SHOT_OFFSET + VIABLE_ONE_SHOT_SIZE)

#define VIABLE_QMK_SETTINGS_OFFSET   (VIABLE_MAGIC_OFFSET + VIABLE_MAGIC_SIZE)

// Total EEPROM size (excluding qmk_settings which has its own size constant)
#define VIABLE_EEPROM_SIZE           (VIABLE_TAP_DANCE_SIZE + VIABLE_COMBO_SIZE + VIABLE_KEY_OVERRIDE_SIZE + VIABLE_ALT_REPEAT_KEY_SIZE + VIABLE_ONE_SHOT_SIZE)

// Public API
void viable_init(void);

// Protocol handler for 0xDF commands
// Returns true if command was handled
bool viable_handle_command(uint8_t *data, uint8_t length);

void viable_read_eeprom(uint16_t offset, void *buf, uint16_t size);
void viable_write_eeprom(uint16_t offset, const void *buf, uint16_t size);

// Storage API - Tap Dance
int viable_get_tap_dance(uint8_t index, viable_tap_dance_entry_t *entry);
int viable_set_tap_dance(uint8_t index, const viable_tap_dance_entry_t *entry);

// Storage API - Combo
int viable_get_combo(uint8_t index, viable_combo_entry_t *entry);
int viable_set_combo(uint8_t index, const viable_combo_entry_t *entry);

// Storage API - Key Override
int viable_get_key_override(uint8_t index, viable_key_override_entry_t *entry);
int viable_set_key_override(uint8_t index, const viable_key_override_entry_t *entry);

// Storage API - Alt Repeat Key
int viable_get_alt_repeat_key(uint8_t index, viable_alt_repeat_key_entry_t *entry);
int viable_set_alt_repeat_key(uint8_t index, const viable_alt_repeat_key_entry_t *entry);

// Storage API - One-Shot
void viable_get_one_shot(viable_one_shot_t *settings);
void viable_set_one_shot(const viable_one_shot_t *settings);

// Administrative functions
void viable_save(void);
void viable_reset(void);

// Get feature flags for protocol info response
uint8_t viable_get_feature_flags(void);

// Reload functions (called after settings change)
void viable_reload_tap_dance(void);
void viable_reload_combo(void);
void viable_reload_key_override(void);
void viable_reload_alt_repeat_key(void);

// Keycode execution helpers
void viable_keycode_down(uint16_t keycode);
void viable_keycode_up(uint16_t keycode);
void viable_keycode_tap(uint16_t keycode);

// Keyboard definition functions
uint32_t viable_get_definition_size(void);
uint8_t viable_get_definition_chunk(uint16_t offset, uint8_t *buffer);

// Weak keyboard hook for post-init
void keyboard_post_init_viable_kb(void);

// Tap dance process_record hook
bool process_record_viable_tap_dance(uint16_t keycode, keyrecord_t *record);
