#ifdef __INTELLISENSE__
// Provide dummy definitions for IntelliSense to prevent errors
// These should not impact the actual build process
#define KEY_SPEC(ConstName, NumericId, ColorCategoryPtr) static const int ConstName = NumericId;
#define KEY_SPEC_STD(UsbKeyCodeName, ColorCategoryPtr) static const int UsbKeyCodeName = 0;
#endif

// This file is intended to be included multiple times with different macro definitions.
// It defines the list of all key specifications for the X-Macro system.
// It should not have its own include guards.

// Format: KEY_SPEC(ConstName, NumericId, ColorCategoryPtr) for custom keys (NumericId will be ORed with 0xA000 by main.h)
// Format: KEY_SPEC_STD(UsbKeyCodeName, ColorCategoryPtr) for standard keys (already defined in usb_keyboard.h)

// Custom Layer Keys and Special Keys (Numeric ID is pre-0xA000)
KEY_SPEC(LAYER_0, 1, &Layer);
KEY_SPEC(LAYER_1, 2, &Layer);
KEY_SPEC(LAYER_2, 3, &Layer);
KEY_SPEC(LAYER_3, 4, &Layer);
KEY_SPEC(LAYER_4, 5, &Layer);
KEY_SPEC(KEY_CAPS_SLASH, 17, &Special);
KEY_SPEC(KEY_CAPS_ESC, 18, &Special);
KEY_SPEC(LAYER_1_2L, 19, &Special);
KEY_SPEC(KEY_ALTL, 20, &Special);     // Custom key for Alt-L toggle behavior
KEY_SPEC(KEY_ALTR, 21, &Special);     // Custom key for Alt-R toggle behavior
KEY_SPEC(KEY_ALT_TAB, 99, &Special);  // Custom key for Alt-Tab macro like behavior

// Custom Shifted Characters / Symbols (Numeric ID is pre-0xA000)
KEY_SPEC(EXCLMAMATION, 100, &Chara2);
KEY_SPEC(KEY_AT, 101, &Chara2);
KEY_SPEC(KEY_HASH, 102, &Chara2);
KEY_SPEC(KEY_DOLLAR, 103, &Chara2);
KEY_SPEC(KEY_PERCENT, 104, &Chara2);
KEY_SPEC(KEY_CARAT, 105, &Chara2);
KEY_SPEC(AMPERSAND, 106, &Chara2);
KEY_SPEC(KEY_ASTERISK, 107, &Chara2);
KEY_SPEC(L_PARENTHESIS, 108, &Chara2);
KEY_SPEC(R_PARENTHESIS, 109, &Chara2);
KEY_SPEC(UNDERSCORE, 110, &Chara2);
KEY_SPEC(KEY_PIPE, 111, &Chara2);
KEY_SPEC(LEFT_CHEVRON, 112, &Chara2);
KEY_SPEC(RIGHT_CHEVRON, 113, &Chara2);
KEY_SPEC(QUESTION_MARK, 114, &Chara2);
KEY_SPEC(KEY_COLON, 115, &Chara2);
KEY_SPEC(KEY_DBLQUOTE, 116, &Chara2);
KEY_SPEC(CURL_L_BRACE, 117, &Chara2);
KEY_SPEC(CURL_R_BRACE, 118, &Chara2);
KEY_SPEC(SHIFT_TILDE, 119, &Chara2);
KEY_SPEC(KEY_PLUS, 120, &Chara2);

// Custom Shifted F-Keys (Numeric ID is pre-0xA000)
KEY_SPEC(KEYSF13, 121, &FKeys2b);
KEY_SPEC(KEYSF14, 122, &FKeys2b);
KEY_SPEC(KEYSF15, 123, &FKeys2b);
KEY_SPEC(KEYSF16, 124, &FKeys2b);
KEY_SPEC(KEYSF17, 125, &FKeys2);
KEY_SPEC(KEYSF18, 126, &FKeys2);
KEY_SPEC(KEYSF19, 127, &FKeys2);
KEY_SPEC(KEYSF20, 128, &FKeys2);
KEY_SPEC(KEYSF21, 129, &FKeys2b);
KEY_SPEC(KEYSF22, 130, &FKeys2b);
KEY_SPEC(KEYSF23, 131, &FKeys2b);
KEY_SPEC(KEYSF24, 132, &FKeys2b);

