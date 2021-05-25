
/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef SPLIT_TRANSACTION_IDS_USER
#    include "drashna_sync.h"
#    include "transactions.h"
#    include <string.h>

typedef struct {
    bool            oled_on;
    uint16_t keymap_config;
} user_runtime_config_t;

user_runtime_config_t user_state_sync;

void user_state_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(user_state_sync)) {
        memcpy(&user_state_sync, initiator2target_buffer, initiator2target_buffer_size);
    }
}

void keyboard_post_init_transport_sync(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(USER_STATE_SYNC, user_state_sync_handler);
}

void housekeeping_task_transport_sync(void) {
    if (is_keyboard_master()) {
#ifdef OLED_DRIVER_ENABLE
        user_state_sync.oled_on = is_oled_on();
#endif
        user_state_sync.keymap_config = keymap_config.raw;
    } else {
#ifdef OLED_DRIVER_ENABLE
        if (user_state_sync.oled_on) {
            oled_on();
        } else {
            oled_off();
        }
#endif
        if (keymap_config.raw != user_state_sync.keymap_config) {
            keymap_config.raw = user_state_sync.keymap_config;
        }
    }

    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static user_runtime_config_t last_state;
        static uint32_t              last_sync;
        bool                         needs_sync = false;

        // Check if the state values are different
        if (memcmp(&user_state_sync, &last_state, sizeof(user_state_sync))) {
            needs_sync = true;
            memcpy(&last_state, &user_state_sync, sizeof(user_state_sync));
        }

        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(USER_STATE_SYNC, sizeof(user_state_sync), &user_state_sync)) {
                last_sync = timer_read32();
            }
        }
    }
}

#endif
