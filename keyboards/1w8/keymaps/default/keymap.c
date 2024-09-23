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

#include "layers.h"

#ifdef COMBO_ENABLE
#   include "combos.h"
#endif




// Tap dance enums
enum {
    TD_R_SPC_NAV_TAB,
    TD_FN_SPC_NAV_TAB,
    TD_S2_SPC_NAV_TAB,
    TD_SYM_NUM_ENT,
    TD_CFG_ENT,
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_A] = LAYOUT(
        KC_Q,               KC_W,       KC_F,    KC_P,    KC_B,
        KC_A,               KC_R,       KC_S,    KC_T,    KC_G,
        LSFT_T(KC_DOT),     KC_Z,       KC_X,    KC_C,    KC_D,
                        LT(_MOUSE, KC_BSPC), TD(TD_R_SPC_NAV_TAB), TD(TD_CFG_ENT)
    ),
    [_A_R] = LAYOUT(
        KC_ESC,             KC_Y,       KC_U,    KC_L,    KC_J,
        KC_O,               KC_I,       KC_E,    KC_N,    KC_M,
        KC_COMM,            KC_SCLN,    KC_H,    KC_K,    KC_V,
                                XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_SYM] = LAYOUT(
        LSFT(KC_GRV),   LSFT(KC_7),    LSFT(KC_8), LSFT(KC_9),  LSFT(KC_EQL),
        LSFT(KC_0),     LSFT(KC_4),    LSFT(KC_5), LSFT(KC_6),  LSFT(KC_MINS),
        LSFT(KC_BSLS),  LSFT(KC_1),    LSFT(KC_2), LSFT(KC_3),  LSFT(KC_SLSH),
                                        _______, _______, _______
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
        KC_COMM,  KC_7,  KC_8,  KC_9,  KC_EQL,
        KC_0,     KC_4,  KC_5,  KC_6,  KC_MINS,
        _______,  KC_1,  KC_2,  KC_3,  KC_SLSH,
                                        _______, _______, _______
    ),
    [_FKEYS] = LAYOUT(
        KC_F14,  KC_F7,  KC_F8,  KC_F9,  KC_F11,
        KC_F10,  KC_F4,  KC_F5,  KC_F6,  KC_F12,
        KC_F15,  KC_F1,  KC_F2,  KC_F3,  KC_F13,
                                        _______, _______, _______
    ),
    [_MM] = LAYOUT(
        KC_LAUNCHPAD,       KC_MEDIA_NEXT_TRACK,  KC_KB_VOLUME_UP,    KC_BRIGHTNESS_UP,   KC_SYSTEM_WAKE,
        KC_MISSION_CONTROL, KC_MEDIA_PREV_TRACK,  KC_KB_VOLUME_DOWN,  KC_BRIGHTNESS_DOWN, KC_SYSTEM_SLEEP,
        XXXXXXX,            KC_MEDIA_PLAY_PAUSE,  KC_KB_MUTE,         XXXXXXX,            KC_KB_POWER,
                                        _______, _______, _______
    ),
    [_NAV] = LAYOUT(
        G(KC_Z),    KC_HOME,    KC_UP,      KC_END,         KC_PGUP ,
        KC_DEL,     KC_LEFT,    KC_DOWN,    KC_RGHT,        KC_PGDN,
        G(KC_X),    A(KC_LEFT), G(KC_V),    A(KC_RIGHT),    G(KC_C),
                                        _______, _______, _______
    ),
    [_MOUSE] = LAYOUT(
        KC_BTN3,  KC_WH_L,  KC_MS_U,  KC_WH_R,  KC_WH_U,
        KC_BTN1,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_WH_D,
        KC_BTN2,  KC_BTN4,  KC_BTN5,  KC_BTN6,  KC_BTN7,
                                        _______, _______, _______
    ),
    [_CFG] = LAYOUT(
        AS_TOGG,        TO(_SYM3),      TO(_FKEYS),     TO(_SYM3),      KC_F17,
        TO(_MM),        TO(_SYM),       TO(_NUM),       TO(_A),         KC_F18,
        OSM(MOD_LSFT),  OSM(MOD_LCTL),  OSM(MOD_LALT),  OSM(MOD_LGUI),  KC_F19,
                                 XXXXXXX, XXXXXXX, _______
    ),
};


layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef CONSOLE_ENABLE
    uprintf("LAYER ______GMNFD32SRA\n");
    uprintf("      %016b\n", state);
#endif
return state;
};






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


// Create an instance of 'td_tap_t' for the 'x' tap dance.
static td_tap_t xtap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
    ) {
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

// CFG
void cfg_ent_finished(tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: register_code(KC_ENT); break;
        case TD_SINGLE_HOLD: reset_oneshot_layer(); layer_clear(); layer_on(_CFG); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: clear_oneshot_mods(); reset_oneshot_layer(); layer_clear(); layer_on(_CFG); break;
        case TD_DOUBLE_SINGLE_TAP: tap_code(KC_ENT); register_code(KC_ENT); break;
        default: break;
    }
}

void cfg_ent_reset(tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case TD_SINGLE_TAP: unregister_code(KC_ENT); break;
        case TD_SINGLE_HOLD: reset_oneshot_layer(); layer_clear(); break;
        case TD_DOUBLE_TAP: break;
        case TD_DOUBLE_HOLD: break;
        case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_ENT); break;
        default: break;
    }
    xtap_state.state = TD_NONE;
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_R_SPC_NAV_TAB]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, r_spc_tab_finished, r_spc_tab_reset),
    [TD_FN_SPC_NAV_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fn_spc_tab_finished, fn_spc_tab_reset),
    [TD_S2_SPC_NAV_TAB] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, s2_spc_tab_finished, s2_spc_tab_reset),
    [TD_CFG_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cfg_ent_finished, cfg_ent_reset),
};
