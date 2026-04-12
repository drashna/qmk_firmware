// Copyright 2025 Ira Cooper <ira@wakeful.net>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "viable.h"
#include "quantum.h"
#include "eeprom.h"
#include <string.h>

#ifdef MOUSEKEY_ENABLE
#include "mousekey.h"
#endif

#ifdef AUTO_SHIFT_ENABLE
#include "process_auto_shift.h"
#endif

// Settings storage structure - matches Vial's qmk_settings_t for compatibility
typedef struct __attribute__((packed)) {
    uint16_t auto_shift_timeout;
    uint16_t osk_timeout;
    uint16_t mousekey_delay;
    uint16_t mousekey_interval;
    uint16_t mousekey_move_delta;
    uint16_t mousekey_max_speed;
    uint16_t mousekey_time_to_max;
    uint16_t mousekey_wheel_delay;
    uint16_t mousekey_wheel_interval;
    uint16_t mousekey_wheel_max_speed;
    uint16_t mousekey_wheel_time_to_max;
    uint16_t combo_term;
    uint16_t tapping_term;
    uint8_t  grave_esc_override;
    uint8_t  auto_shift;
    uint8_t  osk_tap_toggle;
    uint8_t  tapping_v2;
    uint16_t tap_code_delay;
    uint16_t tap_hold_caps_delay;
    uint8_t  tapping_toggle;
    uint8_t  unused;
    uint16_t quick_tap_term;
    uint16_t flow_tap_term;
} viable_qmk_settings_t;
_Static_assert(sizeof(viable_qmk_settings_t) == 40, "viable_qmk_settings_t must be 40 bytes");

// RAM copy of settings
static viable_qmk_settings_t settings;

// Forward declarations
static void viable_qmk_settings_load(void);
static void viable_qmk_settings_save(void);
static void viable_qmk_settings_apply(void);

// QSID definitions - must match GUI's qmk_settings.json
enum viable_qsid {
    QSID_GRAVE_ESC_OVERRIDE = 1,
    QSID_COMBO_TERM = 2,
    QSID_AUTO_SHIFT = 3,
    QSID_AUTO_SHIFT_TIMEOUT = 4,
    QSID_OSK_TAP_TOGGLE = 5,
    QSID_OSK_TIMEOUT = 6,
    QSID_TAPPING_TERM = 7,
    QSID_TAPPING_V1 = 8,  // Legacy tapping flags
    QSID_MOUSEKEY_DELAY = 9,
    QSID_MOUSEKEY_INTERVAL = 10,
    QSID_MOUSEKEY_MOVE_DELTA = 11,
    QSID_MOUSEKEY_MAX_SPEED = 12,
    QSID_MOUSEKEY_TIME_TO_MAX = 13,
    QSID_MOUSEKEY_WHEEL_DELAY = 14,
    QSID_MOUSEKEY_WHEEL_INTERVAL = 15,
    QSID_MOUSEKEY_WHEEL_MAX_SPEED = 16,
    QSID_MOUSEKEY_WHEEL_TIME_TO_MAX = 17,
    QSID_TAP_CODE_DELAY = 18,
    QSID_TAP_HOLD_CAPS_DELAY = 19,
    QSID_TAPPING_TOGGLE = 20,
    QSID_MAGIC = 21,
    QSID_PERMISSIVE_HOLD = 22,
    QSID_HOLD_ON_OTHER_KEY = 23,
    QSID_RETRO_TAPPING = 24,
    QSID_QUICK_TAP_TERM = 25,
    QSID_CHORDAL_HOLD = 26,
    QSID_FLOW_TAP_TERM = 27,
};

// tapping_v2 bit positions
#define TAPPING_PERMISSIVE_HOLD_BIT 0
#define TAPPING_HOLD_ON_OTHER_KEY_BIT 1
#define TAPPING_RETRO_TAPPING_BIT 2
#define TAPPING_CHORDAL_HOLD_BIT 3

// Setting descriptor
typedef struct {
    uint16_t qsid;
    uint8_t  size;    // Size in bytes (0 = special handler)
    uint16_t offset;  // Offset in settings struct
    uint8_t  bit;     // For bit fields
} viable_setting_desc_t;

