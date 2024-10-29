// Copyright 2022 zhaqian
// Copyright 2024 Drashna Jael're (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

typedef struct {
        uint16_t button : 1;
        int16_t dial : 15;
} report_radial_controller_t;

void radial_controller_task(void);
void radial_controller_event_finished(void);
void radial_controller_button_update(bool pressed);
void radial_controller_dial_update(bool clockwise, bool continued);
void radial_controller_dial_finished(void);
bool process_radial_controller(uint16_t keycode, keyrecord_t *record);
