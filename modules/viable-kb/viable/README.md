# Viable Module

Viable is a QMK community module that provides dynamic configuration of advanced QMK features via USB HID protocol. It's designed to work with the Vial GUI (or compatible tools) to allow users to configure tap dance, combos, key overrides, and QMK settings without recompiling firmware.

## Features

- Dynamic Tap Dance configuration
- Dynamic Combo configuration
- Dynamic Key Override configuration
- Dynamic Alt Repeat Key configuration
- One-Shot key settings
- QMK Settings (tapping term, mouse keys, magic settings, etc.)

## Installation

Add to your keymap's `keymap.json`:

```json
{
    "modules": ["viable-kb/viable"]
}
```

## Configuration

All configuration options are set in your keyboard's `config.h`.

### Keyboard UID

The keyboard UID is used to match saved profiles (.vil files) to the correct keyboard. If your keyboard previously used Vial, define the same UID for backwards compatibility:

```c
// Use the same UID as your Vial keymap for .vil compatibility
#define VIAL_KEYBOARD_UID {0x1B, 0x18, 0x7D, 0xF2, 0x21, 0xF6, 0x29, 0x48}
```

Viable will automatically use `VIAL_KEYBOARD_UID` if defined. You can also define `VIABLE_KEYBOARD_UID` directly:

```c
#define VIABLE_KEYBOARD_UID {0x1B, 0x18, 0x7D, 0xF2, 0x21, 0xF6, 0x29, 0x48}
```

If neither is defined, the UID defaults to all zeros.

### Entry Counts

Control how many entries are available for each dynamic feature. More entries use more EEPROM space.

```c
// Tap dance entries (default: 16, each uses 10 bytes)
#define VIABLE_TAP_DANCE_ENTRIES 50

// Combo entries (default: 16, each uses 12 bytes)
#define VIABLE_COMBO_ENTRIES 50

// Key override entries (default: 16, each uses 12 bytes)
#define VIABLE_KEY_OVERRIDE_ENTRIES 30

// Alt repeat key entries (default: 16, each uses 6 bytes)
#define VIABLE_ALT_REPEAT_KEY_ENTRIES 16
```

### Default Settings

These settings are applied when EEPROM is reset (e.g., after flashing new firmware). Users can change them via the GUI, but these are the starting values.

#### NKRO (N-Key Rollover)

```c
// Enable NKRO by default (requires NKRO_ENABLE in rules.mk)
// Set to 0 to default to 6KRO, 1 to default to NKRO
#define VIABLE_DEFAULT_NKRO 1
```

If not defined, defaults to 1 (NKRO on) when `NKRO_ENABLE` is set.

#### Tapping Behavior

These control mod-tap and layer-tap behavior. See [QMK Tap-Hold documentation](https://docs.qmk.fm/#/tap_hold) for details.

```c
// Permissive Hold: Trigger hold action if another key is pressed and released
// while the tap-hold key is held, even within tapping term
#define VIABLE_DEFAULT_PERMISSIVE_HOLD 1

// Chordal Hold: Allows comfortable same-hand rolls with mod-taps
// Recommended for most users
#define VIABLE_DEFAULT_CHORDAL_HOLD 1

// Hold On Other Key Press: Immediately select hold action when another key
// is pressed (more aggressive than permissive hold)
#define VIABLE_DEFAULT_HOLD_ON_OTHER_KEY 0

// Retro Tapping: If hold action is triggered but no other key is pressed,
// send the tap action on release
#define VIABLE_DEFAULT_RETRO_TAPPING 0
```

### Example Configuration

Here's a complete example for a keyboard that wants generous dynamic feature storage and sensible mod-tap defaults:

```c
// config.h

// Generous entry counts for power users
#define VIABLE_TAP_DANCE_ENTRIES 50
#define VIABLE_COMBO_ENTRIES 50
#define VIABLE_KEY_OVERRIDE_ENTRIES 30

// Sane defaults for mod-tap heavy usage
#define VIABLE_DEFAULT_NKRO 1
#define VIABLE_DEFAULT_PERMISSIVE_HOLD 1
#define VIABLE_DEFAULT_CHORDAL_HOLD 1
```

## EEPROM Layout

Viable stores data in the keyboard's EEPROM datablock. The layout is:

| Section | Size |
|---------|------|
| Tap Dance | entries × 10 bytes |
| Combo | entries × 12 bytes |
| Key Override | entries × 12 bytes |
| Alt Repeat Key | entries × 6 bytes |
| One-Shot | 3 bytes |
| Magic (version) | 6 bytes |
| QMK Settings | 40 bytes |

With default entry counts (16 each), this uses approximately 689 bytes.

## EEPROM Reset Behavior

Viable uses the build timestamp as a version marker. When firmware is flashed, if the timestamp differs from what's stored in EEPROM, all Viable settings are reset to defaults. This ensures a clean state when firmware changes might affect data layout.

## Protocol

Viable uses the `0xDF` prefix for its USB HID protocol, separate from VIA's `0xFE` prefix. This allows it to coexist with VIA while providing additional functionality.

## GUI Support

Viable is designed to work with the Vial GUI. The GUI auto-detects Viable support via the `viable:` prefix in the USB serial string.

## License

GPL-2.0-or-later
