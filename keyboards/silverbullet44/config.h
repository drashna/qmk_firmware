/*
Copyright 2019 SwanMatch

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

#ifdef RGBLIGHT_ENABLE
/*== customize breathing effect ==*/
  /*==== (DEFAULT) use fixed table instead of exp() and sin() ====*/
    #define RGBLIGHT_BREATHE_TABLE_SIZE 256      // 256(default) or 128 or 64
  /*==== use exp() and sin() ====*/
    #define RGBLIGHT_EFFECT_BREATHE_CENTER 2     // 1 to 2.7
    #define RGBLIGHT_EFFECT_BREATHE_MAX    255   // 0 to 255
/*== customize snake effect ==*/
    #define RGBLIGHT_EFFECT_SNAKE_LENGTH RGBLIGHT_LED_COUNT
/*== customize knight effect ==*/
    #define RGBLIGHT_EFFECT_KNIGHT_LENGTH 6
#endif

/* Audio */
#ifdef AUDIO_ENABLE
  #define AUDIO_PIN B6
  #define STARTUP_SONG SONG(STARTUP_SOUND)
  #define AUDIO_CLICKY
  #define AUDIO_CLICKY_FREQ_RANDOMNESS 1.0f
#endif

//#define RETRO_TAPPING

#ifdef MOUSEKEY_ENABLE
  #define MOUSEKEY_INTERVAL 20
  #define MOUSEKEY_MAX_SPEED 5
  #define MOUSEKEY_TIME_TO_MAX 60
#endif

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
