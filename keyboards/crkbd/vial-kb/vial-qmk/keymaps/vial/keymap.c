#include QMK_KEYBOARD_H

// Define custom keycodes
enum custom_keycodes {
    RM_LBRC = QK_KB_0,
    RM_RBRC,
    RM_PGUP,
    RM_PGDN,
    TD_MKEY,
};

enum {
    TD_MKEY_ACTION = 0,
};

// Variables to handle the macros
bool is_rm_lbrc_active = false;
bool is_rm_rbrc_active = false;
bool is_rm_pgup_active = false;
bool is_rm_pgdn_active = false;

uint16_t macro_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RM_LBRC:
            if (record->event.pressed) {
                is_rm_lbrc_active = true;
                macro_timer = timer_read();
            } else {
                is_rm_lbrc_active = false;
            }
            return false; // Skip all further processing of this key
        case RM_RBRC:
            if (record->event.pressed) {
                is_rm_rbrc_active = true;
                macro_timer = timer_read();
            } else {
                is_rm_rbrc_active = false;
            }
            return false; // Skip all further processing of this key
        case RM_PGUP:
            if (record->event.pressed) {
                is_rm_pgup_active = true;
                macro_timer = timer_read();
            } else {
                is_rm_pgup_active = false;
            }
            return false; // Skip all further processing of this key
        case RM_PGDN:
            if (record->event.pressed) {
                is_rm_pgdn_active = true;
                macro_timer = timer_read();
            } else {
                is_rm_pgdn_active = false;
            }
            return false; // Skip all further processing of this key
    }
    return true; // Process all other keycodes normally
}

void matrix_scan_user(void) {
    // Check if any macro is active and the timer has elapsed
    if (timer_elapsed(macro_timer) > 250) {
        if (is_rm_lbrc_active) {
            tap_code(KC_LBRC);
        } else if (is_rm_rbrc_active) {
            tap_code(KC_RBRC);
        } else if (is_rm_pgup_active) {
            tap_code(KC_PGUP);
        } else if (is_rm_pgdn_active) {
            tap_code(KC_PGDN);
        }
    }
}

void dance_finished(tap_dance_state_t *state, void *user_data) {
    switch (state->count) {
        case 1:
            tap_code16(KC_K); // K
            break;
        case 2:
            tap_code16(LALT(KC_LSFT)); // ALT+SHIFT+K
            break;
        case 3:
            tap_code16(LCTL(KC_LSFT)); // CTRL+SHIFT+ESC
            break;
    }
}

