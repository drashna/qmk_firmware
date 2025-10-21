// Copyright 2023 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include "c1.h"
#include "tusb.h"
#include "pio_usb.h"
#include "pio_usb_ll.h"
#include "hardware/sync.h"
#include "pico/time.h"

// Correct pin definitions for Adafruit Feather RP2040 with USB Host
#define PIO_USB_PIN_DP 16 // D+ on GPIO 16
#define PIN_VBUS       18 // VBUS enable on GPIO 18


// dummy implementation
bool alarm_pool_add_repeating_timer_us(alarm_pool_t *pool, int64_t delay_us, repeating_timer_callback_t callback, void *user_data, repeating_timer_t *out) {
    return true;
}
alarm_pool_t *alarm_pool_create(unsigned int hardware_alarm_num, unsigned int max_timers) {
    return NULL;
}

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