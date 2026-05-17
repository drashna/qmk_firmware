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

#pragma once

#include "quantum.h"
#include "default_keyboard.h"

#define DPI_RMOD POINTER_DEFAULT_DPI_REVERSE
#define S_D_RMOD POINTER_SNIPING_DPI_REVERSE

// DPI/sniper-mode configuration, EEPROM persistence, split sync and keycodes
// are provided by the `drashna/charybdis_config` community module.
#ifdef COMMUNITY_MODULE_CHARYBDIS_CONFIG_ENABLE
#    include "charybdis_config.h"
#endif // COMMUNITY_MODULE_CHARYBDIS_CONFIG_ENABLE

#ifdef POINTING_DEVICE_ENABLE
/** \brief Whether drag-scroll is enabled. */
bool charybdis_get_pointer_dragscroll_enabled(void);

/**
 * \brief Enable/disable drag-scroll mode.
 *
 * When drag-scroll mode is enabled, horizontal and vertical pointer movements
 * are translated into horizontal and vertical scroll movements.
 */
void charybdis_set_pointer_dragscroll_enabled(bool enable);
#endif // POINTING_DEVICE_ENABLE
