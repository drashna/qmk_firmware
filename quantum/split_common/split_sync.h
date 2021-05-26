/* Copyright 2021 QMK
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

#pragma once

// Number of extra transaction IDs that can be used by keyboard code
#ifndef SPLIT_NUM_TRANSACTIONS_KB
#    define SPLIT_NUM_TRANSACTIONS_KB 0
#endif  // SPLIT_NUM_TRANSACTIONS_KB

// Number of extra transaction IDs that can be used by user/keymap code
#ifndef SPLIT_NUM_TRANSACTIONS_USER
#    define SPLIT_NUM_TRANSACTIONS_USER 0
#endif  // SPLIT_NUM_TRANSACTIONS_USER

// List of transaction IDs
enum split_transaction_id {
    // Transaction IDs usable by keyboard
    SAFE_KB_SPLIT_TRANSACTION_ID = 0,

    // Transaction IDs usable by user/keymap
    SAFE_USER_SPLIT_TRANSACTION_ID = SAFE_KB_SPLIT_TRANSACTION_ID + (SPLIT_NUM_TRANSACTIONS_KB),

    // Total number of transaction IDs
    NUM_SPLIT_TRANSACTIONS = SAFE_USER_SPLIT_TRANSACTION_ID + (SPLIT_NUM_TRANSACTIONS_USER),
};

#if defined(SERIAL_USE_MULTI_TRANSACTION) && ( defined(SPLIT_NUM_TRANSACTIONS_KB) || defined(SPLIT_NUM_TRANSACTIONS_USER))
void split_sync_register_transaction(enum split_transaction_id id, uint8_t initiator2target_buffer_size, void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer);
#    define split_sync_register_m2s_transaction(id, buffer_size, buffer) split_sync_register_transaction(id, buffer_size, buffer, 0, NULL)
#    define split_sync_register_s2m_transaction(id, buffer_size, buffer) split_sync_register_transaction(id, 0, NULL, buffer_size, buffer)

bool split_sync_execute_transaction(enum split_transaction_id id);
#endif  // SERIAL_USE_MULTI_TRANSACTION
