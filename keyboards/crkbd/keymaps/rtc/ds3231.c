// Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ds3231.h"
#include "i2c_master.h"
#include "debug.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "print.h"
#include "timer.h"

#ifndef DS3231_READ_INTERVAL
#    define DS3231_READ_INTERVAL 100
#endif

ds3231_time_t   t;
static uint16_t last_rtc_read   = 0;
static bool     rtc_initialized = false, rtc_connected = false;
static float    rtc_temp = 0.0f;

i2c_status_t ds3231_set_byte_reg(uint8_t reg, uint8_t data) {
    uint8_t d[1] = {data};
    return i2c_writeReg(DS3231_I2C_ADDRESS << 1, reg, d, 1, DS3231_I2C_TIMEOUT);
}

i2c_status_t ds3231_get_byte_reg(uint8_t reg, uint8_t *data) {
    return i2c_readReg(DS3231_I2C_ADDRESS << 1, reg, data, 1, DS3231_I2C_TIMEOUT);
}

i2c_status_t ds3231_set_reg(uint8_t reg, uint8_t *data, uint16_t len) {
    return i2c_writeReg(DS3231_I2C_ADDRESS << 1, reg, data, len, DS3231_I2C_TIMEOUT);
}

i2c_status_t ds3231_get_reg(uint8_t reg, uint8_t *data, uint16_t len) {
    return i2c_readReg(DS3231_I2C_ADDRESS << 1, reg, data, len, DS3231_I2C_TIMEOUT);
}

/**
 * @brief returns the current time struct
 *
 * @return ds3231_time_t
 */
ds3231_time_t ds3231_read_time_struct(void) {
    return t;
}

/**
 * @brief returns the connected state of the RTC
 *
 * @return true
 * @return false
 */
bool ds3231_is_connected(void) {
    return rtc_connected;
}

/**
 * @brief Generates a string with the date
 *
 * @return char*
 */
char *ds3231_read_date_str(void) {
    char date_str_temp[14] = {0};
    snprintf(date_str_temp, sizeof(date_str_temp), "%02d/%02d/%04d", t.month, t.date, t.year);
    static char date_str[12] = {0};
    strncpy(date_str, date_str_temp, sizeof(date_str));
    return date_str;
}

/**
 * @brief Generates a string with the time
 *
 * @return char*
 */
char *ds3231_read_time_str(void) {
    char time_str_temp[12];
    snprintf(time_str_temp, sizeof(time_str_temp), "%02d:%02d:%02d", t.hour, t.minute, t.second);
    static char time_str[9] = {0};
    strncpy(time_str, time_str_temp, sizeof(time_str));
    return time_str;
}

/**
 * @brief Generates a string with the date and time
 *
 * @return char*
 */
char *ds3231_read_date_time_str(void) {
    static char date_time_str[21] = {0};
    snprintf(date_time_str, sizeof(date_time_str), "%s %s", ds3231_read_date_str(), ds3231_read_time_str());
    return date_time_str;
}

char *ds3231_read_temp_str(void) {
    static char temp_str[8] = {0};
#if PRINTF_SUPPORT_DECIMAL_SPECIFIERS
    snprintf(temp_str, sizeof(temp_str), "%2.2f", rtc_temp);
#else
#    pragma message "PRINTF_SUPPORT_DECIMAL_SPECIFIERS not enabled, RTC temperature will be rounded to nearest integer"
    uint8_t temp = (uint8_t)round(rtc_temp);
    uint8_t frac = (uint8_t)round((rtc_temp - temp) * 100);
    snprintf(temp_str, sizeof(temp_str), "%2d.%02d", temp, frac);
#endif
    return temp_str;
}

char *ds3232_read_temp_imperial_str(void) {
    static char temp_str[8] = {0};
    float temp_f = (rtc_temp * 9.0f / 5.0f) + 32.0f;
    uint8_t temp = (uint8_t)round(temp_f);
    uint8_t frac = (uint8_t)round((temp_f - temp) * 100);
    snprintf(temp_str, sizeof(temp_str), "%2d.%02d", temp, frac);
    return temp_str;
}


/**
 * @brief Converts a hex value to BCD format, for sending to the DS3231
 *
 * @param val
 * @return uint8_t
 */
static uint8_t ds3231_bcd2hex(uint8_t val) {
    uint8_t temp;

    temp = val & 0x0F;        /* get ones place */
    val  = (val >> 4) & 0x0F; /* get tens place */
    val  = val * 10;          /* set tens place */
    temp = temp + val;        /* get hex */

    return temp; /* return hex */
}

