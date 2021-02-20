
#include "drashna.h"
#include <split_sync.h>
#include <string.h>

enum { KB_STATE_SYNC = SAFE_KB_SPLIT_TRANSACTION_ID, KB_SLAVE_SYNC };

typedef struct user_runtime_config {
    uint16_t        device_cpi;
    bool            oled_on;
    layer_state_t   layer_state;
    layer_state_t   default_layer_state;
    bool            is_rgb_matrix_suspended;
    keymap_config_t keymap_config;
} user_runtime_config;

typedef struct user_slave_data {
    int8_t mouse_x;
    int8_t mouse_y;
} user_slave_data;

user_runtime_config user_state;
user_slave_data     user_slave;

void keyboard_post_init_keymap(void) {
    // Register keyboard state sync split transaction
    split_sync_register_m2s_transaction(KB_STATE_SYNC, sizeof(user_state), &user_state);
    split_sync_register_s2m_transaction(KB_SLAVE_SYNC, sizeof(user_slave), &user_slave);

    // Reset the initial shared data value between master and slave
    memset(&user_state, 0, sizeof(user_state));
    memset(&user_slave, 0, sizeof(user_slave));
}

void user_state_update(void) {
    if (is_keyboard_master()) {
        // Keep the layer state in sync
        user_state.layer_state         = layer_state;
        user_state.default_layer_state = default_layer_state;
#ifdef POINTING_DEVICE_ENABLE
        if (is_keyboard_left()) {
            report_mouse_t temp_report = pointing_device_get_report();
            temp_report.x              = user_slave.mouse_x;
            temp_report.y              = user_slave.mouse_y;
            pointing_device_set_report(temp_report);
        }
#endif
#ifdef OLED_DRIVER_ENABLE
        user_state.oled_on = is_oled_on();
#endif

#ifdef RGB_MATRIX_ENABLE
        user_state.is_rgb_matrix_suspended = rgb_matrix_get_suspend_state();
#endif
    user_state.keymap_config = keymap_config;

    } else {
#ifdef POINTING_DEVICE_ENABLE
        if (!is_keyboard_left()) {
            static uint16_t cpi;
            if (cpi != user_state.device_cpi) {
                cpi = user_state.device_cpi;
                pmw_set_cpi(cpi);
            }
        }
#endif
        if (layer_state != user_state.layer_state) {
            layer_state = user_state.layer_state;
        }
        if (default_layer_state != user_state.default_layer_state) {
            default_layer_state = user_state.default_layer_state;
        }
#ifdef OLED_DRIVER_ENABLE
        if (user_state.oled_on) {
            oled_on();
        } else {
            oled_off();
        }
#endif
        if (keymap_config.raw != user_state.keymap_config.raw) {
            keymap_config = user_state.keymap_config;
        }

#ifdef RGB_MATRIX_ENABLE
        rgb_matrix_set_suspend_state(user_state.is_rgb_matrix_suspended);
#endif
    }
}

void user_state_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static user_runtime_config last_user_state;
        static user_slave_data     last_user_slave;
        static uint32_t            last_sync;
        bool                       needs_sync = false;

        // Check if the state values are different
        if (memcmp(&user_state, &last_user_state, sizeof(user_runtime_config))) {
            needs_sync = true;
            memcpy(&last_user_state, &user_state, sizeof(user_runtime_config));
        }
        if (memcmp(&user_slave, &last_user_slave, sizeof(user_slave_data))) {
            memcpy(&last_user_slave, &user_slave, sizeof(user_slave_data));
        }

        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            last_sync = timer_read32();
            if (!split_sync_execute_transaction(KB_STATE_SYNC)) {
                dprint("Failed to perform sync data transaction\n");
            }
        }
        // always sync slave data, since it may contain device reports.
        if (!split_sync_execute_transaction(KB_SLAVE_SYNC)) {
            dprint("Failed to perform slave data transaction\n");
        }
    }
}

void housekeeping_task_kb(void) {
    // Update kb_state so we can send to slave
    user_state_update();

    // Data sync from master to slave
    user_state_sync();
}

#ifdef POINTING_DEVICE_ENABLE
void master_mouse_send(int8_t x, int8_t y) {
    user_slave.mouse_x = x;
    user_slave.mouse_y = y;
}
void trackball_set_cpi(uint16_t cpi) {
    if (!is_keyboard_left()) {
        pmw_set_cpi(cpi);
    } else {
        user_state.device_cpi = cpi;
    }
}
#endif
