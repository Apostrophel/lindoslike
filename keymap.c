/* Adapted from the Default Keychron suplementary files (Copyright 2023 @ Keychron, https://www.keychron.com)
 *
 * Keymap based on my split keyboard combos and tweeks (Lindos).
 * Author: sjurbarndon@proton.me
 */

#include QMK_KEYBOARD_H

enum layers{
  GAMING, // This is the old "MAC_BASE", and can be toggled with the physical back button. .
  WIN_BASE,
  GAME_FN1,
  WIN_FN1,
  FN2,
};


// Custom macros for shorter keycode mapping.

// This is the home row mods:
#define G_A LGUI_T(KC_A)    // Gui key when held, A when pressed
#define G_C LGUI_T(SYM_COLN) // Gui key when held, : when pressed
#define A_S LALT_T(KC_S)    // ALT key when held, S when pressed
#define A_L RALT_T(KC_L)    // ALT key when held, L when pressed
#define S_D LSFT_T(KC_D)    // SHIFT key when held, D when pressed
#define S_K RSFT_T(KC_K)    // SHIFT key when held, K when pressed
#define C_F LCTL_T(KC_F)    // Control key when held, K when pressed
#define C_J RCTL_T(KC_J)    // Control key when held, J when pressed

// This is the symbols:
#define SYM_LPRN S(KC_8)       // (  this is ok
#define SYM_RPRN S(KC_9)       // )  this is ok
#define SYM_LBRC RALT(KC_8)    // [  should be alt gr + KC_8
#define SYM_RBRC RALT(KC_9)    // ]
#define SYM_LCBR RALT(KC_7)    // {
#define SYM_RCBR RALT(KC_0)    // }
#define SYM_BSLS KC_EQL        //  backslash = \, this is ok
#define SYM_SCLN KC_SCLN       // ;
#define SYM_COLN S(KC_SCLN)    // :
#define SYM_QUOT KC_BSLS   // '
#define SYM_DQUO S(KC_2)   // "
#define SYM_COMM KC_COMM    // ,
#define SYM_LT   S(KC_COMM) // <
#define SYM_DOT  KC_DOT     // .
#define SYM_GT   S(KC_DOT)  // >
#define SYM_SLSH S(KC_7)    // This is: /, this is ok


// Customo combo keys for symbols on  top of the normal keyboard.
const uint16_t PROGMEM open_parentasis[] = {A_S, C_F, COMBO_END};
const uint16_t PROGMEM close_parentasis[] = {C_J, A_L, COMBO_END};
const uint16_t PROGMEM open_bracket[] = {KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM close_bracket[] = {KC_U, KC_O, COMBO_END};
const uint16_t PROGMEM open_curl_bracket[] = {KC_X, KC_V, COMBO_END};
const uint16_t PROGMEM close_curl_bracket[] = {KC_M, KC_DOT, COMBO_END};
const uint16_t PROGMEM double_quote[] = {S_D, C_F, COMBO_END};
const uint16_t PROGMEM single_quote[] = {C_J, S_K, COMBO_END};
const uint16_t PROGMEM forward_slash[] = {G_A, C_F, COMBO_END};
const uint16_t PROGMEM back_slash[] = {C_J, KC_SCLN, COMBO_END};

combo_t key_combos[] = {
    COMBO(open_parentasis, SYM_LPRN),
    COMBO(close_parentasis, SYM_RPRN),
    COMBO(open_bracket, SYM_LBRC),
    COMBO(close_bracket, SYM_RBRC),
    COMBO(open_curl_bracket, SYM_LCBR),
    COMBO(close_curl_bracket,SYM_RCBR),
    COMBO(double_quote, SYM_DQUO),
    COMBO(single_quote, SYM_QUOT),
    COMBO(back_slash, SYM_BSLS),
    COMBO(forward_slash, SYM_SLSH)
};

// Only allow layers on the main layer "Windows":
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    // Only allow combos on layer 1
    if (IS_LAYER_ON_STATE(default_layer_state, WIN_BASE)) {
        return true;
    }
    return false;
}

bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
    return true; // all combos must be tapped
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [GAMING] = LAYOUT_iso_68( // Accessible by the physical "Mac"-togggle button  on the back.
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,     KC_EQL,              KC_BSPC, KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,     KC_RBRC,                      KC_DEL,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,     KC_NUHS,             KC_ENT,  KC_HOME,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,     KC_RSFT,             KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(GAME_FN1), MO(FN2),  KC_LEFT,  KC_DOWN, KC_RGHT),

    [WIN_BASE] = LAYOUT_iso_68( //Keeping the name "Win" since its accessible by the "Win"-toggle button on thte back.
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,     KC_EQL,            KC_BSPC, KC_MUTE,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,     KC_RBRC,                    KC_DEL,
        KC_CAPS,  G_A,      A_S,      S_D,      C_F,      KC_G,     KC_H,     C_J,      S_K,      A_L,      KC_SCLN,  KC_QUOT,     KC_NUHS,           KC_ENT,  KC_HOME,
        KC_LSFT,  KC_NUBS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,              KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(WIN_FN1), MO(FN2), KC_LEFT,  KC_DOWN, KC_RGHT),

    [GAME_FN1] = LAYOUT_iso_68(
        _______,  _______,  _______,  _______,  _______,  RGB_VAD,  RGB_VAI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                     _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
        _______,  _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______, _______),

    [WIN_FN1] = LAYOUT_iso_68(
        KC_GRV,   KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  _______,  KC_GRV,   _______,           RGB_TOG,
        _______,  BT_HST1,  BT_HST2,  BT_HST3,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                     _______,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
        _______,  _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  NK_TOGG,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______, _______),

    [FN2] = LAYOUT_iso_68(
        KC_TILD,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,           _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                     _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,           _______,
        _______,  _______,  _______,  _______,  _______,  _______,  BAT_LVL,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
        _______,  _______,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______, _______),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [GAMING] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [GAME_FN1]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [WIN_FN1]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [FN2]      = {ENCODER_CCW_CW(_______, _______) }
};
#endif // ENCODER_MAP_ENABLE
