#ifndef EDGEEVENTS_H
#define EDGEEVENTS_H

#include "main.h"
#include "layers.h"
#include "trillbar.h"
#include "keydefs.h"
#include "rgbleds.h"
#include "config.h"
#include "macros.h" // Should declare MacroManager

#define EDGE_DEBUG 0

// External variable declarations (defined in Protoboard.cpp or rgbleds.cpp)
extern bool L_0;
extern bool L_1;
extern bool L_2;
extern bool L_3;
extern bool L_4;
extern bool L_1_2L;
extern bool ALT_L;
extern bool ALT_R;
extern bool CAPS_SLSH;
extern bool CAPS_ESC;

extern bool loopTimer;
extern bool updateNeeded;
extern int brightness;

// Double-tap tracking variables (declared in Protoboard.cpp)
extern uint8_t doubleTapRow;
extern uint8_t doubleTapCol;
extern unsigned long doubleTapTimestamp;
extern const unsigned int DOUBLE_TAP_WINDOW_MS;

// Macro Manager (assuming it's a global object)
extern SimpleMacroManager macroManager;


bool L2AltTab = false;
bool prev_L_1 = 0;
bool prev_L_2 = 0;
bool prev_L_3 = 0;
bool prev_L_4 = 0;
bool prev_L_1_2L = 0;
int LYR0_row = -1;
int LYR0_col = -1;

// Helper function to press and release a key
void pressAndRelease(int key) {
  Keyboard.press(key);
  Keyboard.release(key);
}

void shiftedKey(int key) {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(key);
  Keyboard.release(key);
  Keyboard.release(KEY_LEFT_SHIFT);
}

void shiftedFKey(int fKey) {
  shiftedKey(fKey);
}

struct BrightnessLevel {
  int code;
  int brightnessValue;
};

struct SimpleKeyAction {
  int code;
  int keyToPress;
};

struct LayerResetAction {
  int code;
  bool* layerFlag;
};

const LayerResetAction layerResets[] = {
  {LAYER_1, &L_1}, {LAYER_2, &L_2}, {LAYER_3, &L_3},
  {LAYER_4, &L_4}, {LOOP_COUNT, &loopTimer},
};

void pressAndReleaseMultiple(int count, ...) {
  va_list args;
  va_start(args, count);
  for (int i = 0; i < count; i++) {
    int key = va_arg(args, int);
    Keyboard.press(key);
    Keyboard.release(key);
  }
  va_end(args);
}

const BrightnessLevel brightnessLevels[] = {
  {LEDS_BR0, brt0}, {LEDS_BR1, brt1}, {LEDS_BR2, brt2}, {LEDS_BR3, brt3}, {LEDS_BR4, brt4},
  {LEDS_BR5, brt5}, {LEDS_BR6, brt6}, {LEDS_BR7, brt7}, {LEDS_BR8, brt8}, {LEDS_BR9, brt9},
  {LEDS_BR10, brt10},
};

const SimpleKeyAction shiftedKeys[] = {
  {EXCLMAMATION, KEY_1}, {KEY_AT, KEY_2}, {KEY_HASH, KEY_3}, {KEY_DOLLAR, KEY_4},
  {KEY_PERCENT, KEY_5}, {KEY_CARAT, KEY_6}, {AMPERSAND, KEY_7}, {KEY_ASTERISK, KEY_8},
  {L_PARENTHESIS, KEY_9}, {R_PARENTHESIS, KEY_0}, {UNDERSCORE, KEY_MINUS}, {KEY_PLUS, KEY_EQUAL},
  {KEY_PIPE, KEY_BACKSLASH}, {KEY_DBLQUOTE, KEY_QUOTE}, {LEFT_CHEVRON, KEY_COMMA},
  {RIGHT_CHEVRON, KEY_PERIOD}, {QUESTION_MARK, KEY_SLASH}, {KEY_COLON, KEY_SEMICOLON},
  {CURL_L_BRACE, KEY_LEFT_BRACE}, {CURL_R_BRACE, KEY_RIGHT_BRACE}, {SHIFT_TILDE, KEY_TILDE},
  {KEYSF13, KEY_F13}, {KEYSF14, KEY_F14}, {KEYSF15, KEY_F15}, {KEYSF16, KEY_F16},
  {KEYSF17, KEY_F17}, {KEYSF18, KEY_F18}, {KEYSF19, KEY_F19}, {KEYSF20, KEY_F20},
  {KEYSF21, KEY_F21}, {KEYSF22, KEY_F22}, {KEYSF23, KEY_F23}, {KEYSF24, KEY_F24}
};

