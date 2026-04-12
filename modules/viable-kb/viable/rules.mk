# Viable - VIA3-based dynamic features module
# Provides: tap dance, combo, key override, keyboard definition

# Set USB serial number for GUI detection (unless keyboard overrides it)
SERIAL_NUMBER ?= viable:12345-00
OPT_DEFS += -DSERIAL_NUMBER=\"$(SERIAL_NUMBER)\"

# Enable required QMK features if not already enabled
TAP_DANCE_ENABLE ?= yes
COMBO_ENABLE ?= yes
KEY_OVERRIDE_ENABLE ?= yes

# Enable tapping term per key for tap dance custom timing
TAPPING_TERM_PER_KEY ?= yes

# Add viable source files
SRC += viable_tap_dance.c \
       viable_combo.c \
       viable_key_override.c \
       viable_alt_repeat_key.c \
       viable_definition.c \
       viable_qmk_settings.c

# Generate compressed keyboard definition header
# Search for viable.json in keymap directories (same search order as QMK)
VIABLE_JSON_PATH := $(firstword \
    $(wildcard $(MAIN_KEYMAP_PATH_1)/viable.json) \
    $(wildcard $(MAIN_KEYMAP_PATH_2)/viable.json) \
    $(wildcard $(MAIN_KEYMAP_PATH_3)/viable.json) \
    $(wildcard $(MAIN_KEYMAP_PATH_4)/viable.json) \
    $(wildcard $(MAIN_KEYMAP_PATH_5)/viable.json))

VIABLE_DEFINITION_HEADER := $(INTERMEDIATE_OUTPUT)/src/viable_definition_data.h

# Generate the header at the start of the build
$(shell mkdir -p "$(INTERMEDIATE_OUTPUT)/src" && \
    python3 "$(MODULE_PATH_VIABLE)/viable_compress.py" \
        "$(VIABLE_JSON_PATH)" \
        "$(VIABLE_DEFINITION_HEADER)" >/dev/null 2>&1)
