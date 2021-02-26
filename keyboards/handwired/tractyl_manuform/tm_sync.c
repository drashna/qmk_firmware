#include "tractyl_manuform.h"
#include <split_sync.h>
#include <string.h>

kb_runtime_config_t kb_state;
kb_slave_data_t     kb_slave;
enum { KB_STATE_SYNC = SAFE_KB_SPLIT_TRANSACTION_ID, KB_SLAVE_SYNC };

void keyboard_post_init_kb(void) {
    // Register keyboard state sync split transaction
    split_sync_register_m2s_transaction(KB_STATE_SYNC, sizeof(kb_state), &kb_state);
    split_sync_register_s2m_transaction(KB_SLAVE_SYNC, sizeof(kb_slave), &kb_slave);

    // Reset the initial shared data value between master and slave
    memset(&kb_state, 0, sizeof(kb_state));
    memset(&kb_slave, 0, sizeof(kb_slave));

    keyboard_post_init_user();
}

void kb_state_update(void) {
    if (is_keyboard_master()) {
#ifdef POINTING_DEVICE_ENABLE
        if (is_keyboard_left()) {
            report_mouse_t temp_report = pointing_device_get_report();
            temp_report.x              = kb_slave.mouse_x;
            temp_report.y              = kb_slave.mouse_y;
            pointing_device_set_report(temp_report);
        }
#endif
    } else {
#ifdef POINTING_DEVICE_ENABLE
        if (!is_keyboard_left()) {
            static uint16_t cpi;
            if (cpi != kb_state.device_cpi) {
                cpi = kb_state.device_cpi;
                pmw_set_cpi(cpi);
            }
        }
#endif
    }
}

void kb_state_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static kb_runtime_config_t last_kb_state;
        static kb_slave_data_t     last_kb_slave;
        static uint32_t            last_sync;
        bool                       needs_sync = false;

        // Check if the state values are different
        if (memcmp(&kb_state, &last_kb_state, sizeof(kb_runtime_config_t))) {
            needs_sync = true;
            memcpy(&last_kb_state, &kb_state, sizeof(kb_runtime_config_t));
        }
        if (memcmp(&kb_slave, &last_kb_slave, sizeof(kb_slave_data_t))) {
            memcpy(&last_kb_slave, &kb_slave, sizeof(kb_slave_data_t));
        }

        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync) > 500) {
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
    kb_state_update();

    // Data sync from master to slave
    kb_state_sync();
}
