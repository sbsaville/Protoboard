#ifndef EDGEEVENTS_H
#define EDGEEVENTS_H

#include "main.h"
#include "layers.h"
#include "trillbar.h"
#include "keydefs.h"
#include "rgbleds.h"
#include "config.h"
#include "macros.h"

#define EDGE_DEBUG 0

extern bool L_0;
extern bool L_1;
extern bool L_2;
extern bool L_3;
extern bool L_4;
extern bool L_1_2L;
extern bool ALT_L;
extern bool ALT_R;
extern bool CAPS_SLSH;

bool L2AltTab = false;

// Add near the top with other external variables
bool prev_L_1 = 0;
bool prev_L_2 = 0;
bool prev_L_3 = 0;
bool prev_L_4 = 0;
bool prev_L_1_2L = 0;

int LYR0_row = -1;    // Store the physical row position of pressed LYR0 key
int LYR0_col = -1;    // Store the physical column position of pressed LYR0 key

extern bool loopTimer;

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

// TextMacro struct moved to macros.h

struct BrightnessLevel {
  int code;
  int brightnessValue;
};

struct SimpleKeyAction {
  int code;
  int keyToPress;
};

// AltCodeSequence moved to macros.h

// Helper structure for layer reset actions
struct LayerResetAction {
  int code;
  bool* layerFlag; // Pointer to layer flag to reset
};

// Layer reset table
const LayerResetAction layerResets[] = {
  {LAYER_1, &L_1},
  {LAYER_2, &L_2},
  {LAYER_3, &L_3},
  {LAYER_4, &L_4},
  {LOOP_COUNT, &loopTimer},
};

// Helper function to press and release multiple keys in sequence
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

// Alt-code helper function moved to macros.h

// Text macros and alt-codes now handled by MacroManager

// Brightness levels
const BrightnessLevel brightnessLevels[] = {
  {LEDS_BR0,  brt0},
  {LEDS_BR1,  brt1},
  {LEDS_BR2,  brt2},
  {LEDS_BR3,  brt3},
  {LEDS_BR4,  brt4},
  {LEDS_BR5,  brt5},
  {LEDS_BR6,  brt6},
  {LEDS_BR7,  brt7},
  {LEDS_BR8,  brt8},
  {LEDS_BR9,  brt9},
  {LEDS_BR10, brt10},
};

// Shifted keys
const SimpleKeyAction shiftedKeys[] = {
  {EXCLMAMATION,    KEY_1},
  {KEY_AT,         KEY_2},
  {KEY_HASH,       KEY_3},
  {KEY_DOLLAR,     KEY_4},
  {KEY_PERCENT,    KEY_5},
  {KEY_CARAT,      KEY_6},
  {AMPERSAND,      KEY_7},
  {KEY_ASTERISK,   KEY_8},
  {L_PARENTHESIS,  KEY_9},
  {R_PARENTHESIS,  KEY_0},
  {UNDERSCORE,     KEY_MINUS},
  {KEY_PLUS,       KEY_EQUAL},
  {KEY_PIPE,       KEY_BACKSLASH},
  {KEY_DBLQUOTE,   KEY_QUOTE},
  {LEFT_CHEVRON,   KEY_COMMA},
  {RIGHT_CHEVRON,  KEY_PERIOD},
  {QUESTION_MARK,  KEY_SLASH},
  {KEY_COLON,      KEY_SEMICOLON},
  {CURL_L_BRACE,   KEY_LEFT_BRACE},
  {CURL_R_BRACE,   KEY_RIGHT_BRACE},
  {SHIFT_TILDE,    KEY_TILDE},
  {KEYSF13,        KEY_F13},
  {KEYSF14,        KEY_F14},
  {KEYSF15,        KEY_F15},
  {KEYSF16,        KEY_F16},
  {KEYSF17,        KEY_F17},
  {KEYSF18,        KEY_F18},
  {KEYSF19,        KEY_F19},
  {KEYSF20,        KEY_F20},
  {KEYSF21,        KEY_F21},
  {KEYSF22,        KEY_F22},
  {KEYSF23,        KEY_F23},
};

