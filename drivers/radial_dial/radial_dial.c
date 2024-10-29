// Copyright 2022 zhaqian
// Copyright 2024 Drashna Jael're (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "radial_dial.h"
#include "report.h"
#include "host.h"
#include "timer.h"

// support encoder and switches
#ifndef RADIAL_CONTROLLER_RESOLUTION
#    define RADIAL_CONTROLLER_RESOLUTION 100
#endif

#ifndef RADIAL_CONTROLLER_ROTATION_STEP
#    define RADIAL_CONTROLLER_ROTATION_STEP 10
#endif

#ifndef RADIAL_CONTROLLER_TIMER_DELAY
#    define RADIAL_CONTROLLER_TIMER_DELAY 15
#endif

#ifndef RADIAL_CONTROLLER_ROTATION_CONTINUE_STEP
#    define RADIAL_CONTROLLER_ROTATION_CONTINUE_STEP RADIAL_CONTROLLER_RESOLUTION
#endif

static report_radial_dial_t report;

static int16_t  radial_controller_rotation           = 0;
static bool     is_radial_controller_rotate_finished = true;
static bool     is_clockwise                         = true;
static uint16_t radial_controller_timer              = 0;

void radial_controller_task(void) {
    if (!is_radial_controller_rotate_finished) {
        if (timer_elapsed(radial_controller_timer) > RADIAL_CONTROLLER_TIMER_DELAY) {
            if (is_clockwise) {
                radial_controller_rotation = radial_controller_rotation > (3600 - RADIAL_CONTROLLER_ROTATION_STEP) ? 3600 : radial_controller_rotation + RADIAL_CONTROLLER_ROTATION_STEP;
            } else {
                radial_controller_rotation = radial_controller_rotation < (-(3600 - RADIAL_CONTROLLER_ROTATION_STEP)) ? -3600 : radial_controller_rotation - RADIAL_CONTROLLER_ROTATION_STEP;
            }
            radial_controller_timer = timer_read();
#ifdef RADIAL_CONTROLLER_ROTATION_CONTINUE_BUTTON_ENABLE
            if (radial_controller_rotation >= RADIAL_CONTROLLER_ROTATION_CONTINUE_STEP || radial_controller_rotation <= -RADIAL_CONTROLLER_ROTATION_CONTINUE_STEP) {
                radial_controller_dial_finished();
                is_radial_controller_rotate_finished = false;
            }
#endif
        }
    }
}

void radial_controller_event_finished(void) {
    memset(&report, 0, sizeof(report));
    host_radial_dial_send(&report);
}

void radial_controller_button_update(bool pressed) {
    if (pressed) {
        report.button = 1;
    } else {
        report.button = 0;
    }
    host_radial_dial_send(&report);
}

void radial_controller_dial_update(bool clockwise, bool continued) {
    if (!continued) {
        if (clockwise) {
            report.rotation = RADIAL_CONTROLLER_RESOLUTION;
        } else {
            report.rotation = -RADIAL_CONTROLLER_RESOLUTION;
        }
        host_radial_dial_send(&report);
        report.rotation = 0;
    } else {
        is_clockwise                         = clockwise;
        is_radial_controller_rotate_finished = false;
        radial_controller_timer              = timer_read();
    }
}

void radial_controller_dial_finished(void) {
    is_radial_controller_rotate_finished = true;
    report.rotation                      = radial_controller_rotation;
    host_radial_dial_send(&report);
    report.rotation            = 0;
    radial_controller_rotation = 0;
    radial_controller_timer    = 0;
}

#if 0
bool process_radial_controller(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DIAL_BUT:
            if (record->event.pressed) {
                radial_controller_button_update(true);
            } else {
                radial_controller_button_update(false);
            }
            return false;
        case DIAL_L:
            if (record->event.pressed) {
                radial_controller_dial_update(false, false);
            }
            return false;
        case DIAL_R:
            if (record->event.pressed) {
                radial_controller_dial_update(true, false);
            }
            return false;
        case DIAL_LC:
            if (record->event.pressed) {
                radial_controller_dial_update(false, true);
            } else {
                radial_controller_dial_finished();
            }
            return false;
        case DIAL_RC:
            if (record->event.pressed) {
                radial_controller_dial_update(true, true);
            } else {
                radial_controller_dial_finished();
            }
            return false;
    }
    return true;
}
#endif
