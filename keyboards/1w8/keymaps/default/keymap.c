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
    TD_R_SPC_TAB_NAV,
    TD_SYM_NUM_ENT
};

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

enum layers
{
    _ALPHA_COLEMAK = 0,
    _ALPHA_COLEMAK_R,
    _GAME,
    _SYM,
    _SYM2,
    _SYM3,
    _NAV,
    _NUM,
    _FKEYS,
    _MOUSE,
    _CFG,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_ALPHA_COLEMAK] = LAYOUT(
        KC_Q,         KC_W,    KC_F,    KC_P,    KC_B,
        KC_A,          KC_R,    KC_S,    KC_T,    KC_G,
        LSFT_T(KC_DOT),  KC_Z, KC_X,    KC_C,    KC_D,

                        LT(_MOUSE, KC_BSPC), TD(TD_R_SPC_TAB_NAV), LT(_CFG, KC_ENT)
    ),
    [_ALPHA_COLEMAK_R] = LAYOUT(
        KC_ESC,      KC_Y,    KC_U,    KC_L,    KC_J,
        KC_O,         KC_I,    KC_E,    KC_N,    KC_M,
        KC_SCLN,  KC_COMM, KC_H,    KC_K,  KC_V,
                                XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_GAME] = LAYOUT(
        KC_TAB,   KC_Q,         KC_W,    KC_E,    KC_R,
        KC_LALT,   KC_A,         KC_S,    KC_D,    KC_F,
        KC_LSFT,   KC_Z,         KC_X,    KC_C,    KC_V,
                                    MO(_CFG), KC_SPC, KC_ENT
    ),
    [_SYM] = LAYOUT(
        KC_GRV,  KC_MINS, KC_LCBR, KC_RCBR,  KC_SCLN,
        KC_DQT,  KC_UNDS,  KC_LPRN, KC_RPRN,  KC_EQL,
        LT(_FKEYS, LSFT(KC_BSLS)), KC_EXLM, KC_LBRC, KC_RBRC,  KC_COLON,
                                        TO(_ALPHA_COLEMAK), _______, _______
    ),
    [_SYM2] = LAYOUT(
        KC_QUOT,  KC_COLN, KC_MINS, KC_PLUS,  KC_TILD,
        XXXXXXX,  KC_EXLM,  KC_LT, KC_GT,  KC_EQL,
        XXXXXXX, KC_UNDS, KC_LBRC, KC_RBRC,  KC_COLN,
                                        TO(_ALPHA_COLEMAK), _______, _______
    ),
    [_SYM3] = LAYOUT(
        KC_ESC,  KC_MINS, KC_MINS, KC_PLUS,  KC_TILD,
        XXXXXXX,  KC_EXLM,  KC_LT, KC_GT,  KC_EQL,
        XXXXXXX, KC_UNDS, KC_LBRC, KC_RBRC,  KC_COLN,
                                        TO(_ALPHA_COLEMAK), _______, _______
    ),
    [_NAV] = LAYOUT(
        XXXXXXX, KC_PGDN, KC_UP, KC_PGUP, KC_DEL,
        KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                        TO(_ALPHA_COLEMAK), _______, LT(_CFG, KC_ENT)
    ),
    [_NUM] = LAYOUT(
        XXXXXXX,  KC_7,  KC_8,  KC_9,  KC_DOT,
        XXXXXXX,     KC_4,  KC_5,  KC_6,  KC_0,
        XXXXXXX,  KC_1,  KC_2,  KC_3,  KC_COMM,
                                        TO(_ALPHA_COLEMAK), _______, LT(_CFG, KC_ENT)
    ),
    [_FKEYS] = LAYOUT(
        XXXXXXX,  KC_F7,  KC_F8,  KC_F9,  KC_F12,
        XXXXXXX,  KC_F4,  KC_F5,  KC_F6,  KC_F11,
        XXXXXXX,  KC_F1,  KC_F2,  KC_F3,  KC_F10,
                                        TO(_ALPHA_COLEMAK), _______, _______
    ),
    [_MOUSE] = LAYOUT(
        KC_BTN1,  XXXXXXX,  KC_MS_U,  XXXXXXX,  KC_WH_U,
        KC_BTN3,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_WH_D,
        KC_BTN2,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                        TO(_ALPHA_COLEMAK), _______, _______
    ),
    [_CFG] = LAYOUT(
        DF(_ALPHA_COLEMAK), DF(_SYM3), DF(_FKEYS), XXXXXXX, DF(_GAME),
        XXXXXXX, DF(_SYM), TO(_NAV), TO(_NUM), XXXXXXX,
        XXXXXXX, DF(_SYM2), XXXXXXX, XXXXXXX, XXXXXXX,
                                 TO(_ALPHA_COLEMAK), XXXXXXX, LT(_CFG, KC_ENT)
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

void r_spc_tab_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_SPC); break;
        case TD_SINGLE_HOLD: layer_on(_ALPHA_COLEMAK_R); break;
        case TD_DOUBLE_TAP: register_code(KC_TAB); break;
        case TD_DOUBLE_HOLD: layer_on(_NAV); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_SPC); register_code(KC_SPC); break;
        default: break;
    }
}

void r_spc_tab_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_SPC); break;
        case TD_SINGLE_HOLD: layer_off(_ALPHA_COLEMAK_R); break;
        case TD_DOUBLE_TAP: unregister_code(KC_TAB); break;
        case TD_DOUBLE_HOLD: layer_off(_NAV); break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_SPC); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_R_SPC_TAB_NAV] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, r_spc_tab_finished, r_spc_tab_reset),
};


layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef CONSOLE_ENABLE
    uprintf("LAYER: %2u\n", state);
#endif
return state;
}
