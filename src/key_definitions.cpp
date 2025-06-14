#include "key_definitions.h"
#include "main.h" // For all KEY_XXX and custom keycode definitions (includes usb_keyboard.h)

// Define and initialize global LED color category variables
LedColor Layer    = CRGB(0x00FFFF);
LedColor Letter   = CRGB(0x8000FF);
LedColor Number   = CRGB(0x0000FF);
LedColor Numnav   = CRGB(0x0000FF);
LedColor Chara1   = CRGB(0xFF3300);
LedColor Chara2   = CRGB(0xFF3300);
LedColor Modifier = CRGB(0xFF0000);
LedColor Capslock = CRGB(0xFF0000);
LedColor Numlock  = CRGB(0xFFFF00);
LedColor Scrllock = CRGB(0xFFFF00);
LedColor FKeys1   = CRGB(0xFF2200);
LedColor FKeys1b  = CRGB(0xFF0000);
LedColor FKeys2   = CRGB(0x3300FF);
LedColor FKeys2b  = CRGB(0xFF00FF);
LedColor Special  = CRGB(0xFFFF00);
LedColor Nav      = CRGB(0x0000FF);
LedColor LedAdj   = CRGB(0xFFFFFF);
LedColor LEDoff   = CRGB(0x000000);
LedColor Macro    = CRGB(0xFF69B4);
LedColor Toggle1  = CRGB(0xFF0000);
LedColor Toggle2  = CRGB(0x8000FF);
LedColor VimNav   = CRGB(0x33FF33);

std::map<uint16_t, KeyFinalDefinition> G_KeyProperties;