const uint8_t days_in_month[12] PROGMEM = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/**
 * @brief Get the unixtime object
 *
 * @param t time struct
 * @return uint32_t
 */
uint32_t convert_to_unixtime(ds3231_time_t t) {
    uint16_t days;
    int16_t  years;
    uint32_t unixtime;

    if (t.year >= 2000) {
        years = t.year - 2000;
    } else {
        return 0;
    }

    days = t.date - 1;
    for (uint8_t i = 1; i < t.month; i++) {
        days += xpgm_read_byte(days_in_month + i - 1);
    }
    if (t.month > 2 && years % 4 == 0) {
        days++;
    }

    // count leap days
    days += (365 * years + (years + 3) / 4);
    unixtime = ((days * 24UL + t.hour) * 60 + t.minute) * 60 + t.second + SECONDS_FROM_1970_TO_2000 + (TIME_OFFSET * 3000);
    return unixtime;
}

static uint8_t week_to_int(uint8_t d) {
    return d == 0 ? 7 : d;
}

/**
 * @brief convert a date to days
 *
 * @param y
 * @param m
 * @param d
 * @return uint16_t
 */
static uint16_t date_to_days(uint16_t y, uint8_t m, uint8_t d) {
    if (y >= 2000U) y -= 2000U;
    uint16_t days = d;
    for (uint8_t i = 1; i < m; ++i)
        days += pgm_read_byte(days_in_month + i - 1);
    if (m > 2 && y % 4 == 0) ++days;
    return days + 365 * y + (y + 3) / 4 - 1;
}

/**
 * @brief generate the day of the week
 *
 * @param t time struct to use
 * @return uint8_t returns the day of the week
 */
static uint8_t day_of_the_week(ds3231_time_t *t) {
    uint16_t day = date_to_days(t->year - 2000U, t->month, t->date);
    return (day + 6) % 7; // Jan 1, 2000 is a Saturday, i.e. returns 6
}

/**
 * @brief Convert the date and time GCC strings into a ds3231_time_t struct
 *
 * @param date for __DATE__ macro
 * @param time for __TIME__ macro
 * @return ds3231_time_t
 */
ds3231_time_t convert_date_time(const char *date, const char *time) {
    ds3231_time_t t;
    uint16_t      year_offset;

    year_offset = atoi(date + 9);
    // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
    switch (date[0]) {
        case 'J':
            t.month = (date[1] == 'a') ? 1 : ((date[2] == 'n') ? 6 : 7);
            break;
        case 'F':
            t.month = 2;
            break;
        case 'A':
            t.month = date[2] == 'r' ? 4 : 8;
            break;
        case 'M':
            t.month = date[2] == 'r' ? 3 : 5;
            break;
        case 'S':
            t.month = 9;
            break;
        case 'O':
            t.month = 10;
            break;
        case 'N':
            t.month = 11;
            break;
        case 'D':
            t.month = 12;
            break;
        default:
            t.month = 0;
            break;
    }

    t.year     = year_offset + 2000U;
    t.week     = day_of_the_week(&t);
    t.date     = atoi(date + 4);
    t.hour     = atoi(time);
    t.minute   = atoi(time + 3);
    t.second   = atoi(time + 6);
    t.format   = DS3231_FORMAT_24H;
    t.am_pm    = (ds3231_am_pm_t)(t.hour >= 12);
    t.unixtime = convert_to_unixtime(t);

    return t;
}

/**
 * @brief Sets the time on the RTC
 *
 * @param t Time structure to set
 * @return i2c_status_t
 */
i2c_status_t ds3231_set_time(ds3231_time_t t) {
    uint8_t data[7] = {ds3231_bcd2hex(t.second), ds3231_bcd2hex(t.minute), ds3231_bcd2hex(t.hour), ds3231_bcd2hex(week_to_int(t.week)), ds3231_bcd2hex(t.date), ds3231_bcd2hex(t.month), ds3231_bcd2hex(t.year - 2000U)};

    if (ds3231_set_reg(DS3231_TIME_REG, data, 7) != I2C_STATUS_SUCCESS) {
        uprintf("Error while sending time to RTC!\n");
        return I2C_STATUS_ERROR;
    }

    uint8_t status[1] = {0};

    if (ds3231_get_byte_reg(DS3231_STATUS_REG, status) != I2C_STATUS_SUCCESS) {
        uprintf("Error while reading status!\n");
        return I2C_STATUS_ERROR;
    }

    status[0] &= ~0x80; // flip OSF bit

    return ds3231_set_byte_reg(DS3231_STATUS_REG, status[0]);
}

