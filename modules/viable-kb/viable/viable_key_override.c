// Copyright 2025 Ira Cooper <ira@wakeful.net>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "viable.h"
#include "quantum.h"

#ifdef KEY_OVERRIDE_ENABLE

#include "process_key_override.h"

// Static disabled flag for overrides that aren't enabled
static bool viable_key_override_disabled = false;

// Storage for key override structures
static key_override_t viable_key_overrides[VIABLE_KEY_OVERRIDE_ENTRIES];

static void viable_deserialize_key_override(uint8_t index, key_override_t *out) {
    viable_key_override_entry_t entry;
    if (viable_get_key_override(index, &entry) != 0) {
        memset(out, 0, sizeof(*out));
        out->enabled = &viable_key_override_disabled;
        return;
    }

    memset(out, 0, sizeof(*out));
    out->trigger = entry.trigger;
    out->trigger_mods = entry.trigger_mods;
    out->layers = entry.layers;
    out->negative_mod_mask = entry.negative_mod_mask;
    out->suppressed_mods = entry.suppressed_mods;
    out->replacement = entry.replacement;
    out->options = 0;
    out->custom_action = NULL;
    out->context = NULL;

    uint8_t opt = entry.options;
    if (opt & viable_ko_enabled) {
        out->enabled = NULL;  // NULL means enabled
    } else {
        out->enabled = &viable_key_override_disabled;
    }

    // Parse option bits
    if (opt & viable_ko_option_activation_trigger_down)
        out->options |= ko_option_activation_trigger_down;
    if (opt & viable_ko_option_activation_required_mod_down)
        out->options |= ko_option_activation_required_mod_down;
    if (opt & viable_ko_option_activation_negative_mod_up)
        out->options |= ko_option_activation_negative_mod_up;
    if (opt & viable_ko_option_one_mod)
        out->options |= ko_option_one_mod;
    if (opt & viable_ko_option_no_reregister_trigger)
        out->options |= ko_option_no_reregister_trigger;
    if (opt & viable_ko_option_no_unregister_on_other_key_down)
        out->options |= ko_option_no_unregister_on_other_key_down;
}

void viable_reload_key_override(void) {
    for (size_t i = 0; i < VIABLE_KEY_OVERRIDE_ENTRIES; ++i) {
        viable_deserialize_key_override(i, &viable_key_overrides[i]);
    }
}

// Override the introspection functions
uint16_t key_override_count(void) {
    return VIABLE_KEY_OVERRIDE_ENTRIES;
}

const key_override_t* key_override_get(uint16_t key_override_idx) {
    if (key_override_idx >= VIABLE_KEY_OVERRIDE_ENTRIES) {
        return NULL;
    }
    return &viable_key_overrides[key_override_idx];
}

#else
// Stubs when KEY_OVERRIDE_ENABLE is not defined
void viable_reload_key_override(void) {}
#endif
