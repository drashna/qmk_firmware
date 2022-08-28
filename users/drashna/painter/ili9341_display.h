// Copyright 2022 QMK -- generated source code only, image retains original copyright
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

extern painter_device_t ili9341_display;
extern painter_font_handle_t font;


void housekeeping_task_quantum_painter(void);
void keyboard_post_init_quantum_painter(void);
void suspend_power_down_quantum_painter(void);
void suspend_wakeup_init_quantum_painter(void);
void shutdown_quantum_painter(void);
bool process_record_user_quantum_painter(uint16_t keycode, keyrecord_t* record);
