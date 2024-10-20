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

#include <stdint.h>
#include <stdbool.h>

#include <transactions.h>

// initiator is transaction start side
void soft_serial_initiator_init(void);
// target is interrupt accept side
void soft_serial_target_init(void);

bool soft_serial_transaction(int sstd_index);

#ifdef SERIAL_DEBUG
#    include <debug.h>
#    include <print.h>
#    define serial_dprintf(fmt, ...)                                     \
        do {                                                      \
            if (debug_config.serial) xprintf(fmt, ##__VA_ARGS__); \
        } while (0)
#else
#    define serial_dprintf(...) \
        do {                    \
        } while (0)
#endif