void dance_reset(tap_dance_state_t *state, void *user_data) {
    // Reset any persistent state if needed
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_MKEY_ACTION] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_finished, dance_reset),
};
enum combo_events {
    COMBO_Q_TILDE,
    COMBO_QW_1,
    COMBO_WE_2,
    COMBO_ER_3,
    COMBO_RT_4,
    COMBO_TAB_A_SHIFT_TAB,
    COMBO_ZX_CTRL_Z,
    COMBO_XC_CTRL_X,
    COMBO_CV_CTRL_C,
    COMBO_VB_CTRL_V,
    COMBO_YU_LBRACKET,
    COMBO_UI_RBRACKET,
    COMBO_IO_LPAREN,
    COMBO_OP_RPAREN,
    COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM combo_q_tilde[] = {KC_Q, KC_PLUS, COMBO_END};
const uint16_t PROGMEM combo_qw_1[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_we_2[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_er_3[] = {KC_E, KC_R, COMBO_END};
const uint16_t PROGMEM combo_rt_4[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM combo_tab_a_shift_tab[] = {KC_TAB, KC_A, COMBO_END};
const uint16_t PROGMEM combo_zx_ctrl_z[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM combo_xc_ctrl_x[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_cv_ctrl_c[] = {KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM combo_vb_ctrl_v[] = {KC_V, KC_B, COMBO_END};
const uint16_t PROGMEM combo_yu_lbracket[] = {KC_Y, KC_U, COMBO_END};
const uint16_t PROGMEM combo_ui_rbracket[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM combo_io_lparen[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM combo_op_rparen[] = {KC_O, KC_P, COMBO_END};

combo_t key_combos[] = {
    [COMBO_Q_TILDE] = COMBO_ACTION(combo_q_tilde),
    [COMBO_QW_1] = COMBO_ACTION(combo_qw_1),
    [COMBO_WE_2] = COMBO_ACTION(combo_we_2),
    [COMBO_ER_3] = COMBO_ACTION(combo_er_3),
    [COMBO_RT_4] = COMBO_ACTION(combo_rt_4),
    [COMBO_TAB_A_SHIFT_TAB] = COMBO_ACTION(combo_tab_a_shift_tab),
    [COMBO_ZX_CTRL_Z] = COMBO_ACTION(combo_zx_ctrl_z),
    [COMBO_XC_CTRL_X] = COMBO_ACTION(combo_xc_ctrl_x),
    [COMBO_CV_CTRL_C] = COMBO_ACTION(combo_cv_ctrl_c),
    [COMBO_VB_CTRL_V] = COMBO_ACTION(combo_vb_ctrl_v),
    [COMBO_YU_LBRACKET] = COMBO_ACTION(combo_yu_lbracket),
    [COMBO_UI_RBRACKET] = COMBO_ACTION(combo_ui_rbracket),
    [COMBO_IO_LPAREN] = COMBO_ACTION(combo_io_lparen),
    [COMBO_OP_RPAREN] = COMBO_ACTION(combo_op_rparen)
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case COMBO_Q_TILDE:
            if (pressed) {
                tap_code16(KC_GRV); // ` (Grave accent, usually for ~)
            }
            break;
        case COMBO_QW_1:
            if (pressed) {
                tap_code(KC_1);
            }
            break;
        case COMBO_WE_2:
            if (pressed) {
                tap_code(KC_2);
            }
            break;
        case COMBO_ER_3:
            if (pressed) {
                tap_code(KC_3);
            }
            break;
        case COMBO_RT_4:
            if (pressed) {
                tap_code(KC_4);
            }
            break;
        case COMBO_TAB_A_SHIFT_TAB:
            if (pressed) {
                tap_code16(S(KC_TAB));
            }
            break;
        case COMBO_ZX_CTRL_Z:
            if (pressed) {
                tap_code16(C(KC_Z));
            }
            break;
        case COMBO_XC_CTRL_X:
            if (pressed) {
                tap_code16(C(KC_X));
            }
            break;
        case COMBO_CV_CTRL_C:
            if (pressed) {
                tap_code16(C(KC_C));
            }
            break;
        case COMBO_VB_CTRL_V:
            if (pressed) {
                tap_code16(C(KC_V));
            }
            break;
        case COMBO_YU_LBRACKET:
            if (pressed) {
                tap_code(KC_LBRC);
            }
            break;
        case COMBO_UI_RBRACKET:
            if (pressed) {
                tap_code(KC_RBRC);
            }
            break;
        case COMBO_IO_LPAREN:
            if (pressed) {
                tap_code16(S(KC_9)); // (
            }
            break;
        case COMBO_OP_RPAREN:
            if (pressed) {
                tap_code16(S(KC_0)); // )
            }
            break;
    }
}

#ifdef LAYOUT_split_3x6_3_ex2
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
    KC_GRV,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, RM_LBRC,    RM_PGUP,    KC_Y,    KC_U,    KC_I,   KC_O,   KC_P,   KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
    LT(1,KC_TAB),   KC_A,   KC_S,    KC_D,  KC_F, KC_G, LT(2, RM_RBRC),    TD_MKEY,   KC_H,    KC_J,  KC_K,  KC_L, KC_SCLN,  LT(4,KC_ENT),
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
        SC_LSPO,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,   KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                            KC_LCTL, KC_LALT, KC_SPC,  LT(3,KC_SPC), KC_LSFT, KC_F24
                                      //`--------------------------'  `--------------------------'
),

[1] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
        KC_ESC,  KC_Y,    KC_U,    KC_I,   KC_O,   KC_P,  KC_TRNS,     KC_LCBR, KC_RCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_TRNS,   KC_H,    KC_J,   KC_K,   KC_L, KC_SCLN,  KC_TRNS,     KC_TRNS, KC_PLUS,  KC_DLR, KC_PERC, KC_CIRC, KC_DQUO, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
        KC_TRNS,   KC_N,    KC_M,  KC_COMM, KC_DOT, KC_SLSH,                       KC_PIPE, KC_EXLM,  KC_AT, KC_HASH, KC_TILD, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                            KC_TRNS, KC_TRNS, KC_TRNS,    KC_UNDS, KC_LPRN, KC_RPRN
                                      //`--------------------------'  `--------------------------'
),

[2] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
    KC_ESC, KC_P1,  KC_P2,   KC_P3,   KC_P4,   KC_P5,  KC_TRNS,    KC_TRNS, KC_LBRC,   KC_7,    KC_8,    KC_9,  KC_RBRC, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS, KC_P6,  KC_P7,   KC_P8,   KC_P9,   KC_P0,  KC_TRNS,    KC_TRNS,  KC_EQL,   KC_4,    KC_5,    KC_6,  KC_QUOT, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS,KC_NUM,KC_PSLS,  KC_PAST,  KC_PMNS,  KC_PPLS,                    KC_BSLS,   KC_1,    KC_2,    KC_3,   KC_GRV, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS, KC_TRNS, KC_TRNS,    KC_MINS,   KC_0,  KC_DOT
                                      //`--------------------------'  `--------------------------'
),

[3] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
        KC_TRNS, KC_PGUP, KC_PGDN, KC_UP, C(KC_A), C(KC_BSPC),KC_TRNS,   KC_TRNS, KC_WH_U, KC_WH_L, KC_MS_U, KC_WH_R, KC_BTN4, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_TRNS,    KC_TRNS, KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_BTN5, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
        KC_TRNS, C(KC_Z), C(KC_X), C(KC_C), C(KC_V), C(KC_Y),                   KC_BTN1, KC_BTN2, KC_BTN2,  DM_REC1, DM_PLY1, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                        KC_TRNS, KC_TRNS, KC_TRNS,    KC_BTN3, KC_BTN2, KC_BTN1
                                      //`--------------------------'  `--------------------------'
),

[4] = LAYOUT_split_3x6_3_ex2(
//,--------------------------------------------------------------.  ,--------------------------------------------------------------.
    KC_TRNS, RGB_HUI, RGB_SAI, KC_VOLU, RGB_VAI, RGB_TOG, KC_TRNS,    KC_TRNS, KC_PSCR,  KC_F7,   KC_F8,  KC_F9,  KC_F12, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS, RGB_SPI, KC_MPRV, KC_VOLD, KC_MNXT, QK_BOOT, KC_TRNS,    KC_TRNS, KC_SCRL,  KC_F4,   KC_F5,  KC_F6,   KC_F11, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
    KC_TRNS, DM_REC2, DM_PLY2, KC_MRWD, KC_MFFD, DB_TOGG,                      KC_PAUS,  KC_F1,   KC_F2,   KC_F3,  KC_F10, KC_TRNS,
//|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                        KC_MUTE, KC_MSTP, KC_MPLY,     KC_TRNS, KC_TRNS, KC_TRNS
                                    //`--------------------------'  `--------------------------'
),
};

#else
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, TL_LOWR,  KC_SPC,     KC_ENT, TL_UPPR, KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
    [1] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
    [2] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
    [3] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
    [4] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
};
#endif