void ds3231_set_time_split(ds3231_time_t time, float temp, bool is_connected) {
    t             = time;
    rtc_temp      = temp;
    rtc_connected = is_connected;
}

/**
 * @brief Get the time object from the RTC
 *
 * @param t Time struct to fill
 * @return i2c_status_t
 */
i2c_status_t ds3231_get_time(ds3231_time_t *t) {
    uint8_t buf[7] = {0, 0, 0, 0, 0, 0, 0};

    i2c_status_t status = ds3231_get_reg(DS3231_TIME_REG, buf, 7);
    if (status != I2C_STATUS_SUCCESS) {
        return status;
    }

    t->year   = ds3231_bcd2hex(buf[6]) + 2000 + ((buf[5] >> 7) & 0x01) * 100; /* get year */
    t->month  = ds3231_bcd2hex(buf[5] & 0x1F);                                /* get month */
    t->week   = ds3231_bcd2hex(buf[3]);                                       /* get week */
    t->date   = ds3231_bcd2hex(buf[4]);                                       /* get date */
    t->am_pm  = (ds3231_am_pm_t)((buf[2] >> 5) & 0x01);                       /* get am pm */
    t->format = (ds3231_format_t)((buf[2] >> 6) & 0x01);                      /* get format */
    t->minute = ds3231_bcd2hex(buf[1]);                                       /* get minute */
    t->second = ds3231_bcd2hex(buf[0]);                                       /* get second */

    if (t->format == DS3231_FORMAT_12H) {        /* if 12H */
        t->hour = ds3231_bcd2hex(buf[2] & 0x1F); /* get hour */
    } else {
        t->hour = ds3231_bcd2hex(buf[2] & 0x3F); /* get hour */
    }

    t->unixtime = convert_to_unixtime(*t);

    return I2C_STATUS_SUCCESS;
}

/**
 * @brief Check the OSF bit to see if the RTC has lost power or crystal has lost sync
 *
 * @return true Has lost power and needs to be reset
 * @return false Is primed and ready to go
 */
bool ds3231_has_lost_power(void) {
    uint8_t status[1] = {0};
    ds3231_get_byte_reg(DS3231_STATUS_REG, status);
    return status[0] >> 7;
}

/**
 * @brief Get the temperature from the RTC
 *
 * @return float
 */
float ds3231_get_temperature(void) {
    uint8_t temp[2] = {0};

    ds3231_get_reg(DS3231_TEMPERATURE_REG, temp, 2);
    return (float)temp[0] + (float)(temp[1] >> 6) * 0.25;
}

/**
 * @brief Initialize the RTC and performs startup checks.
 *
 * @return true
 * @return false
 */
bool ds3231_init(void) {
    if (rtc_initialized) {
        return true;
    }
    i2c_status_t status = i2c_start(DS3231_I2C_ADDRESS << 1, DS3231_I2C_TIMEOUT);
    rtc_initialized     = (status == I2C_STATUS_SUCCESS);
    if (rtc_initialized) {
        last_rtc_read = timer_read() + DS3231_READ_INTERVAL;
        rtc_connected = true;

        i2c_stop();
    } else {
        dprintf("DS3231: failed to initialize\n");
    }

    if (ds3231_has_lost_power()) {
        // If there is an issue with the RTC config, then manually set the RTC time to the compile time
        // It's not exact, but it's better than nothing. Can be adjusted manually, later.
        ds3231_set_time(convert_date_time(__DATE__, __TIME__));
    }
    return rtc_initialized;
}

/**
 * @brief Runs the RTC task. Reads from the RTC every DS3231_READ_INTERVAL, and stores value locally
 *
 */
void ds3231_task(void) {
    if (!rtc_initialized) {
        return;
    }
    if (timer_expired(timer_read(), last_rtc_read)) {
        i2c_status_t status = ds3231_get_time(&t);

        rtc_connected = false;
        switch (status) {
            case I2C_STATUS_SUCCESS:
                last_rtc_read = timer_read() + DS3231_READ_INTERVAL;
                rtc_connected = true;
                break;
            case I2C_STATUS_ERROR:
                rtc_initialized = false;
                break;
            case I2C_STATUS_TIMEOUT:
                uprintf("Error while reading time from RTC!\n");
                last_rtc_read = timer_read() + (DS3231_READ_INTERVAL * DS3231_I2C_TIMEOUT);
                break;
        }
        rtc_temp = ds3231_get_temperature();
    }
}