// Setting descriptors - defines all supported QSIDs
static const viable_setting_desc_t setting_descs[] = {
    { QSID_GRAVE_ESC_OVERRIDE, 1, offsetof(viable_qmk_settings_t, grave_esc_override), 0 },
    { QSID_COMBO_TERM, 2, offsetof(viable_qmk_settings_t, combo_term), 0 },
    { QSID_AUTO_SHIFT, 1, offsetof(viable_qmk_settings_t, auto_shift), 0 },
    { QSID_AUTO_SHIFT_TIMEOUT, 2, offsetof(viable_qmk_settings_t, auto_shift_timeout), 0 },
    { QSID_OSK_TAP_TOGGLE, 1, offsetof(viable_qmk_settings_t, osk_tap_toggle), 0 },
    { QSID_OSK_TIMEOUT, 2, offsetof(viable_qmk_settings_t, osk_timeout), 0 },
    { QSID_TAPPING_TERM, 2, offsetof(viable_qmk_settings_t, tapping_term), 0 },
#ifdef MOUSEKEY_ENABLE
    { QSID_MOUSEKEY_DELAY, 2, offsetof(viable_qmk_settings_t, mousekey_delay), 0 },
    { QSID_MOUSEKEY_INTERVAL, 2, offsetof(viable_qmk_settings_t, mousekey_interval), 0 },
    { QSID_MOUSEKEY_MOVE_DELTA, 2, offsetof(viable_qmk_settings_t, mousekey_move_delta), 0 },
    { QSID_MOUSEKEY_MAX_SPEED, 2, offsetof(viable_qmk_settings_t, mousekey_max_speed), 0 },
    { QSID_MOUSEKEY_TIME_TO_MAX, 2, offsetof(viable_qmk_settings_t, mousekey_time_to_max), 0 },
    { QSID_MOUSEKEY_WHEEL_DELAY, 2, offsetof(viable_qmk_settings_t, mousekey_wheel_delay), 0 },
    { QSID_MOUSEKEY_WHEEL_INTERVAL, 2, offsetof(viable_qmk_settings_t, mousekey_wheel_interval), 0 },
    { QSID_MOUSEKEY_WHEEL_MAX_SPEED, 2, offsetof(viable_qmk_settings_t, mousekey_wheel_max_speed), 0 },
    { QSID_MOUSEKEY_WHEEL_TIME_TO_MAX, 2, offsetof(viable_qmk_settings_t, mousekey_wheel_time_to_max), 0 },
#endif
    { QSID_TAP_CODE_DELAY, 2, offsetof(viable_qmk_settings_t, tap_code_delay), 0 },
    { QSID_TAP_HOLD_CAPS_DELAY, 2, offsetof(viable_qmk_settings_t, tap_hold_caps_delay), 0 },
    { QSID_TAPPING_TOGGLE, 1, offsetof(viable_qmk_settings_t, tapping_toggle), 0 },
    { QSID_MAGIC, 0, 0, 0 },  // Special handler
    // Individual bit settings from tapping_v2
    { QSID_PERMISSIVE_HOLD, 1, offsetof(viable_qmk_settings_t, tapping_v2), TAPPING_PERMISSIVE_HOLD_BIT },
    { QSID_HOLD_ON_OTHER_KEY, 1, offsetof(viable_qmk_settings_t, tapping_v2), TAPPING_HOLD_ON_OTHER_KEY_BIT },
    { QSID_RETRO_TAPPING, 1, offsetof(viable_qmk_settings_t, tapping_v2), TAPPING_RETRO_TAPPING_BIT },
    { QSID_QUICK_TAP_TERM, 2, offsetof(viable_qmk_settings_t, quick_tap_term), 0 },
    { QSID_CHORDAL_HOLD, 1, offsetof(viable_qmk_settings_t, tapping_v2), TAPPING_CHORDAL_HOLD_BIT },
    { QSID_FLOW_TAP_TERM, 2, offsetof(viable_qmk_settings_t, flow_tap_term), 0 },
};

#define NUM_SETTINGS (sizeof(setting_descs) / sizeof(setting_descs[0]))

