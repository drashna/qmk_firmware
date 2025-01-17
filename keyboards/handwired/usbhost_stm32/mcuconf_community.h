/* Copyright 2020 Nick Brassel (tzarc)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "lib/chibios-contrib/testhal/STM32/STM32F4xx/USB_HOST/mcuconf_community.h"

#undef STM32_USBH_USE_OTG1
#define STM32_USBH_USE_OTG1          FALSE

#undef STM32_USBH_USE_OTG2
#define STM32_USBH_USE_OTG2          TRUE

#undef STM32_OTG2_USE_ULPI
#define STM32_OTG2_USE_ULPI          FALSE
