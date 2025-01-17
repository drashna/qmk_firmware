// Copyright 2025 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "quantum.h"
#include "ch.h"
#include "hal.h"
#include <string.h>
#include "usbh/debug.h"		/* for _usbh_dbg/_usbh_dbgf */

#include "usbh/dev/hid.h"
#include "chprintf.h"

static THD_WORKING_AREA(waTestHID, 1024);

static void _hid_report_callback(USBHHIDDriver *hidp, uint16_t len) {
    uint8_t *report = (uint8_t *)hidp->config->report_buffer;
    (void)report;

    if (hidp->type == USBHHID_DEVTYPE_BOOT_MOUSE) {
        _usbh_dbgf(hidp->dev->host, "Mouse report: buttons=%02x, Dx=%d, Dy=%d",
                report[0],
                (int8_t)report[1],
                (int8_t)report[2]);
    } else if (hidp->type == USBHHID_DEVTYPE_BOOT_KEYBOARD) {
        _usbh_dbgf(hidp->dev->host, "Keyboard report: modifier=%02x, keys=%02x %02x %02x %02x %02x %02x",
                report[0],
                report[2],
                report[3],
                report[4],
                report[5],
                report[6],
                report[7]);
    } else {
        _usbh_dbgf(hidp->dev->host, "Generic report, %d bytes", len);
    }
}

static USBH_DEFINE_BUFFER(uint8_t report[HAL_USBHHID_MAX_INSTANCES][8]);
static USBHHIDConfig hidcfg[HAL_USBHHID_MAX_INSTANCES];

static void ThreadTestHID(void *p) {
    (void)p;
    uint8_t i;
    static uint8_t kbd_led_states[HAL_USBHHID_MAX_INSTANCES];

    chRegSetThreadName("HID");

    for (i = 0; i < HAL_USBHHID_MAX_INSTANCES; i++) {
        hidcfg[i].cb_report = _hid_report_callback;
        hidcfg[i].protocol = USBHHID_PROTOCOL_BOOT;
        hidcfg[i].report_buffer = report[i];
        hidcfg[i].report_len = 8;
    }

    for (;;) {
        for (i = 0; i < HAL_USBHHID_MAX_INSTANCES; i++) {
        	USBHHIDDriver *const hidp = &USBHHIDD[i];
            if (usbhhidGetState(hidp) == USBHHID_STATE_ACTIVE) {
                _usbh_dbgf(hidp->dev->host, "HID: Connected, HID%d", i);
                usbhhidStart(hidp, &hidcfg[i]);
                if (usbhhidGetType(hidp) != USBHHID_DEVTYPE_GENERIC) {
                    usbhhidSetIdle(hidp, 0, 0);
                }
                kbd_led_states[i] = 1;
            } else if (usbhhidGetState(hidp) == USBHHID_STATE_READY) {
                if (usbhhidGetType(hidp) == USBHHID_DEVTYPE_BOOT_KEYBOARD) {
                    USBH_DEFINE_BUFFER(uint8_t val);
                    val = kbd_led_states[i] << 1;
                    if (val == 0x08) {
                        val = 1;
                    }
                    usbhhidSetReport(hidp, 0, USBHHID_REPORTTYPE_OUTPUT, &val, 1);
                    kbd_led_states[i] = val;
                }
            }
        }
        chThdSleepMilliseconds(200);
    }

}

void keyboard_pre_init_kb(void) {
    chThdCreateStatic(waTestHID, sizeof(waTestHID), NORMALPRIO, ThreadTestHID, 0);
    usbhStart(&USBHD2);
    _usbh_dbgf(&USBHD2, "Started");

    keyboard_pre_init_user();
}
void housekeeping_task_kb(void) {
    usbhMainLoop(&USBHD2);

}
