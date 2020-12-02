#include QMK_KEYBOARD_H
#include "brandonschlack.h"

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

#define LWR_B      LT(_LOWER, KC_B)
#define TD_BRC     TD(TD_LR_BRC)
#define TD_QUOT    TD(TD_SD_QUOT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    TD_BRC,  KC_BSPC,      KC_VOLU, \
        HY_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          KC_H,    KC_J,    KC_K,    KC_L,    TD_QUOT,          KC_ENT,         KC_VOLD, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    LWR_B,         KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,      KC_UP,       PLY_FN1, \
        KC_LCTL, KC_LOPT,          KC_LCMD, XXXXXXX, SPC_RAI,       SPC_RAI, XXXXXXX, KC_RCMD,                        KC_LEFT, KC_DOWN, KC_RGHT \
    ),

    [_LOWER] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DELT,      MC_SLPD, \
        _______, KC_MUTE, KC_VOLU, NXT_WIN, PRV_TAB, MC_BACK,       MC_FWRD, NXT_TAB, _______, _______, _______,          _______,        KC_MUTE, \
        SF_CAPS, KC_MPRV, KC_VOLD, KC_MNXT, PX_AFLL, _______,       OP_AFLL, _______, _______, _______, _______, _______,      KC_PGUP,     _______, \
        _______, _______,          _______, XXXXXXX, _______,       _______, XXXXXXX, _______,                        KC_HOME, KC_PGDN, KC_END \
    ),

    [_RAISE] = LAYOUT(
        KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,       KC_CIRC, KC_AMPR, KC_ASTR, KC_LBRC, KC_RBRC, KC_BSLS, _______,      KC_MNXT, \
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,             _______,        KC_MPRV, \
        _______, KC_LPRN, KC_RPRN, KC_SCLN, KC_DOT,  _______,       _______, KC_MINS, KC_PLUS, KC_ASTR, KC_SLSH, KC_EQL,       _______,     _______, \
        _______, _______,          _______, XXXXXXX, _______,       _______, XXXXXXX, _______,                        _______, _______, _______ \
    ),

    [_ADJUST] = LAYOUT(
        QM_MAKE, _______, _______, EEP_RST, RESET,   _______,       _______, _______, _______, _______, _______, _______, _______,      _______, \
        RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD, _______,       _______, _______, _______, _______, _______,          _______,        _______, \
        _______, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______,       _______, _______, _______, _______, _______, _______,      _______,     _______, \
        _______, _______,          _______, XXXXXXX, _______,       _______, XXXXXXX, _______,                        _______, _______, _______ \
    )
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
    writePin(TOP_LED, LED_ON(IS_LAYER_ON(_RAISE)));
    writePin(MIDDLE_LED, LED_ON(IS_LAYER_ON(_LOWER))); // Use for Nav Mode
    writePin(BOTTOM_LED, LED_ON(led_state.caps_lock)); // Use for Caps Lock
    return false; // Override default set by KB
}
#endif
