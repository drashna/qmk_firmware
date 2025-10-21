// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "c1.h"
#include "tusb.h"
#include "pio_usb.h"
#include "pio_usb_ll.h"
#include "hardware/sync.h"

// Correct pin definitions for Adafruit Feather RP2040 with USB Host
#define PIO_USB_PIN_DP 16 // D+ on GPIO 16
#define PIN_VBUS       18 // VBUS enable on GPIO 18

// dummy implementation
void alarm_pool_add_repeating_timer_us(void) {}
void alarm_pool_create(void) {}

// Initialize USB host stack on core1
void c1_usbh(void) {
    pio_usb_configuration_t pio_cfg = PIO_USB_DEFAULT_CONFIG;
    pio_cfg.pin_dp                  = PIO_USB_PIN_DP; // D+ on GPIO 16
    pio_cfg.skip_alarm_pool         = true;
    tuh_configure(1, TUH_CFGID_RPI_PIO_USB_CONFIGURATION, &pio_cfg);

    gpio_init(PIN_VBUS); // Use correct VBUS enable pin
    gpio_set_dir(PIN_VBUS, GPIO_OUT);
    gpio_put(PIN_VBUS, 1);

    tuh_init(1);
    c1_start_timer();
}

// USB host stack main task
void c1_main_task(void) {
    tuh_task();
}