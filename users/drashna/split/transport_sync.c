// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "transport_sync.h"
#include "_wait.h"
#include "drashna.h"
#include "transactions.h"
#include <string.h>

#ifdef UNICODE_COMMON_ENABLE
#    include "process_unicode_common.h"
extern unicode_config_t unicode_config;
#    include "keyrecords/unicode.h"
#endif
#ifdef AUDIO_ENABLE
#    include "audio.h"
extern audio_config_t audio_config;
extern bool           delayed_tasks_run;
#endif
#if defined(POINTING_DEVICE_ENABLE) && defined(KEYBOARD_handwired_tractyl_manuform)
extern bool tap_toggling;
#endif
#ifdef SWAP_HANDS_ENABLE
extern bool swap_hands;
#endif
#ifdef CUSTOM_OLED_ENABLE
#    include "oled/oled_stuff.h"
#endif

extern userspace_config_t userspace_config;
_Static_assert(sizeof(userspace_config_t) <= RPC_M2S_BUFFER_SIZE, "userspace_config_t is larger than split buffer size!");

uint16_t transport_keymap_config    = 0;
uint32_t transport_userspace_config = 0, transport_user_state = 0;

user_runtime_config_t user_state;

void user_state_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_user_state)) {
        memcpy(&transport_user_state, initiator2target_buffer, initiator2target_buffer_size);
    }
}
void user_keymap_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_keymap_config)) {
        memcpy(&transport_keymap_config, initiator2target_buffer, initiator2target_buffer_size);
    }
}
void user_config_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_userspace_config)) {
        memcpy(&transport_userspace_config, initiator2target_buffer, initiator2target_buffer_size);
    }
}

#if defined(AUTOCORRECT_ENABLE)
extern char autocorrected_str[2][22];
_Static_assert(sizeof(autocorrected_str) <= RPC_M2S_BUFFER_SIZE, "Autocorrect array larger than buffer size!");

void autocorrect_string_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == (sizeof(autocorrected_str))) {
        memcpy(&autocorrected_str, initiator2target_buffer, initiator2target_buffer_size);
    }
}
#endif
#ifdef CUSTOM_OLED_DRIVER
void keylogger_string_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == (OLED_KEYLOGGER_LENGTH+1)) {
        memcpy(&oled_keylog_str, initiator2target_buffer, initiator2target_buffer_size);
    }
}
#endif

void suspend_state_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    bool suspend_state;
    memcpy(&suspend_state, initiator2target_buffer, initiator2target_buffer_size);
    if (suspend_state != is_device_suspended()) {
        set_is_device_suspended(suspend_state);
    }
}

void send_device_suspend_state(bool status) {
    if (is_device_suspended() != status && is_keyboard_master()) {
        transaction_rpc_send(RPC_ID_USER_SUSPEND_STATE_SYNC, sizeof(bool), &status);
        wait_ms(5);
    }
}

void keyboard_post_init_transport_sync(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(RPC_ID_USER_STATE_SYNC, user_state_sync);
    transaction_register_rpc(RPC_ID_USER_KEYMAP_SYNC, user_keymap_sync);
    transaction_register_rpc(RPC_ID_USER_CONFIG_SYNC, user_config_sync);
#if defined(AUTOCORRECT_ENABLE)
    transaction_register_rpc(RPC_ID_USER_AUTOCORRECT_STR, autocorrect_string_sync);
#endif
#ifdef CUSTOM_OLED_DRIVER
    transaction_register_rpc(RPC_ID_USER_OLED_KEYLOG_STR, keylogger_string_sync);
#endif
    transaction_register_rpc(RPC_ID_USER_SUSPEND_STATE_SYNC, suspend_state_sync);
}

