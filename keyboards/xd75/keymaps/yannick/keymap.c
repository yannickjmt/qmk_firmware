/* Copyright 2017 Wunder
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

//

#include QMK_KEYBOARD_H

// Layer shorthand
#define _QW 0
#define _FN 5
#define _NUM 8
#define _NAV 6
// #define _EM 99

// tap FUNCT : caps lock KC_CAPS, hold : FUNCTION layer
#define FN_CAPS LT(_FN, KC_CAPS)

// tap RSHIFT : ;:, hold : Rshift
#define SHFT_COL RSFT_T(KC_SCLN)

#define NUMLAY TT(_NUM)
// #define NAVLAY LT(_NAV, KC_BSPC)
#define NAVLAY MO(_NAV)

// one shot mods for nav layer
#define N_CTRL OSM(MOD_LGUI) // TODO: MOD_LCTL for windows
#define N_SHFT OSM(MOD_LSFT)
#define N_ALT OSM(MOD_LALT)
#define N_GUI OSM(MOD_LCTL) // TODO: MOD_LGUI for windows
#define N_APP OSM(MOD_LCTL)

#define UNDO_MAC LGUI(KC_Z)
#define CUT_MAC LGUI(KC_X)
#define COPY_MC LGUI(KC_C)
#define PASTE_MC LGUI(KC_V)


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | `      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | \      | ]      | Y      | U      | I      | O      | P      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | FN_CAPS| A      | S      | D      | F      | G      | HOME   | DEL    | PG UP  | H      | J      | K      | L      | '      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | END    | UP     | PG DN  | N      | M      | ,      | .      | /      |SHFT_APO|
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | LALT   | SPACE  | ENTER  | LOWER  | LEFT   | DOWN   | RIGHT  | RAISE  | SPACE  | FRENCH | APP    | RALT   | RCTRL  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_QW] = LAYOUT_ortho_5x15( /* QWERTY */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_BSLS, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
    FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME, KC_DEL,  KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_END,  KC_UP,   KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,SHFT_COL,
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_ENT,  NAVLAY,  KC_LEFT, KC_DOWN, KC_RGHT, NUMLAY,  KC_SPC,  XXXXXXX, KC_APP,  KC_RALT, KC_RCTL
  ),

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | XXXXXXX| F1     | F2     | F3     | F4     | F5     | F11    | F12    | XXXXXXX| F6     | F7     | F8     | F9     | F10    | RESET  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXXX| !      | @      | #      | $      | %      | XXXXXXX| XXXXXXX| XXXXXXX| ^      | &      | *      | (      | )      | XXXXXXX|
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXXX| XXXXXXX| XXXXXXX| XXXXXXX| RGB SD | RGB SI | XXXXXXX| XXXXXXX| XXXXXXX| XXXXXXX| XXXXXXX| XXXXXXX| XXXXXXX| XXXXXXX| XXXXXXX|
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | XXXXXXX| RGB HD | RGB HI | RGB VD | RGB VI | XXXXXXX|        | XXXXXXX| PR SCR | SCR LK | PAUSE  | XXXXXXX| XXXXXXX|        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        | RGB TG | RGB RMD| RGB MD |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
    XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11 , KC_F12 , XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  RESET,
    XXXXXXX, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, XXXXXXX, XXXXXXX, XXXXXXX, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, RGB_SAD, RGB_SAI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, RGB_HUD, RGB_HUI, RGB_VAD, RGB_VAI, XXXXXXX, _______, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, RGB_TOG, RGB_RMOD,RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

/* NUMPAD
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        | =      | /      | *      | -      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | `      | +      | [      | ]      | =      |        |        |        |        | 7      | 8      | 9      | +      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | ~      | _      | (      | )      | -      |        |        |        |        | 4      | 5      | 6      | +      |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | \      | {      | }      | |      |        |        |        |        | 1      | 2      | 3      | SPC    |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        | toggle | 0      | 0      | 0      | SPC    |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_NUM] = LAYOUT_ortho_5x15(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_EQL , KC_SLSH, KC_ASTR, KC_MINS, _______,
    _______, KC_GRV,S(KC_EQL), KC_LBRC, KC_RBRC, KC_EQL , _______, _______, _______, _______, KC_7   , KC_8   , KC_9   , KC_PLUS, _______,
    _______,S(KC_GRV),S(KC_MINS),S(KC_9),S(KC_0),KC_MINS, _______, _______, _______, _______, KC_4   , KC_5   , KC_6   , KC_PLUS, _______,
    _______,_______,KC_BSLS,S(KC_LBRC),S(KC_RBRC),S(KC_BSLS),_______,_______,_______,_______, KC_1   , KC_2   , KC_3   , KC_SPC , _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,TG(_NUM), KC_P0  , KC_P0  , KC_PDOT, KC_SPC , _______
 ),

/* EMPTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

//   [_EM] = LAYOUT_ortho_5x15(
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//   ),

/* NAV
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |  PgUp  |  Home  |   Up   |   End  |ScrollUp|        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |Ctrl/Win|  Shift |   Alt  |Cmd/Ctrl|        |        |        |        |  PgDown|  Left  |  Down  |  Right |ScrollDn|        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | Ctrl Z | Crtl X | Ctrl C | Ctrl C |        |        |        |        |Prev win|Next win|Prev Tab|Next tab|        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_NAV] = LAYOUT_ortho_5x15(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_WH_U, _______,
    _______, N_GUI  , N_SHFT , N_ALT  , N_CTRL , _______, _______, _______, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_WH_D, _______,
    _______,UNDO_MAC, CUT_MAC, COPY_MC,PASTE_MC, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