// All of the custom operations to be performed on key press
void keyPressed(Key* key, LayoutKey* layout) {
  #if EDGE_DEBUG
  Serial.print("Key pressed: row="); Serial.print(key->row);
  Serial.print(", col="); Serial.println(key->column);
  #endif

  uint8_t row = key->row;
  uint8_t col = key->column;
  unsigned long currentTime = millis();
  uint16_t codeToPress = layout->code; // CORRECT DEFINITION OF codeToPress

  physicalKeyStates[row][col].isPressed = true;
  physicalKeyStates[row][col].activeKey = layout;

  if (doubleTapRow == row && doubleTapCol == col && layout->doubleTapCode != 0 && (currentTime - doubleTapTimestamp < DOUBLE_TAP_WINDOW_MS)) {
    codeToPress = layout->doubleTapCode;
    #if EDGE_DEBUG
    Serial.print("Double tap detected! Sending code: "); Serial.println(codeToPress);
    #endif
    doubleTapRow = 255; doubleTapCol = 255; doubleTapTimestamp = 0;
  } else {
    if (layout->doubleTapCode != 0) {
      #if EDGE_DEBUG
      Serial.print("First tap of potential double tap. Key: "); Serial.print(row); Serial.print(","); Serial.print(col); Serial.print(" Code: "); Serial.println(layout->code);
      #endif
      doubleTapRow = row; doubleTapCol = col; doubleTapTimestamp = currentTime;
    } else {
      if (doubleTapTimestamp != 0 && (doubleTapRow != row || doubleTapCol != col)) {
        #if EDGE_DEBUG
        Serial.println("Different key pressed, clearing pending double tap.");
        #endif
        doubleTapRow = 255; doubleTapCol = 255; doubleTapTimestamp = 0;
      }
    }
  }

  physicalKeyStates[row][col].activeCode = codeToPress;

  if (codeToPress == KEY_NULL) return;
  if (macroManager.executeMacro(codeToPress)) return;

  for (uint8_t i = 0; i < sizeof(brightnessLevels)/sizeof(BrightnessLevel); i++) {
    if (codeToPress == brightnessLevels[i].code) {
      brightness = brightnessLevels[i].brightnessValue;
      LEDS.setBrightness(brightness);
      return;
    }
  }

  if (codeToPress == LEDS_INC) { ledsINC(); return; }
  if (codeToPress == LEDS_DEC) { ledsDEC(); return; }

  if (codeToPress == TRILL_MODE1) { trillbar::setMode(trillbar::MODE_ARROWS); return; }
  if (codeToPress == TRILL_MODE2) { trillbar::setMode(trillbar::MODE_SCROLL); return; }
  if (codeToPress == TRILL_MODE3) { trillbar::setMode(trillbar::MODE_BRIGHTNESS); return; }

  if (codeToPress == MOUSE_LCLICK) { Mouse.set_buttons(1, 0, 0); return; }
  if (codeToPress == MOUSE_RCLICK) { Mouse.set_buttons(0, 0, 1); return; }

  if (codeToPress == KEY_RELEASE) {
    Keyboard.set_modifier(0); Keyboard.set_key1(0); Keyboard.send_now(); Keyboard.releaseAll();
    return;
  }

  if (codeToPress == KEY_ALT_TAB) {
    Keyboard.press(KEY_LEFT_ALT); Keyboard.send_now(); Keyboard.press(KEY_TAB); Keyboard.release(KEY_TAB);
    L2AltTab = true; return;
  }

  for (uint8_t i = 0; i < sizeof(shiftedKeys)/sizeof(SimpleKeyAction); i++) {
    if (codeToPress == shiftedKeys[i].code) {
      shiftedKey(shiftedKeys[i].keyToPress); return;
    }
  }

  if (codeToPress == KEY_REBOOT) { _reboot_Teensyduino_(); return; }

  if (codeToPress == KEY_SET0) {
    L_1 = 0; L_2 = 0; L_3 = 0; L_4 = 0; L_1_2L = 0; L_0 = false;
    LYR0_row = -1; LYR0_col = -1; ALT_R = 0; ALT_L = 0; updateNeeded = true; return;
  }

  switch (codeToPress) {
    case LAYER_1: L_1 = 1; L_check(); updateNeeded = true; return;
    case LAYER_2: L_2 = 1; L_check(); updateNeeded = true; return;
    case LAYER_3: L_3 = 1; L_check(); updateNeeded = true; return;
    case LAYER_4: L_4 = 1; L_check(); updateNeeded = true; return;
    case LOOP_COUNT: loopTimer = true; return;
    case LAYER_1_2L: L_1_2L = !L_1_2L; L_1 = 0; L_2 = 0; L_check(); updateNeeded = true; return;
    case KEY_ALTL: ALT_L = !ALT_L; updateNeeded = true; return;
    case KEY_ALTR: ALT_R = !ALT_R; updateNeeded = true; return;
    case KEY_CAPS_SLASH: CAPS_SLSH = !CAPS_SLSH; CAPS_ESC = 0; updateNeeded = true; return;
    case KEY_CAPS_ESC: CAPS_ESC = !CAPS_ESC; CAPS_SLSH = 0; updateNeeded = true; return;
    case LAYER_0:
      prev_L_1 = L_1; prev_L_2 = L_2; prev_L_3 = L_3; prev_L_4 = L_4; prev_L_1_2L = L_1_2L;
      LYR0_row = key->row; LYR0_col = key->column;
      L_0 = true; L_1 = 0; L_2 = 0; L_3 = 0; L_4 = 0; L_1_2L = 0;
      L_check(); updateNeeded = true; return;
  }
  Keyboard.press(codeToPress); // THIS IS LINE 333 (approx) in this version
}

