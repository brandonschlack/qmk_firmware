 /*
 Copyright 2020 Alec Penland
 Copyright 2020 Garret Gartner
 Copyright 2020 Brandon Schlack

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

#include QMK_KEYBOARD_H
#include "brandonschlack.h"

/**
 * Layer Names
 *
 * Layers mostly used for macro keys
 */
#define _REEDER      _M1
#define _NAV         _M2

/**
 * Keycodes & Macros
 */
#define TG_BASE   TO(_BASE)
#define TG_REDR   TO(_REEDER)
#define TG_NAV    TO(_NAV)

// Tap Dance declarations
enum {
    TD_LR_BRC,
    TD_SD_QUOT
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for LBracket, twice for RBracket
    [TD_LR_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    // Tap once for Single Quote, twice for Double Quote
    [TD_SD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_DQT)
};
#define TD_BRC     TD(TD_LR_BRC)
#define TD_QUOT    TD(TD_SD_QUOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default QWERTY layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐   ┌───┐
     * │Esc│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │{ [│BkS│   │Ply│
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤   ├───┤
     * │HyTb│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ' │Enter │   │Nxt│
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┘   ├───┤
     * │Shift │ Z │ X │ C │ V │ B │ N │ M │ , │ . │Sft/│ ┌───┐ │Prv│
     * ├────┬─┴─┬─┴──┬┴───┴───┴─┬─┴───┴──┬┴───┼───┴┬───┘ │ ↑ │ └───┘
     * │Ctrl│Opt│Cmd │ Spc-Rse  │ Spc-Rse│ Cmd│ Lwr│ ┌───┼───┼───┐
     * └────┴───┴────┴──────────┴────────┴────┴────┘ │ ← │ ↓ │ → │
     *                                               └───┴───┴───┘
     */
    [_BASE] = LAYOUT_split_space(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    TD_BRC,  KC_BSPC,         KC_MPLY,
        HY_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    TD_QUOT,      KC_ENT,              KC_MNXT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  SF_SLSH,               KC_UP,      KC_MPRV,
        KC_LCTL, KC_LOPT, KC_LCMD,               SPC_RAI,         SPC_RAI,          KC_RCMD,      LOWER,        KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Reeder
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐   ┌───┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │Clr│
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤   ├───┤
     * │    │   │   │   │   │   │   │   │   │   │   │      │   │Sb-│
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┘   ├───┤
     * │      │   │   │   │   │   │   │   │   │   │    │ ┌───┐ │Sb+│
     * ├────┬─┴─┬─┴──┬┴───┴───┴─┬─┴───┴──┬┴───┼───┴┬───┘ │   │ └───┘
     * │    │   │    │          │        │    │    │ ┌───┼───┼───┐
     * └────┴───┴────┴──────────┴────────┴────┴────┘ │   │   │   │
     *                                               └───┴───┴───┘
     */
    [_REEDER] = LAYOUT_split_space(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        RD_OPEN,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,            RD_SPRV,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               _______,   RD_SNXT,
        _______, _______, _______,               _______,         _______,          _______,      _______,      _______, _______, _______
    ),

    /* Nav
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐   ┌───┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │Cls│
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤   ├───┤
     * │    │   │   │   │   │   │   │   │   │   │   │      │   │NxT│
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┘   ├───┤
     * │      │   │   │   │   │   │   │   │   │   │    │ ┌───┐ │CTb│
     * ├────┬─┴─┬─┴──┬┴───┴───┴─┬─┴───┴──┬┴───┼───┴┬───┘ │   │ └───┘
     * │    │   │    │          │        │    │    │ ┌───┼───┼───┐
     * └────┴───┴────┴──────────┴────────┴────┴────┘ │   │   │   │
     *                                               └───┴───┴───┘
     */
    [_NAV] = LAYOUT_split_space(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        CLS_TAB,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,            NXT_TAB,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               _______,   CMD_TAB,
        _______, _______, _______,               _______,         _______,          _______,      _______,      _______, _______, _______
    ),

    /* LOWER: Function layer
     * ┌────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐   ┌───┐
     * │Del │F1 │F2 │F3 │F4 │F5 │F6 │BrD│BrU│Msn│LHP│NxW│Slp│   │Ply│
     * ├────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤   ├───┤
     * │     │F7 │F8 │F9 │F10│F11│F12│Bck│Fwd│PvT│NxT│      │   │Nxt│
     * ├─────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┘   ├───┤
     * │SftCaps│   │   │   │   │   │   │   │   │   │    │ ┌───┐ │Prv│
     * ├────┬──┴─┬─┴──┬┴───┴───┴─┬─┴───┴──┬┴───┼───┴┬───┘ │PgU│ └───┘
     * │    │    │    │          │        │    │    │ ┌───┼───┼───┐
     * └────┴────┴────┴──────────┴────────┴────┴────┘ │Hom│PgD│End│
     *                                                └───┴───┴───┘
     */
    [_LOWER] = LAYOUT_split_space(
        KC_DELT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_BRMD, KC_BRMU, MC_MSSN, MC_LHPD, NXT_WIN, MC_SLPD,        KC_MPLY,
        _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  MC_BACK, MC_FWRD, PRV_TAB, NXT_TAB,      _______,            KC_MNXT,
        SF_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               KC_PGUP,   KC_MPRV,
        _______, _______, _______,               _______,         _______,          _______,      _______,      KC_HOME, KC_PGDN, KC_END
    ),

    /* RAISE: Numbers, Symbols & Function Layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐   ┌───┐
     * │~ `│ ! │ @ │ # │ $ │ % │ ^ │ & │ * │ [ │ ] │ \ │   │   │Mut│
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤   ├───┤
     * │    │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │      │   │Nxt│
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┘   ├───┤
     * │      │ ( │ ) │ ; │ . │   │ - │ + │ * │ / │ =  │ ┌───┐ │Prv│
     * ├────┬─┴─┬─┴──┬┴───┴───┴─┬─┴───┴──┬┴───┼───┴┬───┘ │   │ └───┘
     * │    │   │    │          │        │    │    │ ┌───┼───┼───┐
     * └────┴───┴────┴──────────┴────────┴────┴────┘ │   │   │   │
     *                                               └───┴───┴───┘
     */
    [_RAISE] = LAYOUT_split_space(
        KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_BSLS, _______,         KC_MUTE,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,         _______,             KC_MNXT,
        _______, KC_LPRN, KC_RPRN, KC_SCLN, KC_DOT,  _______, KC_MINS, KC_PLUS, KC_ASTR, KC_SLSH, KC_EQL,                _______,    KC_MPRV,
        _______, _______, _______,               _______,         _______,          _______,      _______,      _______, _______, _______
    ),

    /* ADJUST
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐   ┌───┐
     * │Mke│   │   │EEP│RST│   │   │   │   │   │   │   │   │   │   │
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤   ├───┤
     * │    │   │   │   │   │   │   │   │   │   │   │      │   │   │
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┘   ├───┤
     * │      │   │   │   │   │   │   │   │   │   │    │ ┌───┐ │   │
     * ├────┬─┴─┬─┴──┬┴───┴───┴─┬─┴───┴──┬┴───┼───┴┬───┘ │   │ └───┘
     * │    │   │    │          │        │    │    │ ┌───┼───┼───┐
     * └────┴───┴────┴──────────┴────────┴────┴────┘ │   │   │   │
     *                                               └───┴───┴───┘
     */
    [_ADJUST] = LAYOUT_split_space(
        QM_MAKE, _______, _______, EEP_RST, RESET,   _______, _______, _______, _______, _______, _______, _______, _______,        TG_BASE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,            TG_REDR,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               _______,   TG_NAV,
        _______, _______, _______,               _______,         _______,          _______,      _______,      _______, _______, _______
    )

    /* Blank
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐   ┌───┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │   │
     * ├───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤   ├───┤
     * │    │   │   │   │   │   │   │   │   │   │   │      │   │   │
     * ├────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴──┬───┘   ├───┤
     * │      │   │   │   │   │   │   │   │   │   │    │ ┌───┐ │   │
     * ├────┬─┴─┬─┴──┬┴───┴───┴─┬─┴───┴──┬┴───┼───┴┬───┘ │   │ └───┘
     * │    │   │    │          │        │    │    │ ┌───┼───┼───┐
     * └────┴───┴────┴──────────┴────────┴────┴────┘ │   │   │   │
     *                                               └───┴───┴───┘
     */
    // [BLANK] = LAYOUT_split_space(
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,        _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,      _______,            _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,               _______,   _______,
    //     _______, _______, _______,               _______,         _______,          _______,      _______,      _______, _______, _______
    // )
};

void keyboard_pre_init_user(void) {
    setPinOutput(TOP_LED);
    setPinOutput(MIDDLE_LED);
    setPinOutput(BOTTOM_LED);
}

layer_state_t layer_state_set_keymap(layer_state_t state) {
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    return state;
}

#ifdef USE_LEDS_FOR_LAYERS
bool led_update_keymap(led_t led_state) {
    writePin(TOP_LED, LED_ON(IS_LAYER_ON(_REEDER))); // Use for Reeder Mode
    writePin(MIDDLE_LED, LED_ON(IS_LAYER_ON(_NAV))); // Use for Nav Mode
    writePin(BOTTOM_LED, LED_ON(led_state.caps_lock)); // Use for Caps Lock
    return false; // Override default set by KB
}
#endif

void encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t layer = get_highest_layer(layer_state);

    switch (layer) {
        case _REEDER:
            if (clockwise) {
                tap_code(RD_INXT);
            } else {
                tap_code(RD_IPRV);
            }
            break;
        case _NAV:
            if (clockwise) {
                tap_code16(MC_WH_D);
            } else {
                tap_code16(MC_WH_U);
            }
            break;
        default:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
    }
}