// Custom Alt-Codes (Numeric ID is pre-0xA000)
KEY_SPEC(E_MACRON, 200, &Letter);
KEY_SPEC(GREAT_EQUAL, 201, &Chara2);
KEY_SPEC(LESS_EQUAL, 202, &Chara2);
KEY_SPEC(NOT_EQUAL, 203, &Chara2);
KEY_SPEC(PLUS_MINUS, 204, &Chara2);
KEY_SPEC(KEY_DEGREES, 205, &Chara2);

// Custom Macros (Numeric ID is pre-0xA000)
KEY_SPEC(MACRO_GMAIL, 400, &Macro);
KEY_SPEC(MACRO_HOTMAIL, 401, &Macro);
KEY_SPEC(MACRO_AIMARENA, 402, &Macro);
KEY_SPEC(MACRO_LINEBREAK, 403, &Macro);
KEY_SPEC(CMNTSTRT, 404, &Macro);
KEY_SPEC(CMNTEND, 405, &Macro);
KEY_SPEC(LOOP_COUNT, 406, &Special);
KEY_SPEC(MACRO_SQUAREROOT, 407, &Macro);

// Custom Administrative Keys (Numeric ID is pre-0xA000)
KEY_SPEC(KEY_NULL, 600, &LEDoff);
KEY_SPEC(KEY_RELEASE, 601, &Special);
KEY_SPEC(KEY_SET0, 602, &Special);
KEY_SPEC(KEY_REBOOT, 603, &Special);

// Custom Non-Keyboard Things (Numeric ID is pre-0xA000)
KEY_SPEC(MOUSE_LCLICK, 900, &Special);
KEY_SPEC(MOUSE_RCLICK, 901, &Special);
KEY_SPEC(TRILL_MODE1, 902, &Special);
KEY_SPEC(TRILL_MODE2, 903, &Special);
KEY_SPEC(TRILL_MODE3, 904, &Special);
KEY_SPEC(LEDS_BR0, 905, &LedAdj);
KEY_SPEC(LEDS_BR1, 906, &LedAdj);
KEY_SPEC(LEDS_BR2, 907, &LedAdj);
KEY_SPEC(LEDS_BR3, 908, &LedAdj);
KEY_SPEC(LEDS_BR4, 909, &LedAdj);
KEY_SPEC(LEDS_BR5, 910, &LedAdj);
KEY_SPEC(LEDS_BR6, 911, &LedAdj);
KEY_SPEC(LEDS_BR7, 912, &LedAdj);
KEY_SPEC(LEDS_BR8, 913, &LedAdj);
KEY_SPEC(LEDS_BR9, 914, &LedAdj);
KEY_SPEC(LEDS_BR10, 915, &LedAdj);
KEY_SPEC(LEDS_INC, 916, &LedAdj);
KEY_SPEC(LEDS_DEC, 917, &LedAdj);

// Standard USB HID Keys (from usb_keyboard.h)
KEY_SPEC_STD(KEY_ESC, &Modifier);
KEY_SPEC_STD(KEY_F1, &FKeys1);
KEY_SPEC_STD(KEY_F2, &FKeys1);
KEY_SPEC_STD(KEY_F3, &FKeys1);
KEY_SPEC_STD(KEY_F4, &FKeys1);
KEY_SPEC_STD(KEY_F5, &FKeys1b);
KEY_SPEC_STD(KEY_F6, &FKeys1b);
KEY_SPEC_STD(KEY_F7, &FKeys1b);
KEY_SPEC_STD(KEY_F8, &FKeys1b);
KEY_SPEC_STD(KEY_F9, &FKeys1);
KEY_SPEC_STD(KEY_F10, &FKeys1);
KEY_SPEC_STD(KEY_F11, &FKeys1);
KEY_SPEC_STD(KEY_F12, &FKeys1);
KEY_SPEC_STD(KEY_F13, &FKeys2); // Standard F13-F24
KEY_SPEC_STD(KEY_F14, &FKeys2);
KEY_SPEC_STD(KEY_F15, &FKeys2);
KEY_SPEC_STD(KEY_F16, &FKeys2);
KEY_SPEC_STD(KEY_F17, &FKeys2b);
KEY_SPEC_STD(KEY_F18, &FKeys2b);
KEY_SPEC_STD(KEY_F19, &FKeys2b);
KEY_SPEC_STD(KEY_F20, &FKeys2b);
KEY_SPEC_STD(KEY_F21, &FKeys2);
KEY_SPEC_STD(KEY_F22, &FKeys2);
KEY_SPEC_STD(KEY_F23, &FKeys2);
KEY_SPEC_STD(KEY_F24, &FKeys2);

