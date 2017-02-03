// Netable differences vs. the default firmware for the ErgoDox EZ:
// 1. The Cmd key is now on the right side, making Cmd+Space easier.
// 2. The media keys work on OSX (But not on Windows).
#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

typedef enum onoff_t {OFF, ON} onoff;

#define caps_led_on  ergodox_right_led_2_on
#define caps_led_off ergodox_right_led_2_off


// layers
enum {
  BASE = 0,
  COLEMAK,
  SYMB,
  MDIA
};

// actions
enum {
  AC_GUI_QUOTE = 0,
  AC_GUI_BSPC,
  AC_GUI_TAB,
  AC_GUI_ESC,
  AC_ALT_SPACE,
  AC_ALT_ENTER,
  AC_SYMB_TAP,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |    ~   |   1  |   2  |   3  |   4  |   5  |  ACD |           |      |   6  |   7  |   8  |   9  |   0  | CAPS   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |   Tab  |   Q  |   W  |   F  |   P  |   B  | CLMK |           | Del  |   J  |   L  |   U  |   Y  |   ;  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |Esc/Ctrl|   A  |   R  |   S  |   T  |   G  |------|           |------|   M  |   N  |   E  |   I  |   O  | Ctrl/' |
 * |--------+------+------+------+------+------| Hyper|           | Meh  |------+------+------+------+------+--------|
 * | LShf/( |   Z  |   X  |   C  |   D  |   V  |      |           |      |   K  |   H  |   ,  |   .  |  /   | RShf/) |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  ~L1 |  -L2 |  Ctrl| Alt/[| Cmd/]|                                       | Cmd/-| Alt/=| Ctrl |  -L2 | ~L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                      ,--------------.       ,---------------.
 *                                      |  Down |  Up  |       | Left |  Right |
 *                              ,-------|-------|------|       |------+--------+---------.
 *                              | ~SYMB | ~MEDIA| Home |       | PgUp | ~MEDIA |  ~SYMB  |
 *                              |  Spc  |  BSpc |------|       |------|  BSpc  |  Enter  |
 *                              |       |       | Cmd  |       | PgDn |        |         |
 *                              `----------------------'       `-------------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_GRV,       KC_1,      KC_2,   KC_3,   KC_4,   KC_5,   LALT(LCTL(KC_DEL)),
        KC_TAB,        M(KC_Q),   M(KC_W),M(KC_E),M(KC_R),M(KC_T),TG(COLEMAK),
        CTL_T(KC_ESC), M(KC_A),   M(KC_S),M(KC_D),M(KC_F),M(KC_G),
        KC_LSPO,       M(KC_NUBS), M(KC_Z),M(KC_X),M(KC_C),M(KC_V),ALL_T(KC_NO),
        MO(SYMB),      MO(MDIA), KC_LCTL,ALT_T(KC_LBRC),GUI_T(KC_RBRC),
                                                              KC_DOWN, KC_UP,
                                                                       KC_HOME,
                                                     LT(SYMB, KC_SPC),  LT(MDIA, KC_BSPC),KC_LGUI,
        // right hand
             KC_NO,       KC_6,   KC_7,   KC_8,   KC_9,   KC_0,        M(KC_CAPS),
             KC_DEL,      M(KC_Y),M(KC_U),M(KC_I),M(KC_O),M(KC_P),      KC_BSLS,
                          M(KC_H),M(KC_J),M(KC_K),M(KC_L),M(KC_SCLN),   CTL_T(KC_QUOT),
             MEH_T(KC_NO),M(KC_N),M(KC_M),KC_COMM,KC_DOT, KC_SLSH,      KC_RSPC,
                                  GUI_T(KC_MINS),ALT_T(KC_EQL),KC_RCTL,MO(MDIA),    MO(SYMB),
             KC_LEFT,   KC_RIGHT,
             KC_PGUP,
             KC_PGDN,   LT(MDIA, KC_BSPC), LT(SYMB, KC_ENTER)
    ),