void keyReleased(Key* key, LayoutKey* layout) {
  uint8_t row = key->row;
  uint8_t col = key->column;
  uint16_t initialCodeFromLayout = layout->code;
  LayoutKey* activeKey = physicalKeyStates[row][col].activeKey;
  uint16_t relevantCode = activeKey ? activeKey->code : initialCodeFromLayout;

  #if EDGE_DEBUG
  Serial.print("Key released: row="); Serial.print(key->row); Serial.print(", col="); Serial.print(key->column);
  Serial.print(", initialLayoutCode="); Serial.print(initialCodeFromLayout);
  if (activeKey) { Serial.print(", activeKey->code="); Serial.print(activeKey->code); } else { Serial.print(", activeKey=NULL"); }
  Serial.print(", relevantCode="); Serial.print(relevantCode);
  Serial.print(", physicalState.activeCode (before clear)="); Serial.print(physicalKeyStates[row][col].activeCode);
  Serial.print(", L_0="); Serial.println(L_0);
  #endif

  physicalKeyStates[row][col].isPressed = false;
  physicalKeyStates[row][col].activeCode = 0;
  physicalKeyStates[row][col].activeKey = nullptr;

  if (relevantCode == KEY_NULL) return;
  if (relevantCode == KEY_SET0) { L_check(); updateNeeded = true; return; }

  for (uint8_t i = 0; i < sizeof(layerResets)/sizeof(LayerResetAction); i++) {
    if (relevantCode == layerResets[i].code) {
      if (relevantCode == LAYER_2 && L2AltTab) { Keyboard.release(KEY_LEFT_ALT); L2AltTab = false; }
      *(layerResets[i].layerFlag) = 0;
      Config::saveBrightness(brightness);
      L_check(); updateNeeded = true; return;
    }
  }

  if (relevantCode == LAYER_1_2L) { L_check(); updateNeeded = true; return; }

  if (relevantCode == LAYER_0) {
    #if EDGE_DEBUG
    Serial.println("Layer 0 released");
    #endif
    L_1 = prev_L_1; L_2 = prev_L_2; L_3 = prev_L_3; L_4 = prev_L_4; L_1_2L = prev_L_1_2L;
    L_0 = false; LYR0_row = -1; LYR0_col = -1;
    L_check(); updateNeeded = true; return;
  }

  switch (relevantCode) {
    case MOUSE_LCLICK:
    case MOUSE_RCLICK:
      Mouse.set_buttons(0, 0, 0);
      // Mouse.send_now(); // REMOVED - THIS IS LINE 425 (approx)
      return;
  }

  bool isNonStandardRelease = (relevantCode == KEY_ALTL || relevantCode == KEY_ALTR ||
                             relevantCode == KEY_CAPS_SLASH || relevantCode == KEY_CAPS_ESC ||
                             (relevantCode >= LAYER_0 && relevantCode <= LAYER_4) || /* Basic layer check */
                             relevantCode == LAYER_1_2L ||
                             relevantCode == LOOP_COUNT);

  if (!isNonStandardRelease && relevantCode != KEY_NULL) {
      Keyboard.release(relevantCode);
  }
}
#endif