// Alt-code sequences moved to macro_definitions.h

// All of the custom operations to be performed on key press
void keyPressed(Key* key, LayoutKey* layout) {
  #if EDGE_DEBUG
  Serial.print("Key pressed: row=");
  Serial.print(key->row);
  Serial.print(", col=");
  Serial.println(key->column);
  #endif
  int code = layout->code;

  // Store the key state information - this must happen before any early returns
  uint8_t row = key->row;
  uint8_t col = key->column;
  physicalKeyStates[row][col].isPressed = true;
  physicalKeyStates[row][col].activeCode = code;
  physicalKeyStates[row][col].activeKey = layout;  // Store the original LayoutKey pointer

  // Check for null key first (early return)
  if (code == KEY_NULL) {
    return;
  }

  // Check macros using new macro system
  if (macroManager.executeMacro(code)) {
    return;
  }

  // Check brightness levels
  for (uint8_t i = 0; i < sizeof(brightnessLevels)/sizeof(BrightnessLevel); i++) {
    if (code == brightnessLevels[i].code) {
      brightness = brightnessLevels[i].brightnessValue;
      LEDS.setBrightness(brightness);
      return;
    }
  }

  // Check LED increment/decrement
  if (code == LEDS_INC) {
    ledsINC();
    return;
  }
  else if (code == LEDS_DEC) {
    ledsDEC();
    return;
  }

  // Check trill modes
  if (code == TRILL_MODE1) {
    trillbar::setMode(trillbar::MODE_ARROWS);
    return;
  }
  else if (code == TRILL_MODE2) {
    trillbar::setMode(trillbar::MODE_SCROLL);
    return;
  }
  else if (code == TRILL_MODE3) {
    trillbar::setMode(trillbar::MODE_BRIGHTNESS);
    return;
  }

  // Check mouse clicks
  if (code == MOUSE_LCLICK) {
    Mouse.set_buttons(1, 0, 0);
    return;
  }
  else if (code == MOUSE_RCLICK) {
    Mouse.set_buttons(0, 0, 1);
    return;
  }

  // Check key release
  if (code == KEY_RELEASE) {
    Keyboard.set_modifier(0);
    Keyboard.set_key1(0);
    Keyboard.send_now();
    Keyboard.releaseAll();
//    trillbar::active(false);
    return;
  }

  if (code == KEY_ALT_TAB) {
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.send_now();
    Keyboard.press(KEY_TAB);
    Keyboard.release(KEY_TAB);
    L2AltTab = true;
    return;
  }

  // Alt-codes now handled by macro system above

  for (uint8_t i = 0; i < sizeof(shiftedKeys)/sizeof(SimpleKeyAction); i++) {
    if (code == shiftedKeys[i].code) {
      shiftedKey(shiftedKeys[i].keyToPress);
      return;
    }
  }

  if (code == KEY_REBOOT) {
    _reboot_Teensyduino_();
    return;
  }

  // Emergency layer reset
  if (code == KEY_SET0) {
    L_1 = 0;
    L_2 = 0;
    L_3 = 0;
    L_4 = 0;
    L_1_2L = 0;
    L_0 = false;
    LYR0_row = -1;
    LYR0_col = -1;
    ALT_R = 0;
    ALT_L = 0;
    CAPSLSH = 0;
    CAPSESC = 0;
    return;
  }

  switch (code) {
    case LAYER_1:
      L_1 = 1;
      L_check();
      return;
    case LAYER_2:
      L_2 = 1;
      L_check();
      return;
      case LAYER_3:
      L_3 = 1;
      L_check();
      return;
    case LAYER_4:
      L_4 = 1;
      L_check();
      return;
    case LOOP_COUNT:
      loopTimer = 1;
      return;
    case LAYER_1_2L:
      L_1_2L = !L_1_2L;
      L_1 = 0;
      L_2 = 0;
      L_check();
      return;
    case KEY_ALTL:
      ALT_L = !ALT_L;
      updateNeeded = true;
      return;
    case KEY_ALTR:
      ALT_R = !ALT_R;
      updateNeeded = true;
      return;
    case KEY_CAPS_SLASH:
      CAPS_SLSH = !CAPS_SLSH;
      updateNeeded = true;
      return;
    case KEY_CAPS_ESC:
      CAPS_ESC = !CAPS_ESC;
      updateNeeded = true;
      return;
    case LAYER_0:
      prev_L_1 = L_1;
      prev_L_2 = L_2;
      prev_L_3 = L_3;
      prev_L_4 = L_4;
      prev_L_1_2L = L_1_2L;
      LYR0_row = key->row;
      LYR0_col = key->column;
      L_0 = 1;
      L_1 = 0;
      L_2 = 0;
      L_3 = 0;
      L_4 = 0;
      L_1_2L = 0;
      L_check();
      return;
  }

  Keyboard.press(layout->code);

  }
                                                           // All of the operations to be performed on key release
  void keyReleased(Key* key, LayoutKey* layout) {
  int code = layout->code;
  uint8_t row = key->row;
  uint8_t col = key->column;

  // Get the original active key information from our tracking matrix
  LayoutKey* activeKey = physicalKeyStates[row][col].activeKey;

  #if EDGE_DEBUG
  Serial.print("Key released: row="); Serial.print(key->row);
  Serial.print(", col="); Serial.print(key->column);
  Serial.print(", code="); Serial.print(code);
  Serial.print(", activeCode="); Serial.print(activeCode);
  if (activeKey) {
    Serial.print(", activeKeyCode="); Serial.print(activeKey->code);
  }
  Serial.print(", L_0="); Serial.println(L_0);
  #endif

  // Clear the key state tracking
  physicalKeyStates[row][col].isPressed = false;
  physicalKeyStates[row][col].activeCode = 0;
  physicalKeyStates[row][col].activeKey = nullptr;

  // Check for null key first (early return)
  if ((code == KEY_NULL) && (!activeKey || activeKey->code == KEY_NULL)) {
    return;
  }
  // Special handling for KEY_SET0
  if (code == KEY_SET0 || (activeKey && activeKey->code == KEY_SET0)) {
    L_check();
    Keyboard.releaseAll();
    return;
  }
  // Handle layer resets - prioritize the activeKey if available
  uint16_t relevantCode = activeKey ? activeKey->code : code;

  for (uint8_t i = 0; i < sizeof(layerResets)/sizeof(LayerResetAction); i++) {
    if (relevantCode == layerResets[i].code) {
      if (relevantCode == LAYER_2 && L2AltTab) {
        Keyboard.release(KEY_LEFT_ALT);
        L2AltTab = false;
      }
      *(layerResets[i].layerFlag) = 0; // Reset the layer flag

      // Save brightness to SD card when any layer key is released
      Config::saveBrightness(brightness);

      L_check();
      return;
    }
  }

  // Handle LAYER_1_2L which only needs L_check()
  if (relevantCode == LAYER_1_2L) {
    L_check();
    return;
  }

  // Handle LAYER_0
  if (relevantCode == LAYER_0) {
    #if EDGE_DEBUG
    Serial.println("Layer 0 released");
    #endif
    // Restore previous layer states
    L_1 = prev_L_1;
    L_2 = prev_L_2;
    L_3 = prev_L_3;
    L_4 = prev_L_4;
    L_1_2L = prev_L_1_2L;
    L_0 = false;
    L_check();
    return;
  }

  // Handle mouse button releases
  switch (code) {
    case MOUSE_LCLICK:
    case MOUSE_RCLICK:
      Mouse.set_buttons(0, 0, 0);
      return;
  }
    // Default: regular key release
  // Always use the activeKey if available (preserves original function during layer change)
  if (activeKey) {
    Keyboard.release(activeKey->code);
  } else {
    Keyboard.release(code);
  }

}

  #endif