// Find setting descriptor by QSID
static const viable_setting_desc_t* find_setting(uint16_t qsid) {
    for (size_t i = 0; i < NUM_SETTINGS; i++) {
        if (setting_descs[i].qsid == qsid) {
            return &setting_descs[i];
        }
    }
    return NULL;
}

// Initialize QMK settings
void viable_qmk_settings_init(void) {
    viable_qmk_settings_load();
    viable_qmk_settings_apply();
}

// Load settings from EEPROM
static void viable_qmk_settings_load(void) {
    viable_read_eeprom(VIABLE_QMK_SETTINGS_OFFSET, &settings, sizeof(settings));
}

// Save settings to EEPROM
static void viable_qmk_settings_save(void) {
    viable_write_eeprom(VIABLE_QMK_SETTINGS_OFFSET, &settings, sizeof(settings));
}

// Apply settings to QMK subsystems
static void viable_qmk_settings_apply(void) {
#ifdef AUTO_SHIFT_ENABLE
    set_autoshift_timeout(settings.auto_shift_timeout);
#endif

#ifdef MOUSEKEY_ENABLE
    mk_delay = settings.mousekey_delay / 10;
    mk_interval = settings.mousekey_interval;
    mk_max_speed = settings.mousekey_max_speed;
    mk_time_to_max = settings.mousekey_time_to_max;
    mk_wheel_max_speed = settings.mousekey_wheel_max_speed;
    mk_wheel_time_to_max = settings.mousekey_wheel_time_to_max;
#endif
}

// Query supported QSIDs greater than qsid_gt
// Response format: list of uint16_t QSIDs, terminated by 0xFFFF
void viable_qmk_settings_query(uint16_t qsid_gt, uint8_t *buffer, uint8_t length) {
    memset(buffer, 0xFF, length);

    size_t buf_offset = 0;
    for (size_t i = 0; i < NUM_SETTINGS; i++) {
        if (setting_descs[i].qsid > qsid_gt) {
            if (buf_offset + 2 > length) break;
            buffer[buf_offset++] = setting_descs[i].qsid & 0xFF;
            buffer[buf_offset++] = (setting_descs[i].qsid >> 8) & 0xFF;
        }
    }
}

// Get a setting value
// Returns 0 on success, non-zero on error
int viable_qmk_settings_get(uint16_t qsid, uint8_t *buffer, uint8_t length) {
    // Special case: Magic settings (keymap_config)
    if (qsid == QSID_MAGIC) {
        if (length < 4) return -1;
        uint32_t flags =
            (keymap_config.swap_control_capslock << 0) |
            (keymap_config.capslock_to_control << 1) |
            (keymap_config.swap_lalt_lgui << 2) |
            (keymap_config.swap_ralt_rgui << 3) |
            (keymap_config.no_gui << 4) |
            (keymap_config.swap_grave_esc << 5) |
            (keymap_config.swap_backslash_backspace << 6) |
            (keymap_config.nkro << 7) |
            (keymap_config.swap_lctl_lgui << 8) |
            (keymap_config.swap_rctl_rgui << 9);
        memcpy(buffer, &flags, 4);
        return 0;
    }

    const viable_setting_desc_t *desc = find_setting(qsid);
    if (!desc) return -1;

    // Bit field settings (QSID 22-26)
    if (qsid >= QSID_PERMISSIVE_HOLD && qsid <= QSID_CHORDAL_HOLD && qsid != QSID_QUICK_TAP_TERM) {
        if (length < 1) return -1;
        uint8_t *field = ((uint8_t*)&settings) + desc->offset;
        buffer[0] = (*field >> desc->bit) & 1;
        return 0;
    }

    // Regular settings
    if (desc->size > length) return -1;
    memcpy(buffer, ((uint8_t*)&settings) + desc->offset, desc->size);
    return 0;
}

