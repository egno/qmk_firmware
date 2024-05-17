/* Copyright 2021 weteor
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

#include QMK_KEYBOARD_H

#ifdef COMBO_ENABLE
#   include "combos.h"
#endif

// Tap Dance declarations
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

// Tap dance enums
enum {
    TD_R_SPC_NAV_TAB,
    TD_FN_SPC_NAV_TAB,
    TD_S2_SPC_NAV_TAB,
    TD_SYM_NUM_ENT
};

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

enum layers
{
    _A = 0,
    _A_R,
    _SYM,
    _SYM2,
    _SYM3,
    _NUM,
    _FKEYS,
    _NAV,
    _MOUSE,
    _CFG,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_A] = LAYOUT(
        KC_Q,               KC_W,       KC_F,    KC_P,    KC_B,
        KC_A,               KC_R,       KC_S,    KC_T,    KC_G,
        LSFT_T(KC_DOT),     KC_Z,       KC_X,    KC_C,    KC_D,
                        LT(_MOUSE, KC_BSPC), TD(TD_R_SPC_NAV_TAB), LT(_CFG, KC_ENT)
    ),
    [_A_R] = LAYOUT(
        KC_ESC,             KC_Y,       KC_U,    KC_L,    KC_J,
        KC_O,               KC_I,       KC_E,    KC_N,    KC_M,
        KC_SCLN,            KC_COMM,    KC_H,    KC_K,      KC_V,
                                XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_SYM] = LAYOUT(
        LSFT(KC_GRV),   LSFT(KC_7),    LSFT(KC_8), LSFT(KC_9),  LSFT(KC_EQL),
        XXXXXXX,        LSFT(KC_4),    LSFT(KC_5), LSFT(KC_6),  LSFT(KC_MINS),
        LSFT(KC_BSLS),  LSFT(KC_1),    LSFT(KC_2), LSFT(KC_2),  LSFT(KC_0),
                                        _______, TD(TD_S2_SPC_NAV_TAB), _______
    ),
    [_SYM2] = LAYOUT(
        KC_GRV,             XXXXXXX,    KC_LBRC,    KC_RBRC,    KC_EQL,
        LSFT(LALT(KC_2)),   KC_SCLN,    KC_QUOT,    KC_BSLS,    KC_MINS,
        LSFT_T(KC_DOT),     KC_COMM,    KC_DOT,     KC_SLSH,    XXXXXXX,
                                        _______, _______, _______
    ),
    [_SYM3] = LAYOUT(
        KC_ESC,     KC_MINS,    KC_MINS,    KC_PLUS,    KC_TILD,
        XXXXXXX,    KC_EXLM,    KC_LT,      KC_GT,      KC_EQL,
        XXXXXXX,    KC_UNDS,    KC_LBRC,    KC_RBRC,    KC_COLN,
                                        _______, _______, _______
    ),
    [_NUM] = LAYOUT(
        KC_MINS,  KC_7,  KC_8,  KC_9,  KC_DOT,
        KC_SLSH,  KC_4,  KC_5,  KC_6,  KC_0,
        XXXXXXX,  KC_1,  KC_2,  KC_3,  KC_COMM,
                                        _______, TD(TD_FN_SPC_NAV_TAB), _______
    ),
    [_FKEYS] = LAYOUT(
        KC_F15,  KC_F7,  KC_F8,  KC_F9,  KC_F12,
        KC_F14,  KC_F4,  KC_F5,  KC_F6,  KC_F11,
        KC_F13,  KC_F1,  KC_F2,  KC_F3,  KC_F10,
                                        _______, _______, _______
    ),
    [_NAV] = LAYOUT(
        XXXXXXX, KC_PGDN, KC_UP,    KC_PGUP, KC_DEL,
        KC_HOME, KC_LEFT, KC_DOWN,  KC_RGHT, KC_END,
        XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,
                                        _______, _______, _______
    ),
    [_MOUSE] = LAYOUT(
        KC_BTN1,  XXXXXXX,  KC_MS_U,  XXXXXXX,  KC_WH_U,
        KC_BTN3,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_WH_D,
        KC_BTN2,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                        _______, _______, _______
    ),
    [_CFG] = LAYOUT(
        DF(_A),         OSL(_SYM3),     XXXXXXX,        XXXXXXX,        XXXXXXX,
        XXXXXXX,        OSL(_SYM),      OSL(_NUM),      TO(_A),         XXXXXXX,
        OSM(MOD_LSFT),  OSM(MOD_LCTL),  OSM(MOD_LALT),  OSM(MOD_LGUI),  XXXXXXX,
                                 TO(_A), XXXXXXX, _______
    ),
};




td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (state->pressed) return TD_DOUBLE_HOLD;
        else return TD_DOUBLE_TAP;
    }

    // Assumes no one is trying to type the same letter three times (at least not quickly).
    // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    if (state->count == 3) {
        if (!state->pressed) return TD_TRIPLE_TAP;
        else return TD_TRIPLE_HOLD;
    } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};


// R
void r_spc_tab_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_SPC); break;
        case TD_SINGLE_HOLD: layer_on(_A_R); break;
        case TD_DOUBLE_TAP: register_code(KC_TAB); break;
        case TD_DOUBLE_HOLD: layer_on(_NAV); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_SPC); register_code(KC_SPC); break;
        default: break;
    }
}

void r_spc_tab_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SPC); break;
        case TD_SINGLE_HOLD: layer_off(_A_R); break;
        case TD_DOUBLE_TAP: unregister_code(KC_TAB); break;
        case TD_DOUBLE_HOLD: layer_off(_NAV); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_SPC); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

// FKEYS
void fn_spc_tab_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_SPC); break;
        case TD_SINGLE_HOLD: layer_on(_FKEYS); break;
        case TD_DOUBLE_TAP: register_code(KC_TAB); break;
        case TD_DOUBLE_HOLD: layer_on(_NAV); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_SPC); register_code(KC_SPC); break;
        default: break;
    }
}

void fn_spc_tab_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SPC); break;
        case TD_SINGLE_HOLD: layer_off(_FKEYS); break;
        case TD_DOUBLE_TAP: unregister_code(KC_TAB); break;
        case TD_DOUBLE_HOLD: layer_off(_NAV); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_SPC); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

// SYM2
void s2_spc_tab_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_SPC); break;
        case TD_SINGLE_HOLD: layer_on(_SYM2); break;
        case TD_DOUBLE_TAP: register_code(KC_TAB); break;
        case TD_DOUBLE_HOLD: layer_on(_NAV); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_SPC); register_code(KC_SPC); break;
        default: break;
    }
}

void s2_spc_tab_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SPC); break;
        case TD_SINGLE_HOLD: layer_off(_SYM2); break;
        case TD_DOUBLE_TAP: unregister_code(KC_TAB); break;
        case TD_DOUBLE_HOLD: layer_off(_NAV); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_SPC); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_R_SPC_NAV_TAB]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, r_spc_tab_finished, r_spc_tab_reset),
    [TD_FN_SPC_NAV_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fn_spc_tab_finished, fn_spc_tab_reset),
    [TD_S2_SPC_NAV_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, s2_spc_tab_finished, s2_spc_tab_reset),
};


layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef CONSOLE_ENABLE
    uprintf("LAYER: %016b\n", state);
#endif
return state;
}
