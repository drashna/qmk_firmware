/*
Copyright 2022 Jeff Shufelt <jshuf@puppyfish.com> @jshuf

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

// We have 1 2-bit layout option and 13 1-bit layout options
// in the VIA usb_usb.json, so we need 15 bits (2 bytes)
// of layout option storage.
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2
#define DYNAMIC_KEYMAP_LAYER_COUNT 3
