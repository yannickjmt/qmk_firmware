/* Copyright 2019 Yannick Jamet
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

#ifdef IS_YANNICK
#include "secrets.h"
#else
#define EMAIL_PERSO "test@test.com"
#define EMAIL_PRO "testpro@pro.com"
#endif

// for PREVWIN and NEXTWIN macro
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

// Layer shorthand
#define _MAC 0
#define _WIN 1
#define _FN 2
#define _NUM 3
#define _NAV 4
#define _NAV_OS 5
#define _FR 6

#define FN_CAPS MO(_FN)

// tap RSHIFT : ;:, hold : Rshift
#define SHFT_COL RSFT_T(KC_SCLN)

#define NUMLAY TT(_NUM)
#define FRLAY MO(_FR)

// nav layer
#define OS_SHFT OSM(MOD_LSFT)
#define OS_ALT OSM(MOD_LALT)
// CTRL and WGUI defined in macros as they change according to base layer


// dynamic macro
#define DYNREC1 DYN_REC_START1
#define DYNREC2 DYN_REC_START2
#define DYNGO1 DYN_MACRO_PLAY1
#define DYNGO2 DYN_MACRO_PLAY2
#define DYNSTP DYN_REC_STOP

// French chars
enum unicode_names {
  E_AIG,
  E_AIG_MAJ,
  E_GRV,
  E_GRV_MAJ,
  E_CIRC,
  E_CIRC_MAJ,
  E_TREMA,
  E_TREMA_MAJ,
  A_CIRC,
  A_CIRC_MAJ,
  A_GRV,
  A_GRV_MAJ,
  C_CEDILLE,
  C_CEDILLE_MAJ,
  CARRE,
  CUBE,
  EURO,
  BAHT,
  COPYRIGHT,
  REGISTERED,
  OMEGA,
  OMEGA_MAJ,
  O_CIRC,
  O_CIRC_MAJ,
  U_GRAV,
  U_GRAV_MAJ,
  OE,
  OE_MAJ,
  PI,
  DEGREE,
  N_TILDE,
  N_TILDE_MAJ,
  MICRO,
  SIGMA,
  INFEQ,
  SUPEQ,
  GUILL_G,
  GUILL_R,
  UNEQUAL,
  PRETTYMUCH,
  INFINIT,
};

const uint32_t PROGMEM unicode_map[] = {
  [E_AIG]  = 0x00E9,  // 0 é
  [E_AIG_MAJ] = 0x00C9,  // 1 É
  [E_GRV]  = 0x00E8,  // 2 è
  [E_GRV_MAJ] = 0x00C8,  // 3 È
  [E_CIRC]  = 0x00EA,  // 4 ê
  [E_CIRC_MAJ] = 0x00CA,  // 5 Ê
  [E_TREMA]  = 0x00EB,  // 6 ë
  [E_TREMA_MAJ] = 0x00CB,  // 7 Ë
  [A_CIRC]  = 0x00E2,  // 8 â
  [A_CIRC_MAJ] = 0x00C2,  // 9 Ê
  [A_GRV]  = 0x00E0,  // 10 Â
  [A_GRV_MAJ] = 0x00C0,  // 11 À
  [C_CEDILLE]  = 0x00E7,  // 12 ç
  [C_CEDILLE_MAJ] = 0x00C7,  // 13 Ç
  [CARRE]  = 0x00B2,  // 14 ²
  [CUBE] = 0x00B3,  // 15 ³
  [EURO]  = 0x20AC,  // 16 €
  [BAHT] = 0x0E3F,  // 17 ฿
  [COPYRIGHT]  = 0x00A9,  // 18 ©
  [REGISTERED] = 0x00AE,  // 19 ®
  [OMEGA]  = 0x03C9,  // 20 ω
  [OMEGA_MAJ] = 0x03A9,  // 21 Ω
  [O_CIRC]  = 0x00F4,  // 22 ô
  [O_CIRC_MAJ] = 0x00D4,  // 23 Ô
  [U_GRAV]  = 0x00F9,  // 24 ù
  [U_GRAV_MAJ] = 0x00D9,  // 25 Ù
  [OE]  = 0x0153,  // 26 œ
  [OE_MAJ] = 0x0152,  // 27 Œ
  [PI] = 0x03C0, // 28 π
  [DEGREE] = 0x00B0, // 29 °
  [N_TILDE]  = 0x00F1,  // 30 ñ
  [N_TILDE_MAJ] = 0x00D1,  // 31 Ñ
  [MICRO]  = 0x00B5,  // 32 µ
  [SIGMA] = 0x03C3,  // 33 σ
  [INFEQ]  = 0x2264,  // 34 ≤
  [SUPEQ] = 0x2265,  // 35 ≥
  [GUILL_G]  = 0x00AB,  // 36 «
  [GUILL_R] = 0x00BB,  // 37 »
  [UNEQUAL]  = 0x2260,  // 38 ≠
  [PRETTYMUCH] = 0x2248,  // 39 ≈
  [INFINIT] = 0x221E,  // 40 ∞
};

// initialize unicode mode
void eeconfig_init_user(void) {
  set_unicode_input_mode(UC_OSX);
}

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  NEXTWIN = SAFE_RANGE,
  PREVWIN,
  NEXTTAB,
  PREVTAB,
  N_CTRL,
  N_GUI,
  OS_GUI,
  OS_CTRL,
  N_APP,
  N_UNDO,
  N_CUT,
  N_COPY,
  N_PASTE,
  MAIL,
  MAILPRO,
  XCEL_V,
  XCEL_D,
  CLEARK,
  BASEMAC,
  BASEWIN,
  DYNAMIC_MACRO_RANGE,
};

#include "dynamic_macro.h"

#define M_PDESK TD(MAC_PREVIOUS_DESKTOP)
#define M_NDESK TD(MAC_NEXT_DESKTOP)
#define W_PDESK TD(WIN_PREVIOUS_DESKTOP)
#define W_NDESK TD(WIN_NEXT_DESKTOP)
#define NAVLAY TD(NAV_LAYER)

// tapdance keycodes
enum td_keycodes {
  MAC_PREVIOUS_DESKTOP,
  MAC_NEXT_DESKTOP,
  WIN_PREVIOUS_DESKTOP,
  WIN_NEXT_DESKTOP,
  NAV_LAYER
};

// tapdance states
typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_TAP,
  TRIPLE_TAP
} td_state_t;

// global instance of the tapdance state type
static td_state_t td_state;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* MAC
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | `      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | \      | ]      | Y      | U      | I      | O      | P      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | FN_CAPS| A      | S      | D      | F      | G      | HOME   | DEL    | PG UP  | H      | J      | K      | L      | '      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | END    | UP     | PG DN  | N      | M      | ,      | .      | /      |SHFT_APO|
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | CMD    | LALT   | SPACE  | ENTER  | LOWER  | LEFT   | DOWN   | RIGHT  | RAISE  | SPACE  | FRENCH | APP    | RALT   | CMD    |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_MAC] = LAYOUT_ortho_5x15( /* QWERTY MAC */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_BSLS, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
    FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME, KC_DEL,  KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_END,  KC_UP,   KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SHFT_COL,
    M_PDESK, KC_LGUI, KC_LALT, KC_SPC,  KC_ENT,  NAVLAY,  KC_LEFT, KC_DOWN, KC_RGHT, NUMLAY,  KC_SPC,  FRLAY  , N_APP,   KC_RALT, M_NDESK
  ),

