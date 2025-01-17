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

#define HAL_USE_COMMUNITY           TRUE
#define HAL_USE_FSMC                FALSE
#define HAL_USE_SDRAM               FALSE
#define HAL_USE_CRC                 FALSE
#define HAL_USE_RNG                 FALSE
#define HAL_USE_USBH                TRUE
#define HAL_USBH_USE_HID            TRUE
#include_next "lib/chibios-contrib/testhal/STM32/STM32F4xx/USB_HOST/halconf_community.h"

#undef HAL_USBH_USE_ADDITIONAL_CLASS_DRIVERS
#define HAL_USBH_USE_ADDITIONAL_CLASS_DRIVERS FALSE

#undef USBH_DEBUG_SINGLE_HOST_SELECTION
#define USBH_DEBUG_SINGLE_HOST_SELECTION    USBHD2

#undef HAL_USBH_USE_MSD
#define HAL_USBH_USE_MSD                              FALSE
#undef HAL_USBH_USE_FTDI
#define HAL_USBH_USE_FTDI                             FALSE
#undef HAL_USBH_USE_AOA
#define HAL_USBH_USE_AOA                              FALSE
#undef HAL_USBH_USE_UVC
#define HAL_USBH_USE_UVC                              FALSE

#undef USBH_DEBUG_ENABLE
#define USBH_DEBUG_ENABLE FALSE
