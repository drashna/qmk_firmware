// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "rtc/rtc.h"
#include <stdint.h>
#include <stdbool.h>

void vendor_rtc_set_time(rtc_time_t time);
void vendor_rtc_get_time(rtc_time_t *time);
bool vendor_rtc_init(rtc_time_t *time);
bool vendor_rtc_task(rtc_time_t *time);
