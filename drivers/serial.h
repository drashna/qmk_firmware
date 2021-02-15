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

#include <stdbool.h>

// /////////////////////////////////////////////////////////////////
//
// //// USE simple API (using signle-type transaction function)
//   /* nothing */
// //// USE flexible API (using multi-type transaction function)
//   #define SERIAL_USE_MULTI_TRANSACTION
//
// /////////////////////////////////////////////////////////////////

// Soft Serial Transaction Descriptor
typedef struct _SSTD_t {
    uint8_t *status;
    uint8_t  initiator2target_buffer_size;
    uint8_t *initiator2target_buffer;
    uint8_t  target2initiator_buffer_size;
    uint8_t *target2initiator_buffer;
} SSTD_t;
#define TID_LIMIT(table) (sizeof(table) / sizeof(SSTD_t))

// initiator is transaction start side
void soft_serial_initiator_init(SSTD_t *sstd_table, int sstd_table_size);
// target is interrupt accept side
void soft_serial_target_init(SSTD_t *sstd_table, int sstd_table_size);

// initiator result
#define TRANSACTION_END 0
#define TRANSACTION_NO_RESPONSE 0x1
#define TRANSACTION_DATA_ERROR 0x2
#define TRANSACTION_TYPE_ERROR 0x4
#ifndef SERIAL_USE_MULTI_TRANSACTION
int soft_serial_transaction(void);
#else
int soft_serial_transaction(int sstd_index);
#endif

// target status
// *SSTD_t.status has
//   initiator:
//       TRANSACTION_END
//    or TRANSACTION_NO_RESPONSE
//    or TRANSACTION_DATA_ERROR
//   target:
//       TRANSACTION_DATA_ERROR
//    or TRANSACTION_ACCEPTED
#define TRANSACTION_ACCEPTED 0x8
#ifdef SERIAL_USE_MULTI_TRANSACTION
int soft_serial_get_and_clean_status(int sstd_index);
#endif
