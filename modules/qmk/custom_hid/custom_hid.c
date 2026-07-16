// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

// Prototypes for the generated custom_hid_send / custom_hid_receive come from here (the single
// source of truth), keeping this module in step with the API the core USB stack was built against.
#include "community_modules_usb.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 2, 0);

// Echo every received report straight back to the host. A minimal example of a community module
// providing its own USB HID functionality, with no keymap code required.
void custom_hid_receive(uint8_t *data, uint8_t length) {
    custom_hid_send(data, length);
}
