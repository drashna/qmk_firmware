// Copyright 2025 Ira Cooper <ira@wakeful.net>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "viable.h"
#include "quantum.h"

#ifdef COMBO_ENABLE

#include "process_combo.h"

// Bit mask for enabled flag in custom_combo_term
#define VIABLE_COMBO_ENABLED_BIT 0x8000
// Mask for timing value (bits 0-14)
#define VIABLE_COMBO_TIMING_MASK 0x7FFF

// Storage for combo key sequences (4 keys + COMBO_END terminator)
static uint16_t viable_combo_keys[VIABLE_COMBO_ENTRIES][5];

// Storage for combo structures
static combo_t viable_combos[VIABLE_COMBO_ENTRIES];

// Storage for custom combo terms (0 = use global default)
static uint16_t viable_combo_terms[VIABLE_COMBO_ENTRIES];

// Track which combos are enabled
static bool viable_combo_enabled[VIABLE_COMBO_ENTRIES];

void viable_reload_combo(void) {
    // Initialize with all keys = COMBO_END
    memset(viable_combo_keys, 0, sizeof(viable_combo_keys));
    memset(viable_combos, 0, sizeof(viable_combos));
    memset(viable_combo_terms, 0, sizeof(viable_combo_terms));
    memset(viable_combo_enabled, 0, sizeof(viable_combo_enabled));

    // Load from EEPROM
    for (size_t i = 0; i < VIABLE_COMBO_ENTRIES; ++i) {
        uint16_t *seq = viable_combo_keys[i];
        viable_combos[i].keys = seq;

        viable_combo_entry_t entry;
        if (viable_get_combo(i, &entry) == 0) {
            // Check if enabled (bit 15 of custom_combo_term)
            viable_combo_enabled[i] = (entry.custom_combo_term & VIABLE_COMBO_ENABLED_BIT) != 0;

            if (viable_combo_enabled[i]) {
                memcpy(seq, entry.input, sizeof(entry.input));
                // Ensure null termination
                seq[4] = COMBO_END;
                viable_combos[i].keycode = entry.output;

                // Extract custom timing (bits 0-14), 0 means use global default
                viable_combo_terms[i] = entry.custom_combo_term & VIABLE_COMBO_TIMING_MASK;
            } else {
                // Disabled combo: empty key sequence
                seq[0] = COMBO_END;
                viable_combos[i].keycode = KC_NO;
            }
        }
    }
}

// Override the introspection functions
uint16_t combo_count(void) {
    return VIABLE_COMBO_ENTRIES;
}

combo_t* combo_get(uint16_t combo_idx) {
    if (combo_idx >= VIABLE_COMBO_ENTRIES) {
        return NULL;
    }
    return &viable_combos[combo_idx];
}

// User hook: override this for custom per-combo timing logic
// Return 0 to use Viable's setting, or a positive value to override
__attribute__((weak)) uint16_t get_combo_term_viable(uint16_t combo_idx, combo_t *combo) {
    return 0;  // Default: use Viable's setting
}

// Viable owns this function - user hook is checked FIRST
uint16_t get_combo_term(uint16_t combo_idx, combo_t *combo) {
    // User hook gets first priority
    uint16_t user_term = get_combo_term_viable(combo_idx, combo);
    if (user_term > 0) {
        return user_term;
    }

    // Then check for per-combo custom timing from Viable
    if (combo_idx < VIABLE_COMBO_ENTRIES && viable_combo_terms[combo_idx] > 0) {
        return viable_combo_terms[combo_idx];
    }

    // Fall back to Viable's global setting
    return viable_get_combo_term();
}

#else
// Stubs when COMBO_ENABLE is not defined
void viable_reload_combo(void) {}
#endif
