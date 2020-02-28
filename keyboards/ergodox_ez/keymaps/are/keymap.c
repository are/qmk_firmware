#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"

// LAYERS
#define BASE 0 // default layer
#define SYMB 1 // symbols
#define CUST 2 // custom

// CUSTOM KEYCODES
enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE,
  XC_VRSN,
};

// ALIASES
#define CMD_SPC LCMD_T(KC_SPACE)
#define CTL_BSP LCTL_T(KC_BSPACE)
#define CTL_F2  LCTL(KC_F2)
#define SFT_ENT LSFT_T(KC_ENTER)
#define XC_LOCK LCMD(LCTL(KC_Q))
#define LM_SYMB MO(SYMB) // momentary layer to SYMB
#define LM_FUNC MO(CUST) // momentary layer to FUNC

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// default layer
[BASE] = LAYOUT_ergodox(
  KC_F1  , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , XXXXXXX,
  KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , XXXXXXX,
  XXXXXXX, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,
  KC_RALT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LM_FUNC,
                                      CTL_F2 , KC_ESC ,
                                               XXXXXXX,
                             CMD_SPC, CTL_BSP, KC_HYPR,

  XXXXXXX, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC__MUTE,
  XXXXXXX, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_TAB ,
           KC_H   , KC_J   , KC_K   , KC_L   , KC_QUOT, KC_PGUP,
  KC_DEL , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_PGDN,
                    KC_LEFT, KC_UP  , KC_DOWN, KC_RGHT, XXXXXXX,
  XXXXXXX, XXXXXXX,
  XXXXXXX,
  KC_MEH , LM_SYMB, SFT_ENT
),
// symbols
[SYMB] = LAYOUT_ergodox(
  XXXXXXX, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, KC_EQL , XXXXXXX, KC_TILD, XXXXXXX,
  XXXXXXX, KC_AT  , KC_ASTR, KC_DLR , KC_MINS, KC_PLUS,
  XXXXXXX, XXXXXXX, XXXXXXX, KC_CIRC, KC_UNDS, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                      XXXXXXX, XXXXXXX,
                                               XXXXXXX,
                             XXXXXXX, XXXXXXX, XXXXXXX,

  XXXXXXX,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX,
  XXXXXXX,  XXXXXXX, KC_COLN, KC_LPRN, KC_RPRN, KC_PERC, XXXXXXX,
            KC_HASH, KC_SCLN, KC_LCBR, KC_RCBR, KC_GRV , XXXXXXX,
  XXXXXXX,  KC_PIPE, KC_AMPR, KC_LABK, KC_RABK, KC_BSLS, XXXXXXX,
                     KC_HOME, KC_LBRC, KC_RBRC, KC_END , XXXXXXX,
  XXXXXXX, XXXXXXX,
  XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX
),
// functional
[CUST] = LAYOUT_ergodox(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XC_VRSN, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                      XXXXXXX, XXXXXXX,
                                               XXXXXXX,
                             XXXXXXX, XXXXXXX, XXXXXXX,

  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XC_LOCK, XXXXXXX, XXXXXXX,
  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX,
  XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case XC_VRSN:
      if (record->event.pressed) {
        SEND_STRING("1/28-02-2020/Are");
      }
      return false; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}

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
    case BASE:
      ergodox_right_led_1_on();
      break;
    case SYMB:
      ergodox_right_led_2_on();
      break;
    case CUST:
      ergodox_right_led_3_on();
      break;
    default:
      break;
  }
};