// Set a setting value
// Returns 0 on success, non-zero on error
int viable_qmk_settings_set(uint16_t qsid, const uint8_t *data, uint8_t length) {
    // Special case: Magic settings (keymap_config)
    if (qsid == QSID_MAGIC) {
        if (length < 4) return -1;
        uint32_t flags;
        memcpy(&flags, data, 4);

        clear_keyboard();  // Prevent stuck keys when changing NKRO

        keymap_config.swap_control_capslock = (flags >> 0) & 1;
        keymap_config.capslock_to_control = (flags >> 1) & 1;
        keymap_config.swap_lalt_lgui = (flags >> 2) & 1;
        keymap_config.swap_ralt_rgui = (flags >> 3) & 1;
        keymap_config.no_gui = (flags >> 4) & 1;
        keymap_config.swap_grave_esc = (flags >> 5) & 1;
        keymap_config.swap_backslash_backspace = (flags >> 6) & 1;
        keymap_config.nkro = (flags >> 7) & 1;
        keymap_config.swap_lctl_lgui = (flags >> 8) & 1;
        keymap_config.swap_rctl_rgui = (flags >> 9) & 1;

        eeconfig_update_keymap(&keymap_config);
        return 0;
    }

    const viable_setting_desc_t *desc = find_setting(qsid);
    if (!desc) return -1;

    // Bit field settings
    if (qsid >= QSID_PERMISSIVE_HOLD && qsid <= QSID_CHORDAL_HOLD && qsid != QSID_QUICK_TAP_TERM) {
        if (length < 1) return -1;
        uint8_t *field = ((uint8_t*)&settings) + desc->offset;
        if (data[0]) {
            *field |= (1 << desc->bit);
        } else {
            *field &= ~(1 << desc->bit);
        }
        viable_qmk_settings_save();
        return 0;
    }

    // Regular settings
    if (desc->size > length) return -1;
    memcpy(((uint8_t*)&settings) + desc->offset, data, desc->size);
    viable_qmk_settings_save();
    viable_qmk_settings_apply();
    return 0;
}

// Reset all settings to defaults
void viable_qmk_settings_reset(void) {
    memset(&settings, 0, sizeof(settings));

    // Set defaults
    settings.tapping_term = TAPPING_TERM;
#ifdef COMBO_TERM
    settings.combo_term = COMBO_TERM;
#else
    settings.combo_term = 50;
#endif
#ifdef ONESHOT_TIMEOUT
    settings.osk_timeout = ONESHOT_TIMEOUT;
#else
    settings.osk_timeout = 5000;
#endif
#ifdef ONESHOT_TAP_TOGGLE
    settings.osk_tap_toggle = ONESHOT_TAP_TOGGLE;
#else
    settings.osk_tap_toggle = 5;
#endif
#ifdef AUTO_SHIFT_TIMEOUT
    settings.auto_shift_timeout = AUTO_SHIFT_TIMEOUT;
#else
    settings.auto_shift_timeout = 175;
#endif
#ifdef TAP_CODE_DELAY
    settings.tap_code_delay = TAP_CODE_DELAY;
#else
    settings.tap_code_delay = 10;
#endif
#ifdef TAP_HOLD_CAPS_DELAY
    settings.tap_hold_caps_delay = TAP_HOLD_CAPS_DELAY;
#else
    settings.tap_hold_caps_delay = 80;
#endif
#ifdef TAPPING_TOGGLE
    settings.tapping_toggle = TAPPING_TOGGLE;
#else
    settings.tapping_toggle = 5;
#endif
#ifdef QUICK_TAP_TERM
    settings.quick_tap_term = QUICK_TAP_TERM;
#else
    settings.quick_tap_term = TAPPING_TERM;
#endif

    // Tapping behavior defaults - keyboards can override via defines
    settings.tapping_v2 = 0;
#if defined(VIABLE_DEFAULT_PERMISSIVE_HOLD) && VIABLE_DEFAULT_PERMISSIVE_HOLD
    settings.tapping_v2 |= (1 << TAPPING_PERMISSIVE_HOLD_BIT);
#endif
#if defined(VIABLE_DEFAULT_CHORDAL_HOLD) && VIABLE_DEFAULT_CHORDAL_HOLD
    settings.tapping_v2 |= (1 << TAPPING_CHORDAL_HOLD_BIT);
#endif
#if defined(VIABLE_DEFAULT_HOLD_ON_OTHER_KEY) && VIABLE_DEFAULT_HOLD_ON_OTHER_KEY
    settings.tapping_v2 |= (1 << TAPPING_HOLD_ON_OTHER_KEY_BIT);
#endif
#if defined(VIABLE_DEFAULT_RETRO_TAPPING) && VIABLE_DEFAULT_RETRO_TAPPING
    settings.tapping_v2 |= (1 << TAPPING_RETRO_TAPPING_BIT);
#endif

#ifdef MOUSEKEY_ENABLE
    settings.mousekey_delay = MOUSEKEY_DELAY;
    settings.mousekey_interval = MOUSEKEY_INTERVAL;
    settings.mousekey_move_delta = MOUSEKEY_MOVE_DELTA;
    settings.mousekey_max_speed = MOUSEKEY_MAX_SPEED;
    settings.mousekey_time_to_max = MOUSEKEY_TIME_TO_MAX;
    settings.mousekey_wheel_delay = MOUSEKEY_WHEEL_DELAY;
    settings.mousekey_wheel_interval = MOUSEKEY_WHEEL_INTERVAL;
    settings.mousekey_wheel_max_speed = MOUSEKEY_WHEEL_MAX_SPEED;
    settings.mousekey_wheel_time_to_max = MOUSEKEY_WHEEL_TIME_TO_MAX;
#endif

    viable_qmk_settings_save();
    viable_qmk_settings_apply();

    // Reset magic settings to defaults
    clear_keyboard();
    keymap_config.raw = 0;
    keymap_config.oneshot_enable = 1;
#ifdef NKRO_ENABLE
#   if defined(VIABLE_DEFAULT_NKRO)
    keymap_config.nkro = VIABLE_DEFAULT_NKRO;
#   else
    keymap_config.nkro = 1;  // Default NKRO on if supported
#   endif
#endif
    eeconfig_update_keymap(&keymap_config);
}