KEY_SPEC_STD(KEY_PRINTSCREEN, &Special);
KEY_SPEC_STD(KEY_SCROLL_LOCK, &Scrllock);
KEY_SPEC_STD(KEY_PAUSE, &Special);

KEY_SPEC_STD(KEY_1, &Number);
KEY_SPEC_STD(KEY_2, &Number);
KEY_SPEC_STD(KEY_3, &Number);
KEY_SPEC_STD(KEY_4, &Number);
KEY_SPEC_STD(KEY_5, &Number);
KEY_SPEC_STD(KEY_6, &Number);
KEY_SPEC_STD(KEY_7, &Number);
KEY_SPEC_STD(KEY_8, &Number);
KEY_SPEC_STD(KEY_9, &Number);
KEY_SPEC_STD(KEY_0, &Number);
KEY_SPEC_STD(KEY_MINUS, &Chara1);
KEY_SPEC_STD(KEY_EQUAL, &Chara1);
KEY_SPEC_STD(KEY_BACKSLASH, &Chara1);
KEY_SPEC_STD(KEY_BACKSPACE, &Letter);

KEY_SPEC_STD(KEY_INSERT, &Chara1);
KEY_SPEC_STD(KEY_DELETE, &Modifier);
KEY_SPEC_STD(KEY_HOME, &Modifier);
KEY_SPEC_STD(KEY_END, &Modifier);
KEY_SPEC_STD(KEY_PAGE_UP, &Modifier);
KEY_SPEC_STD(KEY_PAGE_DOWN, &Modifier);
KEY_SPEC_STD(KEY_UP_ARROW, &Nav);
KEY_SPEC_STD(KEY_DOWN_ARROW, &Nav);
KEY_SPEC_STD(KEY_LEFT_ARROW, &Nav);
KEY_SPEC_STD(KEY_RIGHT_ARROW, &Nav);

KEY_SPEC_STD(KEY_NUM_LOCK, &Numlock);
KEY_SPEC_STD(KEYPAD_SLASH, &Chara2);
KEY_SPEC_STD(KEYPAD_ASTERIX, &Chara2);
KEY_SPEC_STD(KEYPAD_PLUS, &Chara2);
KEY_SPEC_STD(KEYPAD_MINUS, &Chara2);
KEY_SPEC_STD(KEYPAD_ENTER, &Letter);
KEY_SPEC_STD(KEYPAD_0, &Number);
KEY_SPEC_STD(KEYPAD_1, &Number);
KEY_SPEC_STD(KEYPAD_2, &Numnav);
KEY_SPEC_STD(KEYPAD_3, &Number);
KEY_SPEC_STD(KEYPAD_4, &Numnav);
KEY_SPEC_STD(KEYPAD_5, &Number);
KEY_SPEC_STD(KEYPAD_6, &Numnav);
KEY_SPEC_STD(KEYPAD_7, &Number);
KEY_SPEC_STD(KEYPAD_8, &Numnav);
KEY_SPEC_STD(KEYPAD_9, &Number);
KEY_SPEC_STD(KEYPAD_PERIOD, &Chara2);

