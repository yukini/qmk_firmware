// Copyright 2023 contact@vwolf.be
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define KC_I1 MT(MOD_LGUI, KC_LNG1)
#define KC_I2 MT(MOD_RGUI, KC_LNG2)
#define SPC_L2 LT(2, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ Bspc│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
     * │ Ctrl │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│MO1│
     * └─────┬──┴┬──┴──┬┴───┴───┴───┴───┴───┴───┴──┬┴───┴┬───┬─┴───┘
     *       │Alt│ GUI │                           │ GUI │Alt│
     *       └───┴─────┴───────────────────────────┴─────┴───┘
     */
    [0] = LAYOUT_60_hhkb(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(1),
                          MO(2),   KC_LGUI,                   KC_SPC,                             KC_RGUI, KC_RALT
    ),

    [1] = LAYOUT_60_hhkb(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
        KC_CAPS, RGB_TOG, KC_UP,   _______, _______, KC_BRID, KC_BRIU, _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP,   _______, _______,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,          _______,
        _______,          KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, _______, KC_END,  KC_PGDN, KC_DOWN, _______, _______,
                          _______, _______,                   _______,                            _______, _______
    ),

    [2] = LAYOUT_60_hhkb(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_INS,  KC_DEL,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______,
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
        _______,          KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, KC_HOME, KC_END,  KC_PGDN, KC_DOWN, _______, _______,
                          _______, _______,                   _______,                            _______, _______
    )
};

static bool space_pressed = false;
static bool l_gui_pressed = false;
static bool r_shift_pressed = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SPC:
            if (record->event.pressed) {
                layer_on(2);
                space_pressed = true;
            } else {
                layer_off(2);
                if (space_pressed) {
                    register_code(KC_SPC);
                    unregister_code(KC_SPC);
                }
                space_pressed = false;
            }
            return false;
            break;
        case KC_LGUI:
            if (record->event.pressed) {
                register_code(keycode);
                l_gui_pressed = true;
            } else {
                unregister_code(keycode);
                if (l_gui_pressed) {
                    register_code(KC_LNG2);
                    unregister_code(KC_LNG2);
                }
                l_gui_pressed = false;
            }
            return false;
            break;
        case KC_RSFT:
            if (record->event.pressed) {
                register_code(keycode);
                r_shift_pressed = true;
            } else {
                unregister_code(keycode);
                if (r_shift_pressed) {
                    register_code(KC_LNG1);
                    unregister_code(KC_LNG1);
                }
                r_shift_pressed = false;
            }
            return false;
            break;
        default:
            if (record->event.pressed) {
                // spaceを離す前に他キーを押下しても、spaceのキーコードを送信する
                // vimのleader-keyにspaceを使っており、spaceキーが離れる前に他キーを押しがちなので設定
                if (space_pressed) {
                    register_code(KC_SPC);
                    unregister_code(KC_SPC);
                    space_pressed = false;
                }
                l_gui_pressed = false;
                r_shift_pressed = false;
            }
            break;
    }
    return true;
}
