/* Copyright 2016 Jack Humbert
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

#ifdef TAP_DANCE_ENABLE

#    include <stdbool.h>
#    include <inttypes.h>

typedef struct {
    uint16_t interrupting_keycode;
    uint8_t  count;
    uint8_t  weak_mods;
#    ifndef NO_ACTION_ONESHOT
    uint8_t oneshot_mods;
#    endif
    bool pressed : 1;
    bool finished : 1;
    bool interrupted : 1;
} qk_tap_dance_state_t;

typedef void (*qk_tap_dance_user_fn_t)(qk_tap_dance_state_t *state, void *user_data);

typedef struct {
    qk_tap_dance_state_t state;
    struct {
        qk_tap_dance_user_fn_t on_each_tap;
        qk_tap_dance_user_fn_t on_dance_finished;
        qk_tap_dance_user_fn_t on_reset;
    } fn;
    void *user_data;
} qk_tap_dance_action_t;

typedef struct {
    uint16_t kc1;
    uint16_t kc2;
} qk_tap_dance_pair_t;

typedef struct {
    uint16_t kc;
    uint8_t  layer;
    void (*layer_function)(uint8_t);
} qk_tap_dance_dual_role_t;

typedef enum {
    TD_Q_NONE,
    TD_Q_UNKNOWN,
    TD_Q_SINGLE_TAP,
    TD_Q_SINGLE_HOLD,
    TD_Q_DOUBLE_TAP,
    TD_Q_DOUBLE_HOLD,
    TD_Q_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_Q_TRIPLE_TAP,
    TD_Q_TRIPLE_HOLD
} quad_td_state_t;

typedef struct {
    bool is_press_action;
    quad_td_state_t state;
} quad_td_tap_t;

typedef struct {
    uint16_t kc1;
    uint16_t kc2;
    uint16_t kc3;
    uint16_t kc4;
    quad_td_tap_t tap;
} qk_tap_dance_quatrain_t;


#    define ACTION_TAP_DANCE_DOUBLE(kc1, kc2) \
        { .fn = {qk_tap_dance_pair_on_each_tap, qk_tap_dance_pair_finished, qk_tap_dance_pair_reset}, .user_data = (void *)&((qk_tap_dance_pair_t){kc1, kc2}), }

#    define ACTION_TAP_DANCE_QUAD(kc1, kc2, kc3, kc4) \
        { .fn = {qk_tap_dance_quatrain_on_each_tap, qk_tap_dance_quatrain_finished, qk_tap_dance_quatrain_reset}, .user_data = (void *)&((qk_tap_dance_quatrain_t){kc1, kc2, kc3, kc4, {true, TD_Q_NONE}}), }

#    define ACTION_TAP_DANCE_LAYER_MOVE(kc, layer) \
        { .fn = {qk_tap_dance_dual_role_on_each_tap, qk_tap_dance_dual_role_finished, qk_tap_dance_dual_role_reset}, .user_data = (void *)&((qk_tap_dance_dual_role_t){kc, layer, layer_move}), }

#    define ACTION_TAP_DANCE_LAYER_TOGGLE(kc, layer) \
        { .fn = {NULL, qk_tap_dance_dual_role_finished, qk_tap_dance_dual_role_reset}, .user_data = (void *)&((qk_tap_dance_dual_role_t){kc, layer, layer_invert}), }

#    define ACTION_TAP_DANCE_FN(user_fn) \
        { .fn = {NULL, user_fn, NULL}, .user_data = NULL, }

#    define ACTION_TAP_DANCE_FN_ADVANCED(user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset) \
        { .fn = {user_fn_on_each_tap, user_fn_on_dance_finished, user_fn_on_dance_reset}, .user_data = NULL, }

#    define TD(n) (QK_TAP_DANCE | TD_INDEX(n))
#    define TD_INDEX(code) ((code)&0xFF)
#    define TAP_DANCE_KEYCODE(state) TD(((qk_tap_dance_action_t *)state) - tap_dance_actions)

extern qk_tap_dance_action_t tap_dance_actions[];

void reset_tap_dance(qk_tap_dance_state_t *state);

/* To be used internally */

bool preprocess_tap_dance(uint16_t keycode, keyrecord_t *record);
bool process_tap_dance(uint16_t keycode, keyrecord_t *record);
void tap_dance_task(void);

void qk_tap_dance_pair_on_each_tap(qk_tap_dance_state_t *state, void *user_data);
void qk_tap_dance_pair_finished(qk_tap_dance_state_t *state, void *user_data);
void qk_tap_dance_pair_reset(qk_tap_dance_state_t *state, void *user_data);

void qk_tap_dance_dual_role_on_each_tap(qk_tap_dance_state_t *state, void *user_data);
void qk_tap_dance_dual_role_finished(qk_tap_dance_state_t *state, void *user_data);
void qk_tap_dance_dual_role_reset(qk_tap_dance_state_t *state, void *user_data);

void qk_tap_dance_quatrain_on_each_tap(qk_tap_dance_state_t *state, void *user_data);
void qk_tap_dance_quatrain_finished(qk_tap_dance_state_t *state, void *user_data);
void qk_tap_dance_quatrain_reset(qk_tap_dance_state_t *state, void *user_data);

#else

#    define TD(n) KC_NO

#endif
