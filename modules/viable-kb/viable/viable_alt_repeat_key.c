// Copyright 2025 Ira Cooper <ira@wakeful.net>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "viable.h"
#include "quantum.h"

#ifdef REPEAT_KEY_ENABLE

// Storage for alt repeat key entries
static viable_alt_repeat_key_entry_t viable_alt_repeat_entries[VIABLE_ALT_REPEAT_KEY_ENTRIES];

// Track which entries are enabled
static bool viable_ark_entry_enabled[VIABLE_ALT_REPEAT_KEY_ENTRIES];

void viable_reload_alt_repeat_key(void) {
    memset(viable_alt_repeat_entries, 0, sizeof(viable_alt_repeat_entries));
    memset(viable_ark_entry_enabled, 0, sizeof(viable_ark_entry_enabled));

    // Load from EEPROM
    for (size_t i = 0; i < VIABLE_ALT_REPEAT_KEY_ENTRIES; ++i) {
        viable_alt_repeat_key_entry_t entry;
        if (viable_get_alt_repeat_key(i, &entry) == 0) {
            memcpy(&viable_alt_repeat_entries[i], &entry, sizeof(entry));
            viable_ark_entry_enabled[i] = (entry.options & viable_ark_enabled) != 0;
        }
    }
}

// Look up an alt repeat key for the given keycode and modifiers
// Returns the alt keycode if found, or KC_NO if not found
uint16_t viable_get_alt_repeat_keycode(uint16_t keycode, uint8_t mods) {
    for (size_t i = 0; i < VIABLE_ALT_REPEAT_KEY_ENTRIES; ++i) {
        if (!viable_ark_entry_enabled[i]) continue;

        viable_alt_repeat_key_entry_t *entry = &viable_alt_repeat_entries[i];

        // Check if keycode matches
        if (entry->keycode != keycode) continue;

        // Check modifiers
        uint8_t check_mods = mods;
        if (entry->options & viable_ark_option_ignore_mod_handedness) {
            // Collapse left/right mod distinction
            if (check_mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) {
                check_mods = (check_mods & ~(MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) | MOD_BIT(KC_LSFT);
            }
            if (check_mods & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))) {
                check_mods = (check_mods & ~(MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))) | MOD_BIT(KC_LCTL);
            }
            if (check_mods & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))) {
                check_mods = (check_mods & ~(MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))) | MOD_BIT(KC_LALT);
            }
            if (check_mods & (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))) {
                check_mods = (check_mods & ~(MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))) | MOD_BIT(KC_LGUI);
            }
        }

        // Check if allowed mods match
        if ((check_mods & entry->allowed_mods) != entry->allowed_mods) continue;

        // Found a match
        bool default_to_alt = (entry->options & viable_ark_option_default_to_alt) != 0;
        return default_to_alt ? entry->keycode : entry->alt_keycode;
    }

    return KC_NO;
}

// Check if we should use the reverse mapping (for bidirectional entries)
uint16_t viable_get_reverse_alt_repeat_keycode(uint16_t keycode, uint8_t mods) {
    for (size_t i = 0; i < VIABLE_ALT_REPEAT_KEY_ENTRIES; ++i) {
        if (!viable_ark_entry_enabled[i]) continue;

        viable_alt_repeat_key_entry_t *entry = &viable_alt_repeat_entries[i];

        // Only check bidirectional entries
        if (!(entry->options & viable_ark_option_bidirectional)) continue;

        // Check if alt_keycode matches (reverse direction)
        if (entry->alt_keycode != keycode) continue;

        // Found a reverse match - return the original keycode
        return entry->keycode;
    }

    return KC_NO;
}

#else
// Stubs when REPEAT_KEY_ENABLE is not defined
void viable_reload_alt_repeat_key(void) {}
#endif