KEY_SPEC_STD(KEY_TAB, &Modifier);
KEY_SPEC_STD(KEY_TILDE, &Chara1);
KEY_SPEC_STD(KEY_CAPS_LOCK, &Capslock);
KEY_SPEC_STD(KEY_LEFT_SHIFT, &Modifier);
KEY_SPEC_STD(KEY_LEFT_CTRL, &Modifier);
KEY_SPEC_STD(KEY_LEFT_GUI, &Modifier);
KEY_SPEC_STD(KEY_LEFT_ALT, &Modifier); // Standard Left Alt
KEY_SPEC_STD(KEY_SPACE, &Letter);

KEY_SPEC_STD(KEY_Q, &Letter);
KEY_SPEC_STD(KEY_W, &Letter);
KEY_SPEC_STD(KEY_E, &Letter);
KEY_SPEC_STD(KEY_R, &Letter);
KEY_SPEC_STD(KEY_T, &Letter);
KEY_SPEC_STD(KEY_Y, &Letter);
KEY_SPEC_STD(KEY_U, &Letter);
KEY_SPEC_STD(KEY_I, &Letter);
KEY_SPEC_STD(KEY_O, &Letter);
KEY_SPEC_STD(KEY_P, &Letter);
KEY_SPEC_STD(KEY_A, &Letter);
KEY_SPEC_STD(KEY_S, &Letter);
KEY_SPEC_STD(KEY_D, &Letter);
KEY_SPEC_STD(KEY_F, &Letter);
KEY_SPEC_STD(KEY_G, &Letter);
KEY_SPEC_STD(KEY_H, &Letter);
KEY_SPEC_STD(KEY_J, &Letter);
KEY_SPEC_STD(KEY_K, &Letter);
KEY_SPEC_STD(KEY_L, &Letter);
KEY_SPEC_STD(KEY_Z, &Letter);
KEY_SPEC_STD(KEY_X, &Letter);
KEY_SPEC_STD(KEY_C, &Letter);
KEY_SPEC_STD(KEY_V, &Letter);
KEY_SPEC_STD(KEY_B, &Letter);
KEY_SPEC_STD(KEY_N, &Letter);
KEY_SPEC_STD(KEY_M, &Letter);

KEY_SPEC_STD(KEY_LEFT_BRACE, &Chara1);  // Standard [
KEY_SPEC_STD(KEY_RIGHT_BRACE, &Chara1); // Standard ]
KEY_SPEC_STD(KEY_SEMICOLON, &Chara1);
KEY_SPEC_STD(KEY_QUOTE, &Chara1);
KEY_SPEC_STD(KEY_ENTER, &Letter);
KEY_SPEC_STD(KEY_COMMA, &Chara1);
KEY_SPEC_STD(KEY_PERIOD, &Chara1);
KEY_SPEC_STD(KEY_SLASH, &Chara1);
KEY_SPEC_STD(KEY_RIGHT_SHIFT, &Modifier);
KEY_SPEC_STD(KEY_RIGHT_CTRL, &Modifier);
KEY_SPEC_STD(KEY_RIGHT_GUI, &Modifier);
KEY_SPEC_STD(KEY_RIGHT_ALT, &Modifier); // Standard Right Alt

KEY_SPEC_STD(KEY_MEDIA_MUTE, &Modifier);
KEY_SPEC_STD(KEY_MEDIA_PREV_TRACK, &Special);
KEY_SPEC_STD(KEY_MEDIA_NEXT_TRACK, &Special);
KEY_SPEC_STD(KEY_MEDIA_REWIND, &Special);
KEY_SPEC_STD(KEY_MEDIA_FAST_FORWARD, &Special);
KEY_SPEC_STD(KEY_MEDIA_RECORD, &Special);
KEY_SPEC_STD(KEY_MEDIA_PLAY_PAUSE, &Special);
KEY_SPEC_STD(KEY_MEDIA_VOLUME_INC, &Modifier);
KEY_SPEC_STD(KEY_MEDIA_VOLUME_DEC, &Modifier);

// Ensure all color category variables (&Layer, &Letter, etc.) are defined in key_definitions.cpp
// and declared extern in key_definitions.h for these pointers to be valid.
