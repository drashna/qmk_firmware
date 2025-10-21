// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "print.h"

#include "tusb.h"
#include "pio_usb_ll.h"
#include "report_descriptor_parser.h"
#include "report_parser.h"

matrix_row_t*           matrix_dest;
bool                    mouse_send_flag = false;
static uint8_t          kbd_addr;
static uint8_t          kbd_instance;
static int32_t          led_count = -1;
static uint8_t          hid_report_buffer[64];
static volatile uint8_t hid_report_size;
static uint8_t          hid_instance;
static bool             hid_disconnect_flag;
static uint8_t          pre_keyreport[8];
#define LED_BLINK_TIME_MS 50
#define KQ_PIN_LED 13
#define MATRIX_MSBTN_ROW 22

extern void busy_wait_us(uint64_t delay_us);
static bool send_led_report(uint8_t* leds);

void matrix_init_custom(void) {
    // Configure LED pin
    gpio_set_pin_output(KQ_PIN_LED);
    gpio_write_pin_high(KQ_PIN_LED);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // If keyboard is disconnected, clear matrix
    if (hid_disconnect_flag) {
        for (uint8_t rowIdx = 0; rowIdx < MATRIX_ROWS; rowIdx++) {
            if (current_matrix[rowIdx] != 0) {
                matrix_has_changed     = true;
                current_matrix[rowIdx] = 0;
            }
        }

        hid_disconnect_flag = false;

        return matrix_has_changed;
    }

    // If keyboard report is received, apply it to matrix
    if (hid_report_size > 0) {
        matrix_dest        = current_matrix;
        matrix_has_changed = parse_report(hid_instance, hid_report_buffer, hid_report_size);
        hid_report_size    = 0;
        return matrix_has_changed;
    } else {
        return false;
    }

    return matrix_has_changed;
}

void housekeeping_task_kb(void) {
    // Control keyboard indicator LED
    static uint8_t keyboard_led;
    if (keyboard_led != host_keyboard_leds()) {
        uint8_t led_backup = keyboard_led;
        keyboard_led       = host_keyboard_leds();
        if (!send_led_report(&keyboard_led)) {
            keyboard_led = led_backup;
        }
    }

    // Blink LED when USB reports are received
    if (led_count >= 0) {
        if (timer_elapsed(led_count) < LED_BLINK_TIME_MS) {
            writePinLow(KQ_PIN_LED);
        } else if (timer_elapsed(led_count) < 2 * LED_BLINK_TIME_MS) {
            writePinHigh(KQ_PIN_LED);
        } else {
            led_count = -1;
        }
    }

    housekeeping_task_user();
}

static bool send_led_report(uint8_t* leds) {
    if (kbd_addr != 0) {
        return tuh_hid_set_report(kbd_addr, kbd_instance, 0, HID_REPORT_TYPE_OUTPUT, leds, sizeof(*leds));
    }

    return false;
}

static volatile bool set_protocol_complete = false;
void                 tuh_hid_set_protocol_complete_cb(uint8_t dev_addr, uint8_t instance, uint8_t protocol) {
    set_protocol_complete = true;
}

void tuh_mount_cb(uint8_t dev_addr) {
    dprintf("USB device is mounted:%d\n", dev_addr);

    if (led_count < 0) {
        led_count = timer_read();
    }

    for (int instance = 0; instance < tuh_hid_instance_count(dev_addr); instance++) {
        uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);
        if (itf_protocol == HID_ITF_PROTOCOL_KEYBOARD) {
            kbd_addr     = dev_addr;
            kbd_instance = instance;
        }
    }
}

void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len) {
    dprintf("HID is mounted:%d:%d\n", dev_addr, instance);
    parse_report_descriptor((dev_addr * 16) + instance, desc_report, desc_len);
    tuh_hid_receive_report(dev_addr, instance);
}

void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance) {
    dprintf("HID unmounted:%d:%d\n", dev_addr, instance);
    memset(pre_keyreport, 0, sizeof(pre_keyreport));
    hid_disconnect_flag = true;
    kbd_addr            = 0;
    kbd_instance        = 0;
}

void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len) {
    dprintf("Report received\n");
    if (led_count < 0) {
        led_count = timer_read();
    }

    if (len > 0) {
        int cnt = 0;
        while (hid_report_size > 0 && cnt++ < 50000) {
            busy_wait_us(1);
            continue;
        }

        hid_instance = (dev_addr * 16) + instance;
        memcpy(hid_report_buffer, report, len);
        __compiler_memory_barrier();
        // hid_report_size is used as trigger of report parser
        hid_report_size = len;
    }

    tuh_hid_receive_report(dev_addr, instance);
}

__attribute__((weak)) void keyboard_report_hook(keyboard_parse_result_t const* report) {
    if (debug_enable) {
        uprintf("Keyboard report\n");
        for (int idx = 0; idx < sizeof(report->bits); idx++) {
            uprintf("%02X ", report->bits[idx]);
        }
        uprintf("\n");
    }

    for (uint8_t rowIdx = 0; rowIdx < MATRIX_ROWS - 1; rowIdx++) {
        matrix_dest[rowIdx] = report->bits[rowIdx];
    }

    // copy modifier bits
    matrix_dest[KC_LEFT_CTRL / 8] = report->bits[28];
}

__attribute__((weak)) void mouse_report_hook(mouse_parse_result_t const* report) {
    if (debug_enable) {
        uprintf("Mouse report\n");
        uprintf("b:%d ", report->button);
        uprintf("x:%d ", report->x);
        uprintf("y:%d ", report->y);
        uprintf("v:%d ", report->v);
        uprintf("h:%d ", report->h);
        uprintf("undef:%u\n", report->undefined);
    }

    mouse_send_flag = true;

    report_mouse_t mouse = pointing_device_get_report();

    mouse.buttons = report->button;

    mouse.x += report->x;
    mouse.y += report->y;
    mouse.v += report->v;
    mouse.h += report->h;

    pointing_device_set_report(mouse);
}

bool pointing_device_task(void) {
    if (mouse_send_flag) {
        bool send_report = pointing_device_send();
        mouse_send_flag = false;
        return send_report;
    }

    return false;
}

void vendor_report_parser(uint16_t usage_id, hid_report_member_t const* member, uint8_t const* data, uint8_t len) {
    // For Lenovo thinkpad keyboard(17ef:6047)
    // TODO: restriction by VID:PID
    if (usage_id == 0xFFA1) {
        mouse_parse_result_t mouse = {0};
        mouse.h                    = (data[0] & 0x80 ? 0xFF00 : 0) | data[0];
        mouse_report_hook(&mouse);
    }
}

__attribute__((weak)) void system_report_hook(uint16_t report) {
    host_system_send(report);
    wait_ms(TAP_CODE_DELAY);
    host_system_send(0);
}

__attribute__((weak)) void consumer_report_hook(uint16_t report) {
    host_consumer_send(report);
    wait_ms(TAP_CODE_DELAY);
    host_consumer_send(0);
}
