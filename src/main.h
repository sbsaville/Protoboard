#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <usb_keyboard.h>
#include <usb_mouse.h>

class CRGB;

void L_check();

const uint8_t rowsCount = 6;
const uint8_t rows[rowsCount] = {39, 38, 37, 36, 35, 34};

const uint8_t columnsCount = 14;                                                           
const uint8_t columns[columnsCount] = {17, 16, 15, 14, 13, 24, 25, 26, 27, 28, 29, 30, 31, 32};
                                    // c0  c1  c2  c3  c4  c5  c6  c7  c8  c9  10  11  12  13 
                                                                        
struct Key {
  uint8_t row;
  uint8_t column;
  boolean pressed;
};

// Forward declaration of LayoutKey
struct LayoutKey;

/**
 * Structure to track physical key states across layer changes.
 * This is the core of the generic key preservation system that allows
 * keys to maintain their original function when held during layer changes.
 */
struct PhysicalKeyState {
  bool isPressed;
  uint16_t activeCode;
  LayoutKey* activeKey;
};

// Global matrix to track physical key states across layer changes
extern PhysicalKeyState physicalKeyStates[rowsCount][columnsCount];

void initKeyTrackingMatrix();

const uint16_t LAYER_0                       = 1   | 0xA000;
const uint16_t LAYER_1                       = 2   | 0xA000;
const uint16_t LAYER_2                       = 3   | 0xA000;
const uint16_t LAYER_3                       = 4   | 0xA000;
const uint16_t LAYER_4                       = 5   | 0xA000;

// maximum of 16 layers since even that is pushing it for teensy 3.6 EEPROM

const uint16_t KEY_CAPS_SLASH                = 17  | 0xA000;
const uint16_t KEY_CAPS_ESC                  = 18  | 0xA000;
const uint16_t KEY_ALTL                      = 20  | 0xA000;
const uint16_t KEY_ALTR                      = 21  | 0xA000;

// I arbitrarily decided that alt+[KEY] should descend from 99 while shift+[KEY] should ascend from 100
const uint16_t KEY_ALT_TAB                   = 99  | 0xA000;
const uint16_t EXCLMAMATION                  = 100 | 0xA000; // !
const uint16_t KEY_AT                        = 101 | 0xA000; // @
const uint16_t KEY_HASH                      = 102 | 0xA000; // #
const uint16_t KEY_DOLLAR                    = 103 | 0xA000; // $
const uint16_t KEY_PERCENT                   = 104 | 0xA000; // %
const uint16_t KEY_CARAT                     = 105 | 0xA000; // ^
const uint16_t AMPERSAND                     = 106 | 0xA000; // &
const uint16_t KEY_ASTERISK                  = 107 | 0xA000; // *
const uint16_t L_PARENTHESIS                 = 108 | 0xA000; // (
const uint16_t R_PARENTHESIS                 = 109 | 0xA000; // )
const uint16_t UNDERSCORE                    = 110 | 0xA000; // _
const uint16_t KEY_PIPE                      = 111 | 0xA000; // |
const uint16_t LEFT_CHEVRON                  = 112 | 0xA000; // <
const uint16_t RIGHT_CHEVRON                 = 113 | 0xA000; // >
const uint16_t QUESTION_MARK                 = 114 | 0xA000; // ?
const uint16_t KEY_COLON                     = 115 | 0xA000; // :
const uint16_t KEY_DBLQUOTE                  = 116 | 0xA000; // "
const uint16_t CURL_L_BRACE                  = 117 | 0xA000; // {
const uint16_t CURL_R_BRACE                  = 118 | 0xA000; // }
const uint16_t SHIFT_TILDE                   = 119 | 0xA000; // ~
const uint16_t KEY_PLUS                      = 120 | 0xA000; // +
const uint16_t KEYSF13                       = 121 | 0xA000;
const uint16_t KEYSF14                       = 122 | 0xA000;
const uint16_t KEYSF15                       = 123 | 0xA000;
const uint16_t KEYSF16                       = 124 | 0xA000;
const uint16_t KEYSF17                       = 125 | 0xA000;
const uint16_t KEYSF18                       = 126 | 0xA000;
const uint16_t KEYSF19                       = 127 | 0xA000;
const uint16_t KEYSF20                       = 128 | 0xA000;
const uint16_t KEYSF21                       = 129 | 0xA000;
const uint16_t KEYSF22                       = 130 | 0xA000;
const uint16_t KEYSF23                       = 131 | 0xA000;
const uint16_t KEYSF24                       = 132 | 0xA000;

//                            alt-codes
const uint16_t E_MACRON                      = 200 | 0xA000; // ē
const uint16_t GREAT_EQUAL                   = 201 | 0xA000; // ≥
const uint16_t LESS_EQUAL                    = 202 | 0xA000; // ≤
const uint16_t NOT_EQUAL                     = 203 | 0xA000; // ≠
const uint16_t PLUS_MINUS                    = 204 | 0xA000; // ±
const uint16_t KEY_DEGREES                   = 205 | 0xA000; // °

//                            macros
const uint16_t MACRO_GMAIL                   = 400 | 0xA000;
const uint16_t MACRO_HOTMAIL                 = 401 | 0xA000;
const uint16_t MACRO_AIMARENA                = 402 | 0xA000;
const uint16_t MACRO_LINEBREAK               = 403 | 0xA000;
const uint16_t CMNTSTRT                      = 404 | 0xA000;
const uint16_t CMNTEND                       = 405 | 0xA000;
const uint16_t LOOP_COUNT                    = 406 | 0xA000;
const uint16_t MACRO_SQUAREROOT              = 407 | 0xA000;

//                          administrative
const uint16_t KEY_NULL                      = 600 | 0xA000;
const uint16_t KEY_RELEASE                   = 601 | 0xA000;
const uint16_t KEY_SET0                      = 602 | 0xA000;
const uint16_t KEY_REBOOT                    = 603 | 0xA000;

//                          non-keyboard things
const uint16_t MOUSE_LCLICK                  = 900 | 0xA000;
const uint16_t MOUSE_RCLICK                  = 901 | 0xA000;
const uint16_t TRILL_MODE1                   = 902 | 0xA000;
const uint16_t TRILL_MODE2                   = 903 | 0xA000;
const uint16_t TRILL_MODE3                   = 904 | 0xA000;
const uint16_t LEDS_BR0                      = 905 | 0xA000;
const uint16_t LEDS_BR1                      = 906 | 0xA000;
const uint16_t LEDS_BR2                      = 907 | 0xA000;
const uint16_t LEDS_BR3                      = 908 | 0xA000;
const uint16_t LEDS_BR4                      = 909 | 0xA000;
const uint16_t LEDS_BR5                      = 910 | 0xA000;
const uint16_t LEDS_BR6                      = 911 | 0xA000;
const uint16_t LEDS_BR7                      = 912 | 0xA000;
const uint16_t LEDS_BR8                      = 913 | 0xA000;
const uint16_t LEDS_BR9                      = 914 | 0xA000;
const uint16_t LEDS_BR10                     = 915 | 0xA000;
const uint16_t LEDS_INC                      = 916 | 0xA000;
const uint16_t LEDS_DEC                      = 917 | 0xA000;


#endif