/* Keymap COLEMAK: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   Q  |   W  |   F  |   P  |   B  | BASE |           |      |   J  |   L  |   U  |   Y  |   ;  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   A  |   R  |   S  |   T  |   G  |------|           |------|   M  |   N  |   E  |   I  |   O  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   Z  |   X  |   C  |   D  |   V  |      |           |      |   K  |   H  |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                      ,--------------.       ,---------------.
 *                                      |       |      |       |      |        |
 *                              ,-------|-------|------|       |------+--------+---------.
 *                              |       |       |      |       |      |        |         |
 *                              |       |       |------|       |------|        |         |
 *                              |       |       |      |       |      |        |         |
 *                              `----------------------'       `-------------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[COLEMAK] = KEYMAP(  // colemak layout
        // left hand
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, M(KC_Q), M(KC_W), M(KC_F), M(KC_P), M(KC_B), KC_TRNS,
        KC_TRNS, M(KC_A), M(KC_R), M(KC_S), M(KC_T), M(KC_G),
        KC_TRNS, M(KC_Z), M(KC_X), M(KC_C), M(KC_D), M(KC_V), KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                                              KC_TRNS, KC_TRNS,
                                                                       KC_TRNS,
                                                     KC_TRNS, KC_TRNS, KC_TRNS,
        // right hand
             KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS, M(KC_J), M(KC_L), M(KC_U), M(KC_Y), M(KC_SCLN), KC_TRNS,
                      M(KC_M), M(KC_N), M(KC_E), M(KC_I), M(KC_O), KC_TRNS,
             KC_TRNS, M(KC_K), M(KC_H), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
             KC_TRNS, KC_TRNS,
             KC_TRNS,
             KC_TRNS, KC_TRNS, KC_TRNS
    ),
/* Keymap 1:
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  | F11  |           |  F12 |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   0  |   .  |   =  |   -  |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F11,
       KC_TRNS,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
       KC_TRNS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
       KC_TRNS,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_F12,  KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
       KC_TRNS, KC_UP,   KC_7,   KC_8,    KC_9,    KC_ASTR, KC_TRNS,
                KC_DOWN, KC_4,   KC_5,    KC_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_1,   KC_2,    KC_3,    KC_BSLS, KC_TRNS,
                         KC_0,   KC_DOT,  KC_EQL,  KC_MINS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      | Lclk | MsUp | Rclk |      |      |           |      |      | Home |  Up  |  End | PgUp |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      | Left | Down | Right| PgDn |  Play  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      | Prev | Next |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |VolDn |VolUp | Mute |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |Brwser|
 *                                 |      |      |------|       |------|      |Back  |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,  KC_TRNS, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_TRNS,
                 KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_PGDN, KC_MPLY,
       KC_TRNS,  KC_TRNS, KC_TRNS, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
                          KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_WBAK
),
};

const uint16_t PROGMEM fn_actions[] = {
    [AC_GUI_QUOTE] = ACTION_MODS_TAP_KEY(MOD_LGUI, KC_QUOT),    // quote when tapped, GUI when hold
    [AC_GUI_TAB] = ACTION_MODS_TAP_KEY(MOD_LGUI, KC_TAB),
    [AC_GUI_ESC] = ACTION_MODS_TAP_KEY(MOD_LGUI, KC_ESC),
    [AC_GUI_BSPC]  = ACTION_MODS_TAP_KEY(MOD_LGUI, KC_BSPC),
    [AC_ALT_SPACE] = ACTION_MODS_TAP_KEY(MOD_LALT, KC_SPC),
    [AC_ALT_ENTER] = ACTION_MODS_TAP_KEY(MOD_LALT, KC_ENT),
    [AC_SYMB_TAP] = ACTION_LAYER_TAP_TOGGLE(SYMB)               // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    static onoff caps_state = OFF;
    switch(id) {
    case KC_CAPS:
        if (record->event.pressed) {
            // Toggle caps state;
            if (caps_state == OFF) {
                // Turn it on then!
                caps_led_on();
                caps_state = ON;
            } else {
                caps_led_off();
                caps_state = OFF;
            }
        }
        break;
    default:
        if (record->event.pressed) {
            bool shifted = false;
            if (caps_state == ON && get_mods() == 0) {
                register_code(KC_LSFT);
                shifted = true;
            }
            register_code(id);
            if(shifted) {
                unregister_code(KC_LSFT);
            }
        } else {
            unregister_code(id);
        }
        break;
    }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_board_led_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};
