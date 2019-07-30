/* Copyright 2019 MechMerlin
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
#include "brandonschlack.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* N Layer: Blank Template
 * ,---------------------------------------------------------------.
 * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * |---------------------------------------------------------------|
 * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |   |
 * |---------------------------------------------------------------|
 * |      |   |   |   |   |   |   |   |   |   |   |   |        |   |
 * |---------------------------------------------------------------|
 * |        |   |   |   |   |   |   |   |   |   |   |      |   |   |
 * |---------------------------------------------------------------|
 * |    |    |    |                       |    |    |  |   |   |   |
 * `---------------------------------------------------------------'
 */

/* Base Layer: Mac
 * ,---------------------------------------------------------------.
 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|Hom|
 * |---------------------------------------------------------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Backs|PgU|
 * |---------------------------------------------------------------|
 * |HyCaps|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter   |PgD|
 * |---------------------------------------------------------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift |Up |End|
 * |---------------------------------------------------------------|
 * |Ctl |Alt |Gui |         Space         |Gui |FnPy|  |Lef|Dow|Rig|
 * `---------------------------------------------------------------'
 */
[_MAC] = LAYOUT(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  KC_HOME, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          KC_PGUP, \
  HY_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   KC_UP,   KC_END,  \
  KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RGUI, MM_FNPY,                   KC_LEFT, KC_DOWN, KC_RGHT),
/* Function Layer: Mac
 * ,---------------------------------------------------------------.
 * |MKE| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|LHP|MSN|SLP|
 * |---------------------------------------------------------------|
 * |     |   |   |   |RST|   |   |   |   |   |F13|F14|F15|  Del|VlU|
 * |---------------------------------------------------------------|
 * |      |   |   |   |   |   |   |   |   |   |   |   | TgMagic|VlD|
 * |---------------------------------------------------------------|
 * |        |   |   |   |   |   |   |   |Prv|Nxt|Ply|MutSft|PgU|   |
 * |---------------------------------------------------------------|
 * |    |    |    |                       |    |    |  |Hom|PgD|End|
 * `---------------------------------------------------------------'
 */
[_MACFN] = LAYOUT(
  KC_MAKE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  MC_LHPD, MC_MSSN, MC_SLPD, \
  _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______, KC_F13,  KC_F14,  KC_F15,  KC_DEL,           KC_VOLU, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          TG_MAGC,          KC_VOLD, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MRWD, KC_MFFD, KC_MPLY, MM_RSFT,                   KC_PGUP, _______, \
  _______, _______, _______,                   _______,                            _______, _______,                   KC_HOME, KC_PGDN, KC_END ),

/***********
 *  Magic  *
 ***********/
/* Keyboard Layer: Magic
 * ,---------------------------------------------------------------.
 * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * |---------------------------------------------------------------|
 * |     |   |   |EEP|RST|   |   |   |   |   |   |   |   |     |   |
 * |---------------------------------------------------------------|
 * |      |   |   |   |   |   |   |   |   |   |   |   | TgMagic|   |
 * |---------------------------------------------------------------|
 * |        |   |   |   |   |   |   |   |   |   |   |      |   |   |
 * |---------------------------------------------------------------|
 * |    |    |    |                       |    |    |  |   |   |   |
 * `---------------------------------------------------------------'
 */
[_MAGIC] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, EEP_RST, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          TG_MAGC,          XXXXXXX, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,                   XXXXXXX, XXXXXXX, \
  _______, _______, _______,                   XXXXXXX,                            _______, _______,                   XXXXXXX, XXXXXXX, XXXXXXX),
};

void matrix_init_user(void) {

}

void matrix_scan_keymap(void) {

}

void led_set_user(uint8_t usb_led) {

}
