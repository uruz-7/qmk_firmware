/*  -*-  eval: (turn-on-orgtbl); -*-
 * default HHKB Layout
 qmk c2json keyboards/hhkb/ansi/keymaps/uruz7z/keymap.c > keyboards/hhkb/ansi/keymaps/uruz7z/key.json
 qmk compile -kb hhkb/ansi/32u4 -km uruz7z
 */
#include QMK_KEYBOARD_H

#define BASE 0

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* BASE Level: Default Layer
    |-------+---+---+---+---+---+---+---+---+---+---+-----+-----+-------+-----|
    | ESC   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | -   | =   | `     |Backs|
    |-------+---+---+---+---+---+---+---+---+---+---+-----+-----+-------+-----|
    | Tab   | Q | W | E | R | T | Y | U | I | O | P | [   | ]   | \     |
    |-------+---+---+---+---+---+---+---+---+---+---+-----+-----+-------+
    | Ctrl  | A | S | D | F | G | H | J | K | L | ; | '   | Ent |
    |-------+---+---+---+---+---+---+---+---+---+---+-----+-----+
    | Shift | Z | X | C | V | B | N | M | , | . | / | Del | Mo3 |
    |-------+---+---+---+---+---+---+---+---+---+---+-----+-----+
        |------+------+-----------------------+------+------|
        | LGUI | Mo1  | ***** Space Mo1 ***** | RAlt | Mo2  |
        |------+------+-----------------------+------+------|
  */
  [BASE] = LAYOUT( //  default layer
    KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_GRV, KC_BSPC,
    KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_DEL,  MO(3),
                   KC_LGUI, MO(1), LT(1,KC_SPC), KC_RALT, MO(2)
  ),

  /* Layer 1
    |------+-----+-----+-----+-----+-----+-----+----+----+----+-----+-----+------+-----+-----|
    | `    | F1  | F2  | F3  | F4  | F5  | F6  | F7 | F8 | F9 | F10 | F11 | F12  | App | Del |
    |------+-----+-----+-----+-----+-----+-----+----+----+----+-----+-----+------+-----+-----|
    | Ins  | Tab | VoD | Up  | VoU | Slk | Pus | 7  | 8  | 9  | +   | -   | Ln2  | Ln1 |
    |------+-----+-----+-----+-----+-----+-----+----+----+----+-----+-----+------+-----+
    | Caps | Mut | Lft | Dwn | Rgt | Hom | PgU | 4  | 5  | 6  | Bsp | Bsp | PEnt |
    |------+-----+-----+-----+-----+-----+-----+----+----+----+-----+-----+------+
    | Pscr | Stp | Prv | Ply | Nxt | End | PgD | 1  | 2  | 3  | *   | /   | Tg3  |
    |------+-----+-----+-----+-----+-----+-----+----+----+----+-----+-----+------+
                |------+------+----------------------+------+------+
                | Num  | Mo1  |          0           | .    | Mo2  |
                |------+------+----------------------+------+------+
  */
  [1] = LAYOUT(
    KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7, KC_F8, KC_F9, KC_F10,  KC_F11,  KC_F12,  KC_APP, KC_DEL,
    KC_INS,  KC_TAB,  KC_VOLD, KC_UP,   KC_VOLU, KC_SCRL, KC_PAUS, KC_P7, KC_P8, KC_P9, KC_PPLS, KC_PMNS, KC_LNG2, KC_LNG1,
    KC_CAPS, KC_MUTE, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME, KC_PGUP, KC_P4, KC_P5, KC_P6, KC_BSPC, KC_BSPC, KC_PENT,
    KC_PSCR, KC_MSTP, KC_MPRV, KC_MPLY, KC_MNXT, KC_END , KC_PGDN, KC_P1, KC_P2, KC_P3, KC_PAST, KC_PSLS, TG(3),
                      KC_NUM,  KC_TRNS, KC_P0,   KC_PDOT, MO(2)
  ),

  /* Layer 2
    |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------+------|
    | RCtl | Hom | Bak | Fwd | Stp | Ref | Sch | Fav | MyC | Mai | Hlp |     |     | Mail | Calc |
    |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------+------|
    | `    | 1   | 2   | 3   | 4   | 5   | 6   | 7   | 8   | 9   | 0   | \   | =   | Bspc |
    |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------+
    | Caps | "   | :   | +   | _   | [   | ]   | -   | =   | ;   | '   | Ent | Ent |
    |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
    | !    | @   | #   | $   | %   | ^   | &   | *   | (   | )   | |   | +   | Tg3 |
    |------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
                |------+------+----------------------+------+------+
                | ~    | Mo1  | BriD                 | BriU | Mo2  |
                |------+------+----------------------+------+------+
  */
  [2] = LAYOUT(
    KC_RCTL, KC_WHOM, KC_WBAK, KC_WFWD, KC_WSTP, KC_WREF, KC_WSCH, KC_WFAV, KC_MYCM, KC_MAIL, KC_HELP, KC_NO,   KC_NO,  KC_MAIL, KC_CALC,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, KC_EQL, KC_BSPC,
    KC_CAPS, KC_DQUO, KC_COLN, KC_PLUS, KC_UNDS, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT, KC_ENT,  KC_ENT,
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, KC_PLUS, TG(3),
                      KC_TILD, MO(1),   KC_BRID, KC_BRIU, MO(2)
  ),

  /* Layer 3
    |-------+-----+-----+-----+-----+----+----+----+-----+-----+-----+--------+-----+-------+-----|
    | Sleep | F13 | F14 | F15 | F16 | F17| F18| F19| F20 | F21 | F22 | F23    | F24 |       |     |
    |-------+-----+-----+-----+-----+----+----+----+-----+-----+-----+--------+-----+-------+-----|
    |       |     | M2  | MsU | M1  | M4 | M5 | M3 | WhU |     |     |        |     |       |
    |-------+-----+-----+-----+-----+----+----+----+-----+-----+-----+--------+-----+-------+
    |       |     | MsL | MsD | MsR |    |    | WhL| WhD | WhR |     |        |     |
    |-------+-----+-----+-----+-----+----+----+----+-----+-----+-----+--------+-----+
    |       | Ac0 | Ac1 | Ac2 |     |    |    |    |     |     |     | RShift | Mo3 |
    |-------+-----+-----+-----+-----+----+----+----+-----+-----+-----+--------+-----+
                |------+------+----------------------+------+------+
                | LAlt | Tg1  |                      | RGui | Tg2  |
                |------+------+----------------------+------+------+
  */
  [3] = LAYOUT(
    KC_SLEP, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22, KC_F23,  KC_F24, KC_NO, KC_NO,
    KC_NO,   KC_NO,   MS_BTN2, MS_UP,   MS_BTN1, MS_BTN4, MS_BTN5, MS_BTN3, MS_WHLU, KC_NO,   KC_NO,  KC_NO,   KC_NO,  KC_NO,
    KC_NO,   KC_NO,   MS_LEFT, MS_DOWN, MS_RGHT, KC_NO,   KC_NO,   MS_WHLL, MS_WHLD, MS_WHLR, KC_NO,  KC_NO,   KC_NO,
    KC_NO,   MS_ACL0, MS_ACL1, MS_ACL2, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_RSFT, MO(3),
                      KC_LALT, TG(1),   KC_NO,   KC_RGUI, TG(2)
  )
};
