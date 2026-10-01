/* Copyright 2026 QMK
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

// This codec is only meaningful for the wide wire format; every backend keeps its legacy
// framing verbatim under #else, so there is nothing to compile here when the flag is off.
#if defined(SPLIT_WIDE_TRANSACTION_IDS)

#    include <stdint.h>
#    include <stdbool.h>

#    include "crc.h"
#    include "transaction_id_define.h"

// Wide transaction header, wire layout, big-endian: [ id 15:6 ][ check 5:0 ].
//
// The check is a crc8() over the id alone -- the ten-bit value zero-extended to uint16_t and
// serialised big-endian -- masked to six bits, so both encode and decode hash identical bytes
// regardless of where the check field ends up in the final word.
static inline void split_txn_header_encode(split_transaction_id_t id, uint8_t out[2]) {
    uint8_t  id_bytes[2] = {(uint8_t)(id >> 8), (uint8_t)(id & 0xFF)};
    uint8_t  check       = crc8(id_bytes, sizeof(id_bytes)) & 0x3F;
    uint16_t header      = (uint16_t)((id << 6) | check);
    out[0]               = (uint8_t)(header >> 8);
    out[1]               = (uint8_t)(header & 0xFF);
}

// Validates the check field and the id range; this is the only place either test is expressed.
static inline bool split_txn_header_decode(const uint8_t in[2], split_transaction_id_t *out) {
    uint16_t header       = (uint16_t)(((uint16_t)in[0] << 8) | in[1]);
    uint16_t id           = header >> 6;
    uint8_t  check        = header & 0x3F;
    uint8_t  id_bytes[2]  = {(uint8_t)(id >> 8), (uint8_t)(id & 0xFF)};
    uint8_t  expect_check = crc8(id_bytes, sizeof(id_bytes)) & 0x3F;

    if (check != expect_check || id >= NUM_TOTAL_TRANSACTIONS) {
        return false;
    }

    *out = (split_transaction_id_t)id;
    return true;
}

#endif // defined(SPLIT_WIDE_TRANSACTION_IDS)
