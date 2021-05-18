/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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
#include "pro.h"

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {

    {0, CS1_SW1,   CS2_SW1,  CS3_SW1  },
    {0, CS1_SW2,   CS2_SW2,  CS3_SW2  },
    {0, CS1_SW3,   CS2_SW3,  CS3_SW3  },
    {0, CS1_SW4,   CS2_SW4,  CS3_SW4  },
    {0, CS1_SW5,   CS2_SW5,  CS3_SW5  },
    {0, CS1_SW6,   CS2_SW6,  CS3_SW6  },
    {0, CS1_SW7,   CS2_SW7,  CS3_SW7  },
    {0, CS1_SW8,   CS2_SW8,  CS3_SW8  },
    {0, CS1_SW9,   CS2_SW9,  CS3_SW9  },
    {0, CS1_SW10,  CS2_SW10, CS3_SW10 },
    {0, CS1_SW11,  CS2_SW11, CS3_SW11 },
    {0, CS1_SW12,  CS2_SW12, CS3_SW12 },

    {0, CS4_SW1,   CS5_SW1,  CS6_SW1  },
    {0, CS4_SW2,   CS5_SW2,  CS6_SW2  },
    {0, CS4_SW3,   CS5_SW3,  CS6_SW3  },
    {0, CS4_SW4,   CS5_SW4,  CS6_SW4  },
    {0, CS4_SW5,   CS5_SW5,  CS6_SW5  },
    {0, CS4_SW6,   CS5_SW6,  CS6_SW6  },
    {0, CS4_SW7,   CS5_SW7,  CS6_SW7  },
    {0, CS4_SW8,   CS5_SW8,  CS6_SW8  },
    {0, CS4_SW9,   CS5_SW9,  CS6_SW9  },
    {0, CS4_SW10,  CS5_SW10, CS6_SW10 },
    {0, CS4_SW11,  CS5_SW11, CS6_SW11 },
    {0, CS4_SW12,  CS5_SW12, CS6_SW12 },

    {0, CS7_SW1,   CS8_SW1,  CS9_SW1  },
    {0, CS7_SW2,   CS8_SW2,  CS9_SW2  },
    {0, CS7_SW3,   CS8_SW3,  CS9_SW3  },
    {0, CS7_SW4,   CS8_SW4,  CS9_SW4  },
    {0, CS7_SW5,   CS8_SW5,  CS9_SW5  },
    {0, CS7_SW6,   CS8_SW6,  CS9_SW6  },
    {0, CS7_SW7,   CS8_SW7,  CS9_SW7  },
    {0, CS7_SW8,   CS8_SW8,  CS9_SW8  },
    {0, CS7_SW9,   CS8_SW9,  CS9_SW9  },
    {0, CS7_SW10,  CS8_SW10, CS9_SW10 },
    {0, CS7_SW11,  CS8_SW11, CS9_SW11 },
    {0, CS7_SW12,  CS8_SW12, CS9_SW12 },

    {0, CS10_SW1,   CS11_SW1,  CS12_SW1  },
    {0, CS10_SW2,   CS11_SW2,  CS12_SW2  },
    {0, CS10_SW3,   CS11_SW3,  CS12_SW3  },
    {0, CS10_SW4,   CS11_SW4,  CS12_SW4  },
    {0, CS10_SW5,   CS11_SW5,  CS12_SW5  },
    {0, CS10_SW6,   CS11_SW6,  CS12_SW6  },
    {0, CS10_SW7,   CS11_SW7,  CS12_SW7  },
    {0, CS10_SW8,   CS11_SW8,  CS12_SW8  },
    {0, CS10_SW9,   CS11_SW9,  CS12_SW9  },
    {0, CS10_SW10,  CS11_SW10, CS12_SW10 },
    {0, CS10_SW11,  CS11_SW11, CS12_SW11 },
    {0, CS10_SW12,  CS11_SW12, CS12_SW12 },

    {0, CS13_SW1,   CS14_SW1,  CS15_SW1  },
    {0, CS13_SW2,   CS14_SW2,  CS15_SW2  },
    {0, CS13_SW3,   CS14_SW3,  CS15_SW3  },
    {0, CS13_SW4,   CS14_SW4,  CS15_SW4  },
    {0, CS13_SW5,   CS14_SW5,  CS15_SW5  },
    {0, CS13_SW6,   CS14_SW6,  CS15_SW6  },
    {0, CS13_SW7,   CS14_SW7,  CS15_SW7  },
    {0, CS13_SW8,   CS14_SW8,  CS15_SW8  },
    {0, CS13_SW9,   CS14_SW9,  CS15_SW9  },
    {0, CS13_SW10,  CS14_SW10, CS15_SW10 },
    {0, CS13_SW11,  CS14_SW11, CS15_SW11 },
    {0, CS13_SW12,  CS14_SW12, CS15_SW12 },

    {0, CS16_SW1,   CS17_SW1,  CS18_SW1  },
    {0, CS16_SW2,   CS17_SW2,  CS18_SW2  },
    {0, CS16_SW3,   CS17_SW3,  CS18_SW3  },
    {0, CS16_SW4,   CS17_SW4,  CS18_SW4  },
    {0, CS16_SW5,   CS17_SW5,  CS18_SW5  },
    {0, CS16_SW6,   CS17_SW6,  CS18_SW6  },
    {0, CS16_SW7,   CS17_SW7,  CS18_SW7  },
    {0, CS16_SW8,   CS17_SW8,  CS18_SW8  },
    {0, CS16_SW9,   CS17_SW9,  CS18_SW9  },
    {0, CS16_SW10,  CS17_SW10, CS18_SW10 },
    {0, CS16_SW11,  CS17_SW11, CS18_SW11 },
    {0, CS16_SW12,  CS17_SW12, CS18_SW12 },

    {1, CS1_SW1,   CS2_SW1,  CS3_SW1  },
    {1, CS1_SW2,   CS2_SW2,  CS3_SW2  },
    {1, CS1_SW3,   CS2_SW3,  CS3_SW3  },
    {1, CS1_SW4,   CS2_SW4,  CS3_SW4  },
    {1, CS1_SW5,   CS2_SW5,  CS3_SW5  },
    {1, CS1_SW6,   CS2_SW6,  CS3_SW6  },
    {1, CS1_SW7,   CS2_SW7,  CS3_SW7  },
    {1, CS1_SW8,   CS2_SW8,  CS3_SW8  },
    {1, CS1_SW9,   CS2_SW9,  CS3_SW9  },
    {1, CS1_SW10,  CS2_SW10, CS3_SW10 },
    {1, CS1_SW11,  CS2_SW11, CS3_SW11 },
    // {1, CS1_SW12,  CS2_SW12, CS3_SW12 },

    {1, CS4_SW1,   CS5_SW1,  CS6_SW1  },
    {1, CS4_SW2,   CS5_SW2,  CS6_SW2  },
    {1, CS4_SW3,   CS5_SW3,  CS6_SW3  },
    {1, CS4_SW4,   CS5_SW4,  CS6_SW4  },
    {1, CS4_SW5,   CS5_SW5,  CS6_SW5  },
    {1, CS4_SW6,   CS5_SW6,  CS6_SW6  },
    {1, CS4_SW7,   CS5_SW7,  CS6_SW7  },
    {1, CS4_SW8,   CS5_SW8,  CS6_SW8  },
    {1, CS4_SW9,   CS5_SW9,  CS6_SW9  },
    {1, CS4_SW10,  CS5_SW10, CS6_SW10 },
    {1, CS4_SW11,  CS5_SW11, CS6_SW11 },
    // {1, CS4_SW12,  CS5_SW12, CS6_SW12 },

    {1, CS7_SW1,   CS8_SW1,  CS9_SW1  },
    {1, CS7_SW2,   CS8_SW2,  CS9_SW2  },
    {1, CS7_SW3,   CS8_SW3,  CS9_SW3  },
    {1, CS7_SW4,   CS8_SW4,  CS9_SW4  },
    {1, CS7_SW5,   CS8_SW5,  CS9_SW5  },
    {1, CS7_SW6,   CS8_SW6,  CS9_SW6  },
    {1, CS7_SW7,   CS8_SW7,  CS9_SW7  },
    {1, CS7_SW8,   CS8_SW8,  CS9_SW8  },
    {1, CS7_SW9,   CS8_SW9,  CS9_SW9  },
    {1, CS7_SW10,  CS8_SW10, CS9_SW10 },
    {1, CS7_SW11,  CS8_SW11, CS9_SW11 },
    // {1, CS7_SW12,  CS8_SW12, CS9_SW12 },

    {1, CS10_SW1,   CS11_SW1,  CS12_SW1  },
    {1, CS10_SW2,   CS11_SW2,  CS12_SW2  },
    {1, CS10_SW3,   CS11_SW3,  CS12_SW3  },
    {1, CS10_SW4,   CS11_SW4,  CS12_SW4  },
    {1, CS10_SW5,   CS11_SW5,  CS12_SW5  },
    {1, CS10_SW6,   CS11_SW6,  CS12_SW6  },
    {1, CS10_SW7,   CS11_SW7,  CS12_SW7  },
    // {1, CS10_SW8,   CS11_SW8,  CS12_SW8  },
    // {1, CS10_SW9,   CS11_SW9,  CS12_SW9  },
    // {1, CS10_SW10,  CS11_SW10, CS12_SW10 },
    // {1, CS10_SW11,  CS11_SW11, CS12_SW11 },
    // {1, CS10_SW12,  CS11_SW12, CS12_SW12 },

    {1, CS13_SW1,   CS14_SW1,  CS15_SW1  },
    {1, CS13_SW2,   CS14_SW2,  CS15_SW2  },
    {1, CS13_SW3,   CS14_SW3,  CS15_SW3  },
    {1, CS13_SW4,   CS14_SW4,  CS15_SW4  },
    {1, CS13_SW5,   CS14_SW5,  CS15_SW5  },
    {1, CS13_SW6,   CS14_SW6,  CS15_SW6  },
    {1, CS13_SW7,   CS14_SW7,  CS15_SW7  },
    {1, CS13_SW8,   CS14_SW8,  CS15_SW8  },
    {1, CS13_SW9,   CS14_SW9,  CS15_SW9  },
    {1, CS13_SW10,  CS14_SW10, CS15_SW10 },
    // {1, CS13_SW11,  CS14_SW11, CS15_SW11 },
    // {1, CS13_SW12,  CS14_SW12, CS15_SW12 },

    {1, CS16_SW1,   CS17_SW1,  CS18_SW1  },
    {1, CS16_SW2,   CS17_SW2,  CS18_SW2  },
    {1, CS16_SW3,   CS17_SW3,  CS18_SW3  },
    {1, CS16_SW4,   CS17_SW4,  CS18_SW4  },
    {1, CS16_SW5,   CS17_SW5,  CS18_SW5  },
    {1, CS16_SW6,   CS17_SW6,  CS18_SW6  },
    {1, CS16_SW7,   CS17_SW7,  CS18_SW7  },
    {1, CS16_SW8,   CS17_SW8,  CS18_SW8  },
    {1, CS16_SW9,   CS17_SW9,  CS18_SW9  },
    {1, CS16_SW10,  CS17_SW10, CS18_SW10 }
    // {1, CS16_SW11,  CS17_SW11, CS18_SW11 },
    // {1, CS16_SW12,  CS17_SW12, CS18_SW12 }
};

