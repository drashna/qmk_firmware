// Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    RTC_AM = 0x00, /**< am */
    RTC_PM = 0x01, /**< pm */
} rtc_time_am_pm_t;

typedef enum {
    RTC_FORMAT_12H = 0x01, /**< 12h format */
    RTC_FORMAT_24H = 0x00, /**< 24h format */
} rtc_time_format_t;

typedef enum {
    RTC_SUNDAY    = 0x00, /**< sunday */
    RTC_MONDAY    = 0x01, /**< monday */
    RTC_TUESDAY   = 0x02, /**< tuesday */
    RTC_WEDNESDAY = 0x03, /**< wednesday */
    RTC_THURSDAY  = 0x04, /**< thursday */
    RTC_FRIDAY    = 0x05, /**< friday */
    RTC_SATURDAY  = 0x06, /**< saturday */
} rtc_time_day_of_the_week_t;

typedef struct {
    uint16_t                   year;            /**< year */
    uint8_t                    month;           /**< month */
    uint8_t                    date;            /**< date */
    rtc_time_day_of_the_week_t day_of_the_week; /**< week */
    uint8_t                    hour;            /**< hour */
    uint8_t                    minute;          /**< minute */
    uint8_t                    second;          /**< second */
    rtc_time_format_t          format;          /**< data format */
    rtc_time_am_pm_t           am_pm;           /**< am pm */
    uint32_t                   unixtime;        /**< Unix Time */
} rtc_time_t;


#define SECONDS_FROM_1970_TO_2000 946684800
#define TIME_OFFSET 6

void rtc_init(void);
void rtc_task(void);

uint32_t convert_to_unixtime(rtc_time_t time);
rtc_time_t convert_date_time(const char *date, const char *time);
uint8_t rtc_bcd2bin(uint8_t val);
uint8_t rtc_bin2bcd(uint8_t val);
uint8_t week_to_int(uint8_t d);


rtc_time_t rtc_read_time_struct(void);
char *rtc_read_date_str(void);
char *rtc_read_time_str(void);
char *rtc_read_date_time_str(void);
char *rtc_read_date_time_iso8601_str(void);

bool rtc_is_connected(void);
void rtc_set_time_split(rtc_time_t time, bool is_connected);
uint32_t get_fattime(void);