/* WIN
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | `      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | \      | ]      | Y      | U      | I      | O      | P      | DEL    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | FN_CAPS| A      | S      | D      | F      | G      | HOME   | DEL    | PG UP  | H      | J      | K      | L      | '      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | END    | UP     | PG DN  | N      | M      | ,      | .      | /      |SHFT_APO|
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LGUI   | LCTRL  | LALT   | SPACE  | ENTER  | LOWER  | LEFT   | DOWN   | RIGHT  | RAISE  | SPACE  | FRENCH | APP    | RALT   | RCTRL  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_WIN] = LAYOUT_ortho_5x15( /* QWERTY WINDOWS */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_BSLS, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
    FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME, KC_DEL,  KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_END,  KC_UP,   KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SHFT_COL,
    W_PDESK, KC_LCTL, KC_LALT, KC_SPC,  KC_ENT,  NAVLAY,  KC_LEFT, KC_DOWN, KC_RGHT, NUMLAY,  KC_SPC,  FRLAY  , N_APP,   KC_RALT, W_NDESK
  ),

/* FUNCTION
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | XXXXXXX| F1     | F2     | F3     | F4     | F5     | F11    | F12    | XXXXXXX| F6     | F7     | F8     | F9     | F10    | RESET  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXXX| !      | @      | #      | $      | %      | DYNREC1| DYNSTP | DYNREC2| ^      | &      | *      | (      | )      | windows|
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | XXXXXXX| CAPSLOC| XXXXXXX| XXXXXXX| RGB SD | RGB SI | DYNGO1 | CLEARK | DYNGO2 | XXXXXXX| XXXXXXX| XXXXXXX| XXXXXXX| XXXXXXX| mac    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | XXXXXXX| RGB HD | RGB HI | RGB VD | RGB VI | MUTE   | VOL UP | XXXXXXX| PR SCR | SCR LK | PAUSE  | XXXXXXX| XXXXXXX|        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        | RGB TG | RGB RMD| RGB MD |        | VOL DN |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
    XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11 , KC_F12 , XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  RESET,
    XXXXXXX, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, DYNREC1, DYNSTP , DYNREC2, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, BASEWIN,
    _______, KC_CAPS, XXXXXXX, XXXXXXX, RGB_SAD, RGB_SAI, DYNGO1 , CLEARK , DYNGO2 , XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, BASEMAC,
    _______, XXXXXXX, RGB_HUD, RGB_HUI, RGB_VAD, RGB_VAI, KC_MUTE, KC_VOLU, XXXXXXX, KC_PSCR, KC_SLCK, KC_PAUS, XXXXXXX, XXXXXXX, _______,
    _______, _______, _______, RGB_TOG, RGB_RMOD,RGB_MOD, _______, KC_VOLD, _______, _______, _______, _______, _______, _______, _______
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
 * |        |        |        |        |        |        |        |        |        | toggle | 0      | 0      | .      | SPC    |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_NUM] = LAYOUT_ortho_5x15(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_EQL , KC_SLSH, KC_ASTR, KC_MINS, _______,
    _______, KC_GRV,S(KC_EQL), KC_LBRC, KC_RBRC, KC_EQL , _______, _______, _______, _______, KC_7   , KC_8   , KC_9   , KC_PLUS, _______,
    _______,S(KC_GRV),S(KC_MINS),S(KC_9),S(KC_0),KC_MINS, _______, _______, _______, _______, KC_4   , KC_5   , KC_6   , KC_PLUS, _______,
    _______,_______,KC_BSLS,S(KC_LBRC),S(KC_RBRC),S(KC_BSLS),_______,_______,_______,_______, KC_1   , KC_2   , KC_3   , KC_SPC , _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,TG(_NUM), KC_0   , KC_0   , KC_DOT , KC_SPC , _______
 ),

/* NAV
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        | MAIL   |MAILPRO |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |Prev win|Next win|Prev tab|Next tab| EXCEL  |        |        |        |  PgUp  |  Home  |   Up   |   End  |ScrollUp|        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |Ctrl/Win|  Shift |   Alt  |Cmd/Ctrl|  APP   |        | CLEARK |        |  PgDown|  Left  |  Down  |  Right |ScrollDn|        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | Ctrl Z | Crtl X | Ctrl C | Ctrl V | EXCEL  |        |        |        |Prev win|Next win|Prev Tab|Next tab|Ins     |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_NAV] = LAYOUT_ortho_5x15(
    _______, _______, MAIL   , MAILPRO, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, PREVTAB, NEXTTAB, PREVWIN, NEXTWIN, XCEL_D , _______, _______, _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_WH_U, _______,
    _______, N_GUI  , KC_LSFT, KC_LALT, N_CTRL , N_APP  , _______, CLEARK , _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_WH_D, _______,
    _______, N_UNDO , N_CUT  , N_COPY , N_PASTE, XCEL_V , _______, _______, _______, PREVWIN, NEXTWIN, PREVTAB, NEXTTAB, KC_INS , _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),
// same layer with one shot mods
  [_NAV_OS] = LAYOUT_ortho_5x15(
    _______, _______, MAIL   , MAILPRO, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, PREVTAB, NEXTTAB, PREVWIN, NEXTWIN, XCEL_D , _______, _______, _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_WH_U, _______,
    _______, OS_GUI , OS_SHFT, OS_ALT , OS_CTRL, N_APP , _______, CLEARK , _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_WH_D, _______,
    _______, N_UNDO , N_CUT  , N_COPY , N_PASTE, XCEL_V , _______, _______, _______, PREVWIN, NEXTWIN, PREVTAB, NEXTTAB, KC_INS , _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

/* FRENCH
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |  ² ³   |  ê Ê   |  €     |        |        |  ≈     |  ≠     |        |        |        |  ô Ô   |  °     |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |  â Â   |  é É   |  è È   |  © ®   |        |  «     |        |  »     |  ∞     |  ù Ù   |  œ Œ   |  ω Ω   |  π     |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |  à Â   |        |  ë Ë   |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |  ç Ç   |        |  ฿     |        |        |        |  ñ Ñ   |  µ     |  ≤     |  ≥     |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_FR] = LAYOUT_ortho_5x15(
    _______, _______,XP(14,15),XP(4,5), X(16)  , _______, _______,  X(39) ,  X(38) , _______, _______, _______,XP(22,23),  X(29) , _______,
    _______, XP(8,9), XP(0,1), XP(2,3),XP(18,19), _______,  X(36), _______,  X(37) ,  X(40) ,XP(24,25),XP(26,27),XP(20,21), X(28), _______,
    _______,XP(10,11), X(33) , XP(6,7), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______,XP(12,13),_______, X(17)  , _______, _______, _______,XP(30,31), X(32) , X(34)  ,  X(35) , _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_record_dynamic_macro(keycode, record)) {
    return false;
  }

  switch (keycode) {
    case NEXTWIN: // CMD+TAB or ALT+TAB
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          switch (biton32(default_layer_state)) {
          case _MAC:
            register_code(KC_LGUI);
            break;
          case _WIN:
            register_code(KC_LALT);
            break;
          }
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case PREVWIN: // CMD+SHIFT+TAB or ALT+SHIFT+TAB
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          switch (biton32(default_layer_state)) {
          case _MAC:
            register_code(KC_LGUI);
            break;
          case _WIN:
            register_code(KC_LALT);
            break;
          }
        }
        alt_tab_timer = timer_read();
        register_code16(S(KC_TAB));
      } else {
        unregister_code16(S(KC_TAB));
      }
      break;
    case NEXTTAB: // CTRL+TAB or CTRL+PGDOWN
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
        case _MAC:
          SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_TAB)SS_UP(X_LCTRL));
          break;
        case _WIN:
          SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_PGDOWN)SS_UP(X_LCTRL));
          break;
        }
      }
      break;
    case PREVTAB: // CTRL+SHIFT+TAB or CTRL+PGDUP
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
        case _MAC:
          SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_LSHIFT)SS_TAP(X_TAB)SS_UP(X_LSHIFT)SS_UP(X_LCTRL));
          break;
        case _WIN:
          SEND_STRING(SS_DOWN(X_LCTRL)SS_TAP(X_PGUP)SS_UP(X_LCTRL));
          break;
        }
      }
      break;
    case OS_CTRL:
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
        case _MAC:
          set_oneshot_mods(MOD_LGUI);
          break;
        case _WIN:
          set_oneshot_mods(MOD_LCTL);
          break;
        }
      }
      break;
    case N_CTRL:
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
        case _MAC:
          register_code(KC_LGUI);
          break;
        case _WIN:
          register_code(KC_LCTL);
          break;
        }
      } else {
        switch (biton32(default_layer_state)) {
        case _MAC:
          unregister_code(KC_LGUI);
          break;
        case _WIN:
          unregister_code(KC_LCTL);
          break;
        }
      }
      break;
    case OS_GUI:
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
        case _MAC:
          set_oneshot_mods(MOD_LCTL);
          break;
        case _WIN:
          set_oneshot_mods(MOD_LGUI);
          break;
        }
      }
      break;
    case N_GUI:
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
        case _MAC:
          register_code(KC_LCTL);
          break;
        case _WIN:
          register_code(KC_LGUI);
          break;
        }
      } else {
        switch (biton32(default_layer_state)) {
        case _MAC:
          unregister_code(KC_LCTL);
          break;
        case _WIN:
          unregister_code(KC_LGUI);
          break;
        }
      }
      break;
    case N_APP:
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
        case _MAC:
          tap_code(KC_BTN2);
          break;
        case _WIN:
          tap_code(KC_APP);
          break;
        }
      }
      break;
    case N_UNDO:
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
        case _MAC:
          SEND_STRING(SS_LGUI("z"));
          break;
        case _WIN:
          SEND_STRING(SS_LCTRL("z"));
          break;
        }
      }
      break;
    case N_CUT:
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
        case _MAC:
          SEND_STRING(SS_LGUI("x"));
          break;
        case _WIN:
          SEND_STRING(SS_LCTRL("x"));
          break;
        }
      }
      break;
    case N_COPY:
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
        case _MAC:
          SEND_STRING(SS_LGUI("c"));
          break;
        case _WIN:
          SEND_STRING(SS_LCTRL("c"));
          break;
        }
      }
      break;
    case N_PASTE:
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
        case _MAC:
          SEND_STRING(SS_LGUI("v"));
          break;
        case _WIN:
          SEND_STRING(SS_LCTRL("v"));
          break;
        }
      }
      break;
    case MAIL:
      if (record->event.pressed) {
        SEND_STRING(EMAIL_PERSO);
      }
      break;
    case MAILPRO:
      if (record->event.pressed) {
        SEND_STRING(EMAIL_PRO);
      }
      break;
    case XCEL_V:
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
        case _MAC:
          break;
        case _WIN:
          SEND_STRING(SS_LCTRL(SS_LALT("v")));
          _delay_ms(300);
          SEND_STRING("v" SS_TAP(X_ENTER));
          break;
        }
      }
      break;
    case XCEL_D:
      if (record->event.pressed) {
        switch (biton32(default_layer_state)) {
        case _MAC:
          break;
        case _WIN:
          // left ctrl+down right ctrl+shift+up ctrl+D
          SEND_STRING(SS_TAP(X_LEFT) SS_DOWN(X_LCTRL)SS_TAP(X_DOWN)SS_UP(X_LCTRL));
          _delay_ms(200);
          SEND_STRING(SS_TAP(X_RIGHT));
          _delay_ms(200);
          SEND_STRING(SS_DOWN(X_LCTRL)SS_DOWN(X_LSHIFT)SS_TAP(X_UP)SS_UP(X_LSHIFT)SS_UP(X_LCTRL));
          _delay_ms(200);
          SEND_STRING(SS_LCTRL("d"));
          break;
        }
      }
      break;
    case CLEARK:
      if (record->event.pressed) {
        clear_keyboard();
      }
      break;
    case BASEMAC:
      if (record->event.pressed) {
        default_layer_set(1UL<<_MAC);
        layer_move(_MAC);
        set_unicode_input_mode(UC_OSX);
      }
      return false;
      break;
    case BASEWIN:
      if (record->event.pressed) {
        default_layer_set(1UL<<_WIN);
        layer_move(_WIN);
        set_unicode_input_mode(UC_WINC);
      }
      return false;
      break;
  }
  return true;
}

// led control
uint32_t layer_state_set_user(uint32_t state) {
  switch (biton32(state)) {
  case _FN:
    rgblight_sethsv_noeeprom_pink();
    break;
  case _NUM:
    rgblight_sethsv_noeeprom_orange();
    break;
  case _NAV:
    rgblight_sethsv_noeeprom_springgreen();
    break;
  case _NAV_OS:
    rgblight_sethsv_noeeprom_cyan();
    break;
  case _FR:
    rgblight_sethsv_noeeprom_white();
    break;
  default: //  for any other layers, or the default layer
    switch (biton32(default_layer_state)) {
      case _MAC:
        rgblight_sethsv_noeeprom_red();
        break;
      case _WIN:
        rgblight_sethsv_noeeprom_blue();
        break;
    }
    break;
  }
  return state;
}

void matrix_init_user(void) {
    rgblight_enable();
    rgblight_sethsv(0,255,255);
    rgblight_mode(1);
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 600) {
      switch (biton32(default_layer_state)) {
      case _MAC:
        unregister_code(KC_LGUI);
        break;
      case _WIN:
        unregister_code(KC_LALT);
        break;
      }
      is_alt_tab_active = false;
    }
  }
}

void led_set_user(uint8_t usb_led) {

}

// tap dance
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  }
  if (state->count == 2) { return DOUBLE_TAP; }
  else { return TRIPLE_TAP; }
}

void mac_prevdesk_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      set_oneshot_mods(MOD_LCTL);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LCTL));
      break;
    case DOUBLE_TAP:
      SEND_STRING(SS_LCTRL(SS_TAP(X_LEFT)));
      break;
    case TRIPLE_TAP:
      SEND_STRING(SS_LCTRL(SS_TAP(X_LEFT)));
      _delay_ms(20);
      SEND_STRING(SS_LCTRL(SS_TAP(X_LEFT)));
  }
}

void mac_prevdesk_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
     clear_oneshot_mods();
     break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LCTL));
    default:
      break;
  }
}

void mac_nextdesk_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      set_oneshot_mods(MOD_LGUI);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RGUI));
      break;
    case DOUBLE_TAP:
      SEND_STRING(SS_LCTRL(SS_TAP(X_RIGHT)));
      break;
    case TRIPLE_TAP:
      SEND_STRING(SS_LCTRL(SS_TAP(X_RIGHT)));
      _delay_ms(20);
      SEND_STRING(SS_LCTRL(SS_TAP(X_RIGHT)));
  }
}

void mac_nextdesk_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
     clear_oneshot_mods();
     break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_RGUI));
    default:
      break;
  }
}

void win_prevdesk_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      set_oneshot_mods(MOD_LGUI);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_LGUI));
      break;
    case DOUBLE_TAP:
      SEND_STRING(SS_LCTRL(SS_LGUI(SS_TAP(X_LEFT))));
      break;
    case TRIPLE_TAP:
      SEND_STRING(SS_LCTRL(SS_LGUI(SS_TAP(X_LEFT))));
      _delay_ms(20);
      SEND_STRING(SS_LCTRL(SS_LGUI(SS_TAP(X_LEFT))));
  }
}

void win_prevdesk_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
     clear_oneshot_mods();
     break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_LGUI));
    default:
      break;
  }
}

void win_nextdesk_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      set_oneshot_mods(MOD_RCTL);
      break;
    case SINGLE_HOLD:
      register_mods(MOD_BIT(KC_RCTL));
      break;
    case DOUBLE_TAP:
      SEND_STRING(SS_LCTRL(SS_LGUI(SS_TAP(X_RIGHT))));
      break;
    case TRIPLE_TAP:
      SEND_STRING(SS_LCTRL(SS_LGUI(SS_TAP(X_RIGHT))));
      _delay_ms(20);
      SEND_STRING(SS_LCTRL(SS_LGUI(SS_TAP(X_RIGHT))));
  }
}

void win_nextdesk_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      clear_oneshot_mods();
      break;
    case SINGLE_HOLD:
      unregister_mods(MOD_BIT(KC_RCTL));
    default:
      break;
  }
}

void nav_on (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
       layer_on(_NAV);
  }
}

void nav_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state = cur_dance(state);
  switch (td_state) {
    case SINGLE_TAP:
      layer_off(_NAV);
      set_oneshot_layer(_NAV_OS, ONESHOT_START);
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      break;
    case SINGLE_HOLD:
      layer_on(_NAV);
      break;
    case DOUBLE_TAP:
      break;
    case TRIPLE_TAP:
      break;
  }
}

void nav_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_state) {
    case SINGLE_TAP:
      break;
    case SINGLE_HOLD:
      layer_off(_NAV);
    default:
      break;
  }
}

// define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
qk_tap_dance_action_t tap_dance_actions[] = {
  [MAC_PREVIOUS_DESKTOP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mac_prevdesk_finished, mac_prevdesk_reset),
  [MAC_NEXT_DESKTOP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mac_nextdesk_finished, mac_nextdesk_reset),
  [WIN_PREVIOUS_DESKTOP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, win_prevdesk_finished, win_prevdesk_reset),
  [WIN_NEXT_DESKTOP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, win_nextdesk_finished, win_nextdesk_reset),
  [NAV_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(nav_on, nav_finished, nav_reset, 150)
};
