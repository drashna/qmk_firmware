// Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rtc/vendor.h"
#include <hal.h>
#include "debug.h"
#include <math.h>
#include "print.h"
#include "rtc/rtc.h"
#include "timer.h"
#include <stdio.h>


void convert_halrtc_to_local_rtc_struct(RTCDateTime *halrtc, rtc_time_t *local) {
    local->year            = halrtc->year + 1980U;
    local->month           = halrtc->month;
    local->day_of_the_week = halrtc->dayofweek;
    local->date            = halrtc->day;
    local->second          = (halrtc->millisecond / 1000) % 60;
    local->minute          = (local->second / 60) % 60;
    local->hour            = (local->minute / 60) % 24;

    local->unixtime = convert_to_unixtime(*local);
}

void convert_local_rtc_to_halrtc_struct(rtc_time_t *local, RTCDateTime *halrtc) {
    halrtc->year        = local->year - 1980U;
    halrtc->month       = local->month;
    halrtc->dayofweek   = local->day_of_the_week;
    halrtc->day         = local->date;
    halrtc->millisecond = (local->second + (local->minute * 60) + (local->hour * 60 * 60)) * 1000;
}

void vendor_rtc_set_time(rtc_time_t time) {
    RTCDateTime timespec = {0};
    convert_local_rtc_to_halrtc_struct(&time, &timespec);
    rtcSetTime(&RTCD1, &timespec);
}

void vendor_rtc_get_time(rtc_time_t *time) {
    RTCDateTime timespec = {0};
    rtcGetTime(&RTCD1, &timespec);
    convert_halrtc_to_local_rtc_struct(&timespec, time);
}

bool vendor_rtc_init(rtc_time_t *time) {
    vendor_rtc_get_time(time);

    if (time->year < 2000) {
        dprintf("Vendor RTC: Date/time not set. Setting to compiled date/time as fallback!\n");
        vendor_rtc_set_time(convert_date_time(__DATE__, __TIME__));
    }
    return true;
}

bool vendor_rtc_task(rtc_time_t *time) {
    vendor_rtc_get_time(time);
    return true;
}