void initKeyProperties() {
    // Layers & Special Layer Keys
    G_KeyProperties[LAYER_0]        = KeyFinalDefinition(LAYER_0, &Layer);
    G_KeyProperties[LAYER_1]        = KeyFinalDefinition(LAYER_1, &Layer);
    G_KeyProperties[LAYER_2]        = KeyFinalDefinition(LAYER_2, &Layer);
    G_KeyProperties[LAYER_3]        = KeyFinalDefinition(LAYER_3, &Layer);
    G_KeyProperties[LAYER_4]        = KeyFinalDefinition(LAYER_4, &Layer);
    G_KeyProperties[LAYER_1_2L]     = KeyFinalDefinition(LAYER_1_2L, &Special);
    G_KeyProperties[KEY_CAPS_SLASH] = KeyFinalDefinition(KEY_CAPS_SLASH, &Special);
    G_KeyProperties[KEY_CAPS_ESC]   = KeyFinalDefinition(KEY_CAPS_ESC, &Special);
    // Original _ALTL_ was {KEY_ALTL, &Special}; _LALT_ was {KEY_LEFT_ALT, &Modifier};
    G_KeyProperties[KEY_ALTL]       = KeyFinalDefinition(KEY_ALTL, &Special);
    G_KeyProperties[KEY_ALTR]       = KeyFinalDefinition(KEY_ALTR, &Special);

    G_KeyProperties[KEY_RELEASE]    = KeyFinalDefinition(KEY_RELEASE, &Special);
    G_KeyProperties[KEY_SET0]       = KeyFinalDefinition(KEY_SET0, &Special);
    G_KeyProperties[KEY_NULL]       = KeyFinalDefinition(KEY_NULL, &LEDoff);
    G_KeyProperties[KEY_REBOOT]     = KeyFinalDefinition(KEY_REBOOT, &Special);

    G_KeyProperties[MACRO_GMAIL]      = KeyFinalDefinition(MACRO_GMAIL, &Macro);
    G_KeyProperties[MACRO_HOTMAIL]    = KeyFinalDefinition(MACRO_HOTMAIL, &Macro);
    G_KeyProperties[MACRO_AIMARENA]   = KeyFinalDefinition(MACRO_AIMARENA, &Macro);
    G_KeyProperties[MACRO_LINEBREAK]  = KeyFinalDefinition(MACRO_LINEBREAK, &Macro);
    G_KeyProperties[CMNTSTRT]         = KeyFinalDefinition(CMNTSTRT, &Macro);
    G_KeyProperties[CMNTEND]          = KeyFinalDefinition(CMNTEND, &Macro);
    G_KeyProperties[LOOP_COUNT]       = KeyFinalDefinition(LOOP_COUNT, &Special);
    G_KeyProperties[MACRO_SQUAREROOT] = KeyFinalDefinition(MACRO_SQUAREROOT, &Macro);

    G_KeyProperties[KEY_ESC]          = KeyFinalDefinition(KEY_ESC, &Modifier);
    G_KeyProperties[KEY_F1]           = KeyFinalDefinition(KEY_F1, &FKeys1);
    G_KeyProperties[KEY_F2]           = KeyFinalDefinition(KEY_F2, &FKeys1);
    G_KeyProperties[KEY_F3]           = KeyFinalDefinition(KEY_F3, &FKeys1);
    G_KeyProperties[KEY_F4]           = KeyFinalDefinition(KEY_F4, &FKeys1);
    G_KeyProperties[KEY_F5]           = KeyFinalDefinition(KEY_F5, &FKeys1b);
    G_KeyProperties[KEY_F6]           = KeyFinalDefinition(KEY_F6, &FKeys1b);
    G_KeyProperties[KEY_F7]           = KeyFinalDefinition(KEY_F7, &FKeys1b);
    G_KeyProperties[KEY_F8]           = KeyFinalDefinition(KEY_F8, &FKeys1b);
    G_KeyProperties[KEY_F9]           = KeyFinalDefinition(KEY_F9, &FKeys1);
    G_KeyProperties[KEY_F10]          = KeyFinalDefinition(KEY_F10, &FKeys1);
    G_KeyProperties[KEY_F11]          = KeyFinalDefinition(KEY_F11, &FKeys1);
    G_KeyProperties[KEY_F12]          = KeyFinalDefinition(KEY_F12, &FKeys1);
    G_KeyProperties[KEY_F13]          = KeyFinalDefinition(KEY_F13, &FKeys2);
    G_KeyProperties[KEY_F14]          = KeyFinalDefinition(KEY_F14, &FKeys2);
    G_KeyProperties[KEY_F15]          = KeyFinalDefinition(KEY_F15, &FKeys2);
    G_KeyProperties[KEY_F16]          = KeyFinalDefinition(KEY_F16, &FKeys2);
    G_KeyProperties[KEY_F17]          = KeyFinalDefinition(KEY_F17, &FKeys2b);
    G_KeyProperties[KEY_F18]          = KeyFinalDefinition(KEY_F18, &FKeys2b);
    G_KeyProperties[KEY_F19]          = KeyFinalDefinition(KEY_F19, &FKeys2b);
    G_KeyProperties[KEY_F20]          = KeyFinalDefinition(KEY_F20, &FKeys2b);
    G_KeyProperties[KEY_F21]          = KeyFinalDefinition(KEY_F21, &FKeys2);
    G_KeyProperties[KEY_F22]          = KeyFinalDefinition(KEY_F22, &FKeys2);
    G_KeyProperties[KEY_F23]          = KeyFinalDefinition(KEY_F23, &FKeys2);
    G_KeyProperties[KEY_F24]          = KeyFinalDefinition(KEY_F24, &FKeys2);

    G_KeyProperties[KEYSF13]          = KeyFinalDefinition(KEYSF13, &FKeys2b);
    G_KeyProperties[KEYSF14]          = KeyFinalDefinition(KEYSF14, &FKeys2b);
    G_KeyProperties[KEYSF15]          = KeyFinalDefinition(KEYSF15, &FKeys2b);
    G_KeyProperties[KEYSF16]          = KeyFinalDefinition(KEYSF16, &FKeys2b);
    G_KeyProperties[KEYSF17]          = KeyFinalDefinition(KEYSF17, &FKeys2);
    G_KeyProperties[KEYSF18]          = KeyFinalDefinition(KEYSF18, &FKeys2);
    G_KeyProperties[KEYSF19]          = KeyFinalDefinition(KEYSF19, &FKeys2);
    G_KeyProperties[KEYSF20]          = KeyFinalDefinition(KEYSF20, &FKeys2);
    G_KeyProperties[KEYSF21]          = KeyFinalDefinition(KEYSF21, &FKeys2b);
    G_KeyProperties[KEYSF22]          = KeyFinalDefinition(KEYSF22, &FKeys2b);
    G_KeyProperties[KEYSF23]          = KeyFinalDefinition(KEYSF23, &FKeys2b);
    G_KeyProperties[KEYSF24]          = KeyFinalDefinition(KEYSF24, &FKeys2b);

    G_KeyProperties[KEY_PRINTSCREEN]  = KeyFinalDefinition(KEY_PRINTSCREEN, &Special);
    G_KeyProperties[KEY_SCROLL_LOCK]  = KeyFinalDefinition(KEY_SCROLL_LOCK, &Scrllock);
    G_KeyProperties[KEY_PAUSE]        = KeyFinalDefinition(KEY_PAUSE, &Special);

    G_KeyProperties[KEY_1]            = KeyFinalDefinition(KEY_1, &Number);
    G_KeyProperties[KEY_2]            = KeyFinalDefinition(KEY_2, &Number);
    G_KeyProperties[KEY_3]            = KeyFinalDefinition(KEY_3, &Number);
    G_KeyProperties[KEY_4]            = KeyFinalDefinition(KEY_4, &Number);
    G_KeyProperties[KEY_5]            = KeyFinalDefinition(KEY_5, &Number);
    G_KeyProperties[KEY_6]            = KeyFinalDefinition(KEY_6, &Number);
    G_KeyProperties[KEY_7]            = KeyFinalDefinition(KEY_7, &Number);
    G_KeyProperties[KEY_8]            = KeyFinalDefinition(KEY_8, &Number);
    G_KeyProperties[KEY_9]            = KeyFinalDefinition(KEY_9, &Number);
    G_KeyProperties[KEY_0]            = KeyFinalDefinition(KEY_0, &Number);
    G_KeyProperties[KEY_MINUS]        = KeyFinalDefinition(KEY_MINUS, &Chara1);
    G_KeyProperties[KEY_EQUAL]        = KeyFinalDefinition(KEY_EQUAL, &Chara1);
    G_KeyProperties[KEY_BACKSLASH]    = KeyFinalDefinition(KEY_BACKSLASH, &Chara1);
    G_KeyProperties[KEY_BACKSPACE]    = KeyFinalDefinition(KEY_BACKSPACE, &Letter);

    G_KeyProperties[KEY_INSERT]       = KeyFinalDefinition(KEY_INSERT, &Chara1);
    G_KeyProperties[KEY_DELETE]       = KeyFinalDefinition(KEY_DELETE, &Modifier);
    G_KeyProperties[KEY_HOME]         = KeyFinalDefinition(KEY_HOME, &Modifier);
    G_KeyProperties[KEY_END]          = KeyFinalDefinition(KEY_END, &Modifier);
    G_KeyProperties[KEY_PAGE_UP]      = KeyFinalDefinition(KEY_PAGE_UP, &Modifier);
    G_KeyProperties[KEY_PAGE_DOWN]    = KeyFinalDefinition(KEY_PAGE_DOWN, &Modifier);
    G_KeyProperties[KEY_UP_ARROW]     = KeyFinalDefinition(KEY_UP_ARROW, &Nav);
    G_KeyProperties[KEY_DOWN_ARROW]   = KeyFinalDefinition(KEY_DOWN_ARROW, &Nav);
    G_KeyProperties[KEY_LEFT_ARROW]   = KeyFinalDefinition(KEY_LEFT_ARROW, &Nav);
    G_KeyProperties[KEY_RIGHT_ARROW]  = KeyFinalDefinition(KEY_RIGHT_ARROW, &Nav);

    G_KeyProperties[KEY_NUM_LOCK]     = KeyFinalDefinition(KEY_NUM_LOCK, &Numlock);
    G_KeyProperties[KEYPAD_SLASH]     = KeyFinalDefinition(KEYPAD_SLASH, &Chara2);
    G_KeyProperties[KEYPAD_ASTERIX]   = KeyFinalDefinition(KEYPAD_ASTERIX, &Chara2);
    G_KeyProperties[KEYPAD_PLUS]      = KeyFinalDefinition(KEYPAD_PLUS, &Chara2);
    G_KeyProperties[KEYPAD_MINUS]     = KeyFinalDefinition(KEYPAD_MINUS, &Chara2);
    G_KeyProperties[KEYPAD_ENTER]     = KeyFinalDefinition(KEYPAD_ENTER, &Letter);
    G_KeyProperties[KEYPAD_0]         = KeyFinalDefinition(KEYPAD_0, &Number);
    G_KeyProperties[KEYPAD_1]         = KeyFinalDefinition(KEYPAD_1, &Number);
    G_KeyProperties[KEYPAD_2]         = KeyFinalDefinition(KEYPAD_2, &Numnav);
    G_KeyProperties[KEYPAD_3]         = KeyFinalDefinition(KEYPAD_3, &Number);
    G_KeyProperties[KEYPAD_4]         = KeyFinalDefinition(KEYPAD_4, &Numnav);
    G_KeyProperties[KEYPAD_5]         = KeyFinalDefinition(KEYPAD_5, &Number);
    G_KeyProperties[KEYPAD_6]         = KeyFinalDefinition(KEYPAD_6, &Numnav);
    G_KeyProperties[KEYPAD_7]         = KeyFinalDefinition(KEYPAD_7, &Number);
    G_KeyProperties[KEYPAD_8]         = KeyFinalDefinition(KEYPAD_8, &Numnav);
    G_KeyProperties[KEYPAD_9]         = KeyFinalDefinition(KEYPAD_9, &Number);
    G_KeyProperties[KEYPAD_PERIOD]    = KeyFinalDefinition(KEYPAD_PERIOD, &Chara2);

    G_KeyProperties[KEY_TAB]          = KeyFinalDefinition(KEY_TAB, &Modifier);
    G_KeyProperties[KEY_TILDE]        = KeyFinalDefinition(KEY_TILDE, &Chara1);
    G_KeyProperties[KEY_CAPS_LOCK]    = KeyFinalDefinition(KEY_CAPS_LOCK, &Capslock);
    G_KeyProperties[KEY_LEFT_SHIFT]   = KeyFinalDefinition(KEY_LEFT_SHIFT, &Modifier);
    G_KeyProperties[KEY_LEFT_CTRL]    = KeyFinalDefinition(KEY_LEFT_CTRL, &Modifier);
    G_KeyProperties[KEY_LEFT_GUI]     = KeyFinalDefinition(KEY_LEFT_GUI, &Modifier);
    G_KeyProperties[KEY_LEFT_ALT]     = KeyFinalDefinition(KEY_LEFT_ALT, &Modifier);
    G_KeyProperties[KEY_SPACE]        = KeyFinalDefinition(KEY_SPACE, &Letter);

    G_KeyProperties[KEY_Q]            = KeyFinalDefinition(KEY_Q, &Letter);
    G_KeyProperties[KEY_W]            = KeyFinalDefinition(KEY_W, &Letter);
    G_KeyProperties[KEY_E]            = KeyFinalDefinition(KEY_E, &Letter);
    G_KeyProperties[KEY_R]            = KeyFinalDefinition(KEY_R, &Letter);
    G_KeyProperties[KEY_T]            = KeyFinalDefinition(KEY_T, &Letter);
    G_KeyProperties[KEY_Y]            = KeyFinalDefinition(KEY_Y, &Letter);
    G_KeyProperties[KEY_U]            = KeyFinalDefinition(KEY_U, &Letter);
    G_KeyProperties[KEY_I]            = KeyFinalDefinition(KEY_I, &Letter);
    G_KeyProperties[KEY_O]            = KeyFinalDefinition(KEY_O, &Letter);
    G_KeyProperties[KEY_P]            = KeyFinalDefinition(KEY_P, &Letter);
    G_KeyProperties[KEY_A]            = KeyFinalDefinition(KEY_A, &Letter);
    G_KeyProperties[KEY_S]            = KeyFinalDefinition(KEY_S, &Letter);
    G_KeyProperties[KEY_D]            = KeyFinalDefinition(KEY_D, &Letter);
    G_KeyProperties[KEY_F]            = KeyFinalDefinition(KEY_F, &Letter);
    G_KeyProperties[KEY_G]            = KeyFinalDefinition(KEY_G, &Letter);
    G_KeyProperties[KEY_H]            = KeyFinalDefinition(KEY_H, &Letter);
    G_KeyProperties[KEY_J]            = KeyFinalDefinition(KEY_J, &Letter);
    G_KeyProperties[KEY_K]            = KeyFinalDefinition(KEY_K, &Letter);
    G_KeyProperties[KEY_L]            = KeyFinalDefinition(KEY_L, &Letter);
    G_KeyProperties[KEY_Z]            = KeyFinalDefinition(KEY_Z, &Letter);
    G_KeyProperties[KEY_X]            = KeyFinalDefinition(KEY_X, &Letter);
    G_KeyProperties[KEY_C]            = KeyFinalDefinition(KEY_C, &Letter);
    G_KeyProperties[KEY_V]            = KeyFinalDefinition(KEY_V, &Letter);
    G_KeyProperties[KEY_B]            = KeyFinalDefinition(KEY_B, &Letter);
    G_KeyProperties[KEY_N]            = KeyFinalDefinition(KEY_N, &Letter);
    G_KeyProperties[KEY_M]            = KeyFinalDefinition(KEY_M, &Letter);

    G_KeyProperties[KEY_LEFT_BRACE]   = KeyFinalDefinition(KEY_LEFT_BRACE, &Chara1);
    G_KeyProperties[KEY_RIGHT_BRACE]  = KeyFinalDefinition(KEY_RIGHT_BRACE, &Chara1);
    G_KeyProperties[KEY_SEMICOLON]    = KeyFinalDefinition(KEY_SEMICOLON, &Chara1);
    G_KeyProperties[KEY_QUOTE]        = KeyFinalDefinition(KEY_QUOTE, &Chara1);
    G_KeyProperties[KEY_ENTER]        = KeyFinalDefinition(KEY_ENTER, &Letter);
    G_KeyProperties[KEY_COMMA]        = KeyFinalDefinition(KEY_COMMA, &Chara1);
    G_KeyProperties[KEY_PERIOD]       = KeyFinalDefinition(KEY_PERIOD, &Chara1);
    G_KeyProperties[KEY_SLASH]        = KeyFinalDefinition(KEY_SLASH, &Chara1);
    G_KeyProperties[KEY_RIGHT_SHIFT]  = KeyFinalDefinition(KEY_RIGHT_SHIFT, &Modifier);
    G_KeyProperties[KEY_RIGHT_CTRL]   = KeyFinalDefinition(KEY_RIGHT_CTRL, &Modifier);
    G_KeyProperties[KEY_RIGHT_GUI]    = KeyFinalDefinition(KEY_RIGHT_GUI, &Modifier);
    G_KeyProperties[KEY_RIGHT_ALT]    = KeyFinalDefinition(KEY_RIGHT_ALT, &Modifier);

    G_KeyProperties[KEY_MEDIA_MUTE]         = KeyFinalDefinition(KEY_MEDIA_MUTE, &Modifier);
    G_KeyProperties[KEY_MEDIA_PREV_TRACK]   = KeyFinalDefinition(KEY_MEDIA_PREV_TRACK, &Special);
    G_KeyProperties[KEY_MEDIA_NEXT_TRACK]   = KeyFinalDefinition(KEY_MEDIA_NEXT_TRACK, &Special);
    G_KeyProperties[KEY_MEDIA_REWIND]       = KeyFinalDefinition(KEY_MEDIA_REWIND, &Special);
    G_KeyProperties[KEY_MEDIA_FAST_FORWARD] = KeyFinalDefinition(KEY_MEDIA_FAST_FORWARD, &Special);
    G_KeyProperties[KEY_MEDIA_RECORD]       = KeyFinalDefinition(KEY_MEDIA_RECORD, &Special);
    G_KeyProperties[KEY_MEDIA_PLAY_PAUSE]   = KeyFinalDefinition(KEY_MEDIA_PLAY_PAUSE, &Special);
    G_KeyProperties[KEY_MEDIA_VOLUME_INC]   = KeyFinalDefinition(KEY_MEDIA_VOLUME_INC, &Modifier);
    G_KeyProperties[KEY_MEDIA_VOLUME_DEC]   = KeyFinalDefinition(KEY_MEDIA_VOLUME_DEC, &Modifier);

    G_KeyProperties[EXCLMAMATION]     = KeyFinalDefinition(EXCLMAMATION, &Chara2);
    G_KeyProperties[KEY_AT]           = KeyFinalDefinition(KEY_AT, &Chara2);
    G_KeyProperties[KEY_HASH]         = KeyFinalDefinition(KEY_HASH, &Chara2);
    G_KeyProperties[KEY_DOLLAR]       = KeyFinalDefinition(KEY_DOLLAR, &Chara2);
    G_KeyProperties[KEY_PERCENT]      = KeyFinalDefinition(KEY_PERCENT, &Chara2);
    G_KeyProperties[KEY_CARAT]        = KeyFinalDefinition(KEY_CARAT, &Chara2);
    G_KeyProperties[AMPERSAND]        = KeyFinalDefinition(AMPERSAND, &Chara2);
    G_KeyProperties[KEY_ASTERISK]     = KeyFinalDefinition(KEY_ASTERISK, &Chara2);
    G_KeyProperties[L_PARENTHESIS]    = KeyFinalDefinition(L_PARENTHESIS, &Chara2);
    G_KeyProperties[R_PARENTHESIS]    = KeyFinalDefinition(R_PARENTHESIS, &Chara2);
    G_KeyProperties[UNDERSCORE]       = KeyFinalDefinition(UNDERSCORE, &Chara2);
    G_KeyProperties[KEY_PIPE]         = KeyFinalDefinition(KEY_PIPE, &Chara2);
    G_KeyProperties[LEFT_CHEVRON]     = KeyFinalDefinition(LEFT_CHEVRON, &Chara2);
    G_KeyProperties[RIGHT_CHEVRON]    = KeyFinalDefinition(RIGHT_CHEVRON, &Chara2);
    G_KeyProperties[QUESTION_MARK]    = KeyFinalDefinition(QUESTION_MARK, &Chara2);
    G_KeyProperties[KEY_COLON]        = KeyFinalDefinition(KEY_COLON, &Chara2);
    G_KeyProperties[KEY_DBLQUOTE]     = KeyFinalDefinition(KEY_DBLQUOTE, &Chara2);
    G_KeyProperties[CURL_L_BRACE]     = KeyFinalDefinition(CURL_L_BRACE, &Chara2);
    G_KeyProperties[CURL_R_BRACE]     = KeyFinalDefinition(CURL_R_BRACE, &Chara2);
    G_KeyProperties[SHIFT_TILDE]      = KeyFinalDefinition(SHIFT_TILDE, &Chara2);
    G_KeyProperties[KEY_PLUS]         = KeyFinalDefinition(KEY_PLUS, &Chara2);

    G_KeyProperties[E_MACRON]         = KeyFinalDefinition(E_MACRON, &Letter);
    G_KeyProperties[GREAT_EQUAL]      = KeyFinalDefinition(GREAT_EQUAL, &Chara2);
    G_KeyProperties[LESS_EQUAL]       = KeyFinalDefinition(LESS_EQUAL, &Chara2);
    G_KeyProperties[NOT_EQUAL]        = KeyFinalDefinition(NOT_EQUAL, &Chara2);
    G_KeyProperties[PLUS_MINUS]       = KeyFinalDefinition(PLUS_MINUS, &Chara2);
    G_KeyProperties[KEY_DEGREES]      = KeyFinalDefinition(KEY_DEGREES, &Chara2);

    G_KeyProperties[MOUSE_LCLICK]     = KeyFinalDefinition(MOUSE_LCLICK, &Special);
    G_KeyProperties[MOUSE_RCLICK]     = KeyFinalDefinition(MOUSE_RCLICK, &Special);
    G_KeyProperties[TRILL_MODE1]      = KeyFinalDefinition(TRILL_MODE1, &Special);
    G_KeyProperties[TRILL_MODE2]      = KeyFinalDefinition(TRILL_MODE2, &Special);
    G_KeyProperties[TRILL_MODE3]      = KeyFinalDefinition(TRILL_MODE3, &Special);
    G_KeyProperties[LEDS_BR0]         = KeyFinalDefinition(LEDS_BR0, &LedAdj);
    G_KeyProperties[LEDS_BR1]         = KeyFinalDefinition(LEDS_BR1, &LedAdj);
    G_KeyProperties[LEDS_BR2]         = KeyFinalDefinition(LEDS_BR2, &LedAdj);
    G_KeyProperties[LEDS_BR3]         = KeyFinalDefinition(LEDS_BR3, &LedAdj);
    G_KeyProperties[LEDS_BR4]         = KeyFinalDefinition(LEDS_BR4, &LedAdj);
    G_KeyProperties[LEDS_BR5]         = KeyFinalDefinition(LEDS_BR5, &LedAdj);
    G_KeyProperties[LEDS_BR6]         = KeyFinalDefinition(LEDS_BR6, &LedAdj);
    G_KeyProperties[LEDS_BR7]         = KeyFinalDefinition(LEDS_BR7, &LedAdj);
    G_KeyProperties[LEDS_BR8]         = KeyFinalDefinition(LEDS_BR8, &LedAdj);
    G_KeyProperties[LEDS_BR9]         = KeyFinalDefinition(LEDS_BR9, &LedAdj);
    G_KeyProperties[LEDS_BR10]        = KeyFinalDefinition(LEDS_BR10, &LedAdj);
    G_KeyProperties[LEDS_INC]         = KeyFinalDefinition(LEDS_INC, &LedAdj);
    G_KeyProperties[LEDS_DEC]         = KeyFinalDefinition(LEDS_DEC, &LedAdj);

    G_KeyProperties[KEY_ALT_TAB]      = KeyFinalDefinition(KEY_ALT_TAB, &Special);
}
