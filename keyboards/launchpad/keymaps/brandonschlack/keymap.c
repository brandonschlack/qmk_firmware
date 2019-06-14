#include QMK_KEYBOARD_H
#include "brandonschlack.h"

extern keymap_config_t keymap_config;

// Layers defined in brandonschlack.h

enum launchpad_dances {
    TD_LGHT = 0,
    TD_MAGC,
    TD_CMTB
};

typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_SINGLE_TAP
} td_state_t;
static td_state_t td_state;

int cur_dance (qk_tap_dance_state_t *state);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Navigation
 * ,-------------.
 * | PTab | NTab |
 * |------+------|
 * | SclL | SclU |
 * |------+------|
 * | SclR | SclD |
 * |------+------|
 * |LstTab|ClsTab|
 * `-------------'
 */
[_NAVI] = LAYOUT( \
    S(G(KC_LBRC)), S(G(KC_RBRC)), \
    MC_WH_L, MC_WH_U, \
    MC_WH_R, MC_WH_D, \
    TD(TD_LGHT), TD(TD_MAGC) \
),

/* Reeder
 * ,-------------.
 * |CMDTAB|  H   |
 * |------+------|
 * |   P  |  K   |
 * |------+------|
 * |   N  |  J   |
 * |------+------|
 * |   L  |  S   |
 * `-------------'
 */
[_REEDER] = LAYOUT( \
    TD(TD_CMTB), KC_H, \
    KC_P, KC_K, \
    KC_N, KC_J, \
    TD(TD_LGHT), TD(TD_MAGC) \
),

/* Media
 * ,-------------.
 * | Mute | PlPs |
 * |------+------|
 * | VolU | TrkN |
 * |------+------|
 * | VolD | TrkP |
 * |------+------|
 * | Spc  | Plyr |
 * `-------------'
 */
[_MEDIA] = LAYOUT( \
    KC_MUTE, KC_MPLY, \
    KC_VOLU, KC_MFFD, \
    KC_VOLD, KC_MRWD, \
    TD(TD_LGHT), TD(TD_MAGC) \
),

/* Keypad
 * ,-------------.
 * |   1  |  2   |
 * |------+------|
 * |   3  |  4   |
 * |------+------|
 * |   5  |  6   |
 * |------+------|
 * |   7  |  8   |
 * `-------------'
 */
[_KEYPAD] = LAYOUT( \
    KC_P1,     KC_P2, \
    KC_P3,     KC_P4, \
    KC_P5,     KC_P6, \
    TD(TD_LGHT), TD(TD_MAGC) \
),

/* Lights
 * ,-------------.
 * | Mode-| Mode+|
 * |------+------|
 * | HUE- | HUE+ |
 * |------+------|
 * | SAT- | SAT+ |
 * |------+------|
 * | Magc |RGBTOG|
 * `-------------'
 */
[_LIGHT] = LAYOUT( \
    RGB_RMOD, RGB_MOD, \
    RGB_HUD,  RGB_HUI, \
    RGB_SAD,  RGB_SAI, \
    TG(_MAGIC), RGB_TOG \
),

/* Magic
 * ,-------------.
 * | Make | Rset |
 * |------+------|
 * | Navi | Redr |
 * |------+------|
 * | Meda | Kypd |
 * |------+------|
 * | Lght | XXXX |
 * `-------------'
 */
[_MAGIC] = LAYOUT( \
    KC_MAKE, RESET, \
    TG_NAVI, TG_REDR, \
    TG_MEDA, TG_KYPD, \
    TG(_LIGHT), XXXXXXX \
)

};

void matrix_init_user(void) {

}

// Runs once after keyboard initializes
void keyboard_post_init_keymap(void) {
};

/**
 * Tap Dances
 */
int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return SINGLE_TAP;
        } else {
            return SINGLE_HOLD;
        }
    }
    if (state->count == 2) {
        return DOUBLE_SINGLE_TAP;
    } else {
        return 3;
    }
}

void dance_light_layer_finished (qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case DOUBLE_SINGLE_TAP:
            layer_on(_LIGHT);
            break;
        default:
            switch (biton32(layer_state)) {
                case _NAVI:
                    register_code16(S(G(KC_T)));
                    break;
                case _REEDER:
                    register_code(KC_L);
                    break;
                case _MEDIA:
                    register_code(KC_SPC);
                    break;
                case _KEYPAD:
                    register_code(KC_P7);
                    break;
            }
            break;
    }
}
void dance_light_layer_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case DOUBLE_SINGLE_TAP:
            break;
        default:
            switch (biton32(layer_state)) {
                case _NAVI:
                    unregister_code16(S(G(KC_T)));
                    break;
                case _REEDER:
                    unregister_code(KC_L);
                    break;
                case _MEDIA:
                    unregister_code(KC_SPC);
                    break;
                case _KEYPAD:
                    unregister_code(KC_P7);
                    break;
            }
            break;
    }
}

void dance_magic_layer_finished (qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_HOLD:
            layer_on(_MAGIC);
            break;
        default:
            switch (biton32(layer_state)) {
                case _NAVI:
                    register_code16(G(KC_W));
                    break;
                case _REEDER:
                    register_code(KC_S);
                    break;
                case _MEDIA:
                    register_code16(MC_PLYR);
                    break;
                case _KEYPAD:
                    register_code(KC_P8);
                    break;
            }
            break;
    }
}
void dance_magic_layer_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_HOLD:
            layer_off(_MAGIC);
            break;
        default:
            switch (biton32(layer_state)) {
                case _NAVI:
                    unregister_code16(G(KC_W));
                    break;
                case _REEDER:
                    unregister_code(KC_S);
                    break;
                case _MEDIA:
                    unregister_code16(MC_PLYR);
                    break;
                case _KEYPAD:
                    unregister_code(KC_P8);
                    break;
            }
            break;
    }
}

void dance_command_tab_finished (qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case DOUBLE_SINGLE_TAP:
            register_code(KC_R);
            break;
        default:
            switch (biton32(layer_state)) {
                case _REEDER:
                    register_code16(G(KC_TAB));
                    break;
            }
            break;
    }
}
void dance_command_tab_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case DOUBLE_SINGLE_TAP:
            unregister_code(KC_R);
            break;
        default:
            switch (biton32(layer_state)) {
                case _REEDER:
                    unregister_code16(G(KC_TAB));
                    break;
            }
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LGHT] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_light_layer_finished, dance_light_layer_reset),
    [TD_MAGC] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_magic_layer_finished, dance_magic_layer_reset),
    [TD_CMTB] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_command_tab_finished, dance_command_tab_reset)
};
