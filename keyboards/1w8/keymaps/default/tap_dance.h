// tap_dance.h

#include QMK_KEYBOARD_H

// Tap dance enums
enum {
    TD_R_SPC_NAV_TAB,
    TD_FN_SPC_NAV_TAB,
    TD_S2_SPC_NAV_TAB,
    TD_SYM_NUM_ENT,
    TD_CFG_ENT,
};


extern tap_dance_action_t tap_dance_actions[];

