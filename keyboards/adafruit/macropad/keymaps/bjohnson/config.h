// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define OLED_DISABLE_TIMEOUT
#define OLED_TIMEOUT 0
#define OLED_UPDATE_INTERVAL 15

#ifdef OLED_FONT_H
#    undef OLED_FONT_H
#endif
#define OLED_FONT_H "my_oled_font.h"
#define OLED_FONT_END 255
// #    define OLED_FONT_5X5
// #    define OLED_FONT_AZTECH
// #    define OLED_FONT_BMPLAIN
// #    define OLED_FONT_CRACKERS
#define OLED_FONT_DEAD_MEAL
// #    define OLED_FONT_EIN
// #    define OLED_FONT_HISKYF21
// #    define OLED_FONT_SQUASH
// #    define OLED_FONT_ZXPIX
// #    define OLED_FONT_SUPER_DIGG

// #    define OLED_LOGO_BEBOP
// #    define OLED_LOGO_CORNE
// #    define OLED_LOGO_GMK_BAD
// #    define OLED_LOGO_GOTHAM
// #    define OLED_LOGO_HUE_MANITEE
// #    define OLED_LOGO_LOOSE
#define OLED_LOGO_SCIFI
// #    define OLED_LOGO_SETS3N
// #    define OLED_LOGO_SKEEB


#    define STARTUP_SONG SONG(RICK_ROLL)
#    define GOODBYE_SONG SONG(SONIC_RING)