void user_transport_update(void) {
    if (is_keyboard_master()) {
        transport_keymap_config    = keymap_config.raw;
        transport_userspace_config = userspace_config.raw;
#ifdef AUDIO_ENABLE
        user_state.audio_enable        = is_audio_on();
        user_state.audio_clicky_enable = is_clicky_on();
#endif
#if defined(POINTING_DEVICE_ENABLE) && defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE)
        user_state.tap_toggling = get_auto_mouse_toggle();
#endif
#ifdef UNICODE_COMMON_ENABLE
        user_state.unicode_mode        = unicode_config.input_mode;
        user_state.unicode_typing_mode = unicode_typing_mode;
#endif
#ifdef SWAP_HANDS_ENABLE
        user_state.swap_hands = swap_hands;
#endif
        user_state.host_driver_disabled = get_keyboard_lock();
        transport_user_state = user_state.raw;
    } else {
        keymap_config.raw    = transport_keymap_config;
        userspace_config.raw = transport_userspace_config;
        user_state.raw       = transport_user_state;
#ifdef UNICODE_COMMON_ENABLE
        unicode_config.input_mode = user_state.unicode_mode;
        unicode_typing_mode       = user_state.unicode_typing_mode;
#endif
#if defined(POINTING_DEVICE_ENABLE) && defined(POINTING_DEVICE_AUTO_MOUSE_ENABLE)
        if (get_auto_mouse_toggle() != user_state.tap_toggling) {
            auto_mouse_toggle();
        }
#endif
#ifdef SWAP_HANDS_ENABLE
        swap_hands = user_state.swap_hands;
#endif
        set_keyboard_lock(user_state.host_driver_disabled);
    }
}

void user_transport_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static uint16_t last_keymap = 0;
        static uint32_t last_config = 0, last_sync[5], last_user_state = 0;
        bool            needs_sync = false;
#ifdef CUSTOM_OLED_DRIVER
        static char keylog_temp[OLED_KEYLOGGER_LENGTH + 1] = {0};
#endif
#if defined(AUTOCORRECT_ENABLE)
        static char temp_autocorrected_str[2][22] = {0};
#endif

        // Check if the state values are different
        if (memcmp(&transport_user_state, &last_user_state, sizeof(transport_user_state))) {
            needs_sync = true;
            memcpy(&last_user_state, &transport_user_state, sizeof(transport_user_state));
        }
        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync[0]) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_STATE_SYNC, sizeof(user_state), &user_state)) {
                last_sync[0] = timer_read32();
            }
            needs_sync = false;
        }

        // Check if the state values are different
        if (memcmp(&transport_keymap_config, &last_keymap, sizeof(transport_keymap_config))) {
            needs_sync = true;
            memcpy(&last_keymap, &transport_keymap_config, sizeof(transport_keymap_config));
        }

        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync[1]) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_KEYMAP_SYNC, sizeof(transport_keymap_config), &transport_keymap_config)) {
                last_sync[1] = timer_read32();
            }
            needs_sync = false;
        }

        // Check if the state values are different
        if (memcmp(&user_state, &last_config, sizeof(transport_userspace_config))) {
            needs_sync = true;
            memcpy(&last_config, &user_state, sizeof(transport_userspace_config));
        }

        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync[2]) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_CONFIG_SYNC, sizeof(transport_userspace_config), &transport_userspace_config)) {
                last_sync[2] = timer_read32();
            }
            needs_sync = false;
        }

#ifdef CUSTOM_OLED_DRIVER
        // Check if the state values are different
        if (memcmp(&oled_keylog_str, &keylog_temp, OLED_KEYLOGGER_LENGTH + 1)) {
            needs_sync = true;
            memcpy(&keylog_temp, &oled_keylog_str, OLED_KEYLOGGER_LENGTH + 1);
        }
        if (timer_elapsed32(last_sync[3]) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_OLED_KEYLOG_STR, OLED_KEYLOGGER_LENGTH + 1, &oled_keylog_str)) {
                last_sync[3] = timer_read32();
            }
            needs_sync = false;
        }
#endif
#if defined(AUTOCORRECT_ENABLE)
        if (memcmp(&autocorrected_str, &temp_autocorrected_str, sizeof(autocorrected_str))) {
            needs_sync = true;
            memcpy(&temp_autocorrected_str, &autocorrected_str, sizeof(autocorrected_str));
        }
        if (timer_elapsed32(last_sync[4]) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_AUTOCORRECT_STR, sizeof(autocorrected_str), &autocorrected_str)) {
                last_sync[4] = timer_read32();
            }
            needs_sync = false;
        }
#endif
    }
}

void housekeeping_task_transport_sync(void) {
    // Update kb_state so we can send to slave
    user_transport_update();

    // Data sync from master to slave
    user_transport_sync();
}