led_config_t g_led_config = { {
    { k00, k01, NO_LED, k03, k04, k05, k06, k07}, \
    { k10, k11, k12, k13, k14, k15, k16, k17}, \
    { k20, k21, k22, NO_LED, k24, k25, k26, k27}, \
    { k30, k31, k32, k33, k34, k35, k36, k37}, \
    { k40, k41, k42, k43, k44, k45, k46, k47}, \
    { k50, k51, k52, k53, k54, k55, k56, k57}, \
    { k60, k61, k62, k63, k64, k65, k66, k67}, \
    { k70, k71, k72, k73, k74, k75, k76, k77}, \
    { k80, k81, k82, k83, NO_LED, k85, k86, k87}, \
    { k90, k91, k92, k93, k94, k95, NO_LED, k97}, \
    { NO_LED, ka1, ka2, ka3, ka4, ka5, ka6, ka7}  \

}, {
    {   0,   0 }, {   0,  12 }, {   0,  25 }, {   0,  38 }, {   0,  51 },
    {  17,   0 }, {  17,  12 }, {  17,  25 }, {  17,  38 }, {  17,  51 },
    {  34,   0 }, {  34,  12 }, {  34,  25 }, {  34,  38 }, {  34,  51 },
    {  51,   0 }, {  51,  12 }, {  51,  25 }, {  51,  38 }, {  51,  51 },
    {  68,   0 }, {  68,  12 }, {  68,  25 }, {  68,  38 }, {  68,  51 },
    {  86,   0 }, {  86,  12 }, {  86,  25 }, {  86,  38 },
    { 105,   0 }, { 105,  12 }, { 105,  25 },
    {  90,  55 }, { 105,  68 }, { 116,  86 }, { 116, 59 },

    { 250,   0 }, { 250,  12 }, { 250,  25 }, { 250,  38 }, { 250,  51 },
    { 233,   0 }, { 233,  12 }, { 233,  25 }, { 233,  38 }, { 233,  51 },
    { 216,   0 }, { 216,  12 }, { 216,  25 }, { 216,  38 }, { 216,  51 },
    { 198,   0 }, { 198,  12 }, { 198,  25 }, { 198,  38 }, { 198,  51 },
    { 181,   0 }, { 181,  12 }, { 181,  25 }, { 181,  38 }, { 181,  51 },
    { 163,   0 }, { 163,  12 }, { 163,  25 }, { 163,  38 },
    { 146,   0 }, { 146,  12 }, { 146,  25 },
    { 161,  55 }, { 161,  68 }, { 146,  86 }, { 131, 59 }

}, {
    1, 1, 1, 1, 1, 4,
    4, 4, 4, 1, 4, 4,
    4, 4, 1, 4, 4, 4,
    4, 1, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 4,
    4, 4, 4, 1, 4, 4,
    4, 4, 1, 4, 4, 4,
    4, 1, 4, 4, 4, 4,
    1, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1, 1
} };
