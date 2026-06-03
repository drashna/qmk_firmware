/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
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

#define UNUSABLE_PINS \
    { GP1, GP2, GP3, GP4, \
      GP7, GP8, GP9, GP10, GP11, GP12, GP13, GP14, GP15, GP16, GP17, GP18, GP19, \
      GP21, GP22, \
      GP25, GP26, GP27, GP28, GP29 \
    }

/* TMAG5273 Pointing Device Settings */
#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP0
#define I2C1_SCL_PIN GP5

// Timeout for combo keys, in ms. Default is 50.
#define COMBO_TERM 200
#define COMBO_MUST_PRESS_IN_ORDER
#define COMBO_MUST_HOLD_PER_COMBO

#define PLOOPY_DRAGSCROLL_MOMENTARY
#define PLOOPY_DRAGSCROLL_DIVISOR_H 1.0
#define PLOOPY_DRAGSCROLL_DIVISOR_V 1.0
#define PLOOPY_DRAGSCROLL_INVERT
// Windows starts beeping if we send scroll events too quickly.
#define PLOOPY_DRAGSCROLL_RATE_LIMIT 20

#define SCROLL_DIRECTION_LOCK_ENABLE
#define POINTING_DEVICE_TASK_THROTTLE_MS 2
#define PLOOPY_DPI_DEFAULT 1
#define POINTING_DEVICE_HIRES_SCROLL_ENABLE
#define WHEEL_EXTENDED_REPORT
