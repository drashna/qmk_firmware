
#include "transport_sync.h"
#include <split_sync.h>
#include <string.h>

enum { USER_STATE_SYNC = SAFE_USER_SPLIT_TRANSACTION_ID };

typedef struct {
    bool            oled_on;
    layer_state_t   layer_state;
    layer_state_t   default_layer_state;
    bool            is_rgb_matrix_suspended;
    keymap_config_t keymap_config;
} user_runtime_config_t;

user_runtime_config_t user_state;

void keyboard_post_init_transport_sync(void) {
    // Register keyboard state sync split transaction
    split_sync_register_m2s_transaction(USER_STATE_SYNC, sizeof(user_state), &user_state);

    // Reset the initial shared data value between master and slave
    memset(&user_state, 0, sizeof(user_state));
}

void user_state_update(void) {
    if (is_keyboard_master()) {
        // Keep the layer state in sync
        user_state.layer_state         = layer_state;
        user_state.default_layer_state = default_layer_state;

#ifdef OLED_DRIVER_ENABLE
        user_state.oled_on = is_oled_on();
#endif

#ifdef RGB_MATRIX_ENABLE
        user_state.is_rgb_matrix_suspended = rgb_matrix_get_suspend_state();
#endif
        user_state.keymap_config = keymap_config;

    } else {
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
        static user_runtime_config_t last_user_state;
        static uint32_t              last_sync;
        bool                         needs_sync = false;

        // Check if the state values are different
        if (memcmp(&user_state, &last_user_state, sizeof(user_runtime_config_t))) {
            needs_sync = true;
            memcpy(&last_user_state, &user_state, sizeof(user_runtime_config_t));
        }

        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            last_sync = timer_read32();
            if (!split_sync_execute_transaction(USER_STATE_SYNC)) {
                dprint("Failed to perform sync data transaction\n");
            }
        }
    }
}

void housekeeping_task_user(void) {
    // Update kb_state so we can send to slave
    user_state_update();

    // Data sync from master to slave
    user_state_sync();
}