// User hooks (*_viable suffix): override these for custom per-key logic
// For booleans: return -1 to use Viable's setting, 0 for false, 1 for true
// For uint16_t: return 0 to use Viable's setting, or a positive value to override
// User hooks are checked FIRST - they always beat Viable's settings
// Note: get_tapping_term_viable is in viable_tap_dance.c
// Note: get_combo_term_viable is in viable_combo.c

__attribute__((weak)) int8_t get_permissive_hold_viable(uint16_t keycode, keyrecord_t *record) {
    return -1;  // Default: use Viable's setting
}

__attribute__((weak)) int8_t get_hold_on_other_key_press_viable(uint16_t keycode, keyrecord_t *record) {
    return -1;  // Default: use Viable's setting
}

__attribute__((weak)) int8_t get_retro_tapping_viable(uint16_t keycode, keyrecord_t *record) {
    return -1;  // Default: use Viable's setting
}

__attribute__((weak)) uint16_t get_quick_tap_term_viable(uint16_t keycode, keyrecord_t *record) {
    return 0;  // Default: use Viable's setting
}

// Viable owns these functions - user hook is checked FIRST
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    int8_t user_val = get_permissive_hold_viable(keycode, record);
    if (user_val >= 0) return user_val;
    return settings.tapping_v2 & (1 << TAPPING_PERMISSIVE_HOLD_BIT);
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    int8_t user_val = get_hold_on_other_key_press_viable(keycode, record);
    if (user_val >= 0) return user_val;
    return settings.tapping_v2 & (1 << TAPPING_HOLD_ON_OTHER_KEY_BIT);
}

bool get_retro_tapping(uint16_t keycode, keyrecord_t *record) {
    int8_t user_val = get_retro_tapping_viable(keycode, record);
    if (user_val >= 0) return user_val;
    return settings.tapping_v2 & (1 << TAPPING_RETRO_TAPPING_BIT);
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    uint16_t user_val = get_quick_tap_term_viable(keycode, record);
    if (user_val > 0) return user_val;
    return settings.quick_tap_term;
}

// Getters for other modules to use
uint16_t viable_get_tapping_term(void) {
    return settings.tapping_term;
}

uint16_t viable_get_combo_term(void) {
    return settings.combo_term;
}
