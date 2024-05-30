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
#include "tap_dance.h"
#include "layers.h"

#ifdef COMBO_ENABLE
#   include "combos.h"
#endif


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
        KC_SCLN,            KC_COMM,    KC_H,    KC_K,    KC_V,
                                XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_GAME] = LAYOUT(
        KC_ESC,             KC_Q,       KC_W,      KC_E,        KC_R,
        KC_LSFT,            KC_A,       KC_S,      KC_D,        KC_F,
        KC_LCTL,            KC_Z,       KC_X,      KC_C,        KC_V,
                                LT(_NUM, KC_TAB), LT(_GAME_R, KC_ENT), KC_SPC
    ),
    [_GAME_R] = LAYOUT(
        LT(_CFG, KC_O),     KC_I,       KC_U,      KC_Y,        KC_T,
        KC_L,               KC_K,       KC_J,      KC_H,        KC_G,
        KC_DOT,            KC_COMM,     KC_M,      KC_N,        KC_B,
                                XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_SYM] = LAYOUT(
        LSFT(KC_GRV),   LSFT(KC_1),    LSFT(KC_2), LSFT(KC_3),  LSFT(KC_EQL),
        XXXXXXX,        LSFT(KC_4),    LSFT(KC_5), LSFT(KC_6),  LSFT(KC_MINS),
        LSFT(KC_BSLS),  LSFT(KC_7),    LSFT(KC_8), LSFT(KC_9),  LSFT(KC_0),
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
        KC_COMM,  KC_1,  KC_2,  KC_3,  KC_EQL,
        KC_0,     KC_4,  KC_5,  KC_6,  KC_MINS,
        KC_DOT,   KC_7,  KC_8,  KC_9,  KC_SLSH,
                                        _______, TD(TD_FN_SPC_NAV_TAB), _______
    ),
    [_FKEYS] = LAYOUT(
        KC_F15,  KC_F1,  KC_F2,  KC_F3,  KC_F11,
        KC_F10,  KC_F4,  KC_F5,  KC_F6,  KC_F12,
        KC_F14,  KC_F7,  KC_F8,  KC_F9,  KC_F13,
                                        _______, _______, _______
    ),
    [_MM] = LAYOUT(
        KC_LAUNCHPAD,  KC_MEDIA_NEXT_TRACK,  KC_KB_VOLUME_UP,    KC_BRIGHTNESS_UP,   KC_SYSTEM_WAKE,
        KC_MISSION_CONTROL, KC_MEDIA_PREV_TRACK,  KC_KB_VOLUME_DOWN,  KC_BRIGHTNESS_DOWN, KC_SYSTEM_SLEEP,
        XXXXXXX,  KC_MEDIA_PLAY_PAUSE,  KC_KB_MUTE,         XXXXXXX,            KC_KB_POWER,
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
        XXXXXXX,        OSL(_SYM3),     OSL(_FKEYS),       OSL(_NAV),      KC_F17,
        OSL(_MM),       OSL(_SYM),      OSL(_NUM),      TO(_A),         KC_F18,
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
}
