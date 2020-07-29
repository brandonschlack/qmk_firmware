/* Copyright 2020 Brandon Schlack
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_all(
        KC_MUTE, KC_MUTE,          KC_MPLY,
        KC_PMNS, KC_P7,   KC_P8,   KC_P9,
        KC_PPLS, KC_P4,   KC_P5,   KC_P6,
        KC_BSPC, KC_P1,   KC_P2,   KC_P3,
        KC_PENT, MO(1), KC_P0,   KC_PDOT
    ),
    [1] = LAYOUT_all(
        _______, _______,          _______,
        KC_PSLS, KC_F21,  KC_F22,  KC_F23,
        KC_PAST, KC_F18,  KC_F19,  KC_F20,
        KC_NLCK, KC_F15,  KC_F16,  KC_F17,
        RESET,   _______, KC_F13,  KC_F14
    )
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left encoder */
        if (clockwise) {
            tap_code16(KC_VOLU);
        } else {
            tap_code16(KC_VOLD);
        }
    } else if (index == 1) { /* Right encoder */
        if (clockwise) {
            tap_code16(KC_MNXT);
        } else {
            tap_code16(KC_MPRV);
        }
    }
}

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_logo_timer = 0;
bool oled_logo_cleared = false; // Set to true if you don't want a logo at all

static void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Numpad\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Macropad\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Some Other Layer"), false);
    }

    // Empty Line
    oled_write_ln_P(PSTR(" "), false);

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR(" NUM ") : PSTR("     "), led_state.num_lock);
    oled_write_P(led_state.caps_lock ? PSTR(" CAP ") : PSTR("     "), led_state.caps_lock);
    oled_write_P(led_state.scroll_lock ? PSTR(" SCR ") : PSTR("     "), led_state.scroll_lock);
}

/*
    How to convert your own image:
    https://docs.splitkb.com/hc/en-us/articles/360013811280
*/
static void render_logo(void) {
    static const char radpad_logo [] PROGMEM = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf8,
        0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf0, 0xf0, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf0, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x60, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0,
        0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf8,
        0xf8, 0xf0, 0xf0, 0xe0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xf0, 0xf0, 0xe0,
        0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0,
        0xf0, 0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7,
        0xf1, 0xf8, 0xf8, 0xfc, 0xfc, 0xfe, 0x7f, 0x3f, 0x1f, 0x1f, 0x0f, 0x0f, 0x07, 0x00, 0x80, 0xe0,
        0xf8, 0xfc, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xfe, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xc0,
        0xc0, 0xf0, 0xfd, 0xff, 0xff, 0xff, 0x3f, 0x0f, 0x01, 0x00, 0x00, 0x81, 0xc1, 0xff, 0xff, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xf9, 0xf8, 0xfc, 0x7e, 0x7e, 0x3f,
        0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x03, 0x80, 0xc0, 0xf0, 0xfc, 0xff, 0xff, 0xff, 0xbf, 0xff, 0xff,
        0xff, 0xff, 0xe0, 0xc0, 0xc0, 0xe0, 0xe0, 0xc0, 0x80, 0xe0, 0xfd, 0xff, 0xff, 0xff, 0x7f, 0x0f,
        0x03, 0x00, 0x00, 0x81, 0xc1, 0xf3, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0xfc, 0xff, 0xff, 0x7f, 0x1f, 0x0f, 0x03, 0x03, 0x03, 0x01,
        0x01, 0x01, 0x0f, 0x7f, 0xff, 0xff, 0xfe, 0x80, 0x00, 0xe0, 0xf0, 0xf8, 0xfc, 0xff, 0xff, 0x3f,
        0x3f, 0x1f, 0x1f, 0x0f, 0x0f, 0x0f, 0x07, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xe3, 0xf9, 0xff,
        0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xfc, 0xfc, 0x7e, 0x3e, 0x3f, 0x1f, 0x1f, 0x8f, 0xe7, 0xff,
        0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x07, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0xc0, 0xf0, 0xf8, 0xfc, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x1f, 0x0f, 0x0f, 0x0f, 0x07, 0x1f,
        0xff, 0xff, 0xff, 0xff, 0xc3, 0xe3, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xf8, 0xfc,
        0x7e, 0x3e, 0x3f, 0x1f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x07, 0x00, 0x01, 0x01, 0x03, 0x03, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x03, 0x07, 0x07, 0x07, 0x07, 0x03,
        0x07, 0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x1f, 0x1f, 0x0f,
        0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x01, 0x03, 0x03, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(radpad_logo, sizeof(radpad_logo));
}

void oled_task_user(void) {
    if (oled_logo_cleared) {
        render_status();
    } else {
        if (timer_elapsed32(oled_logo_timer) > OLED_LOGO_TIMEOUT) {
            oled_clear();
            oled_logo_cleared = true;
            render_status();
        } else {
            render_logo();
        }
    }
}
#endif
