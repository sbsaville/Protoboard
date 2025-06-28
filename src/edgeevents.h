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

extern KeyMapEntry (*currentLayout)[columnsCount];

// extern bool L_0; // Replaced by layer0_override_active in Protoboard.cpp
// extern bool L_1; // Replaced by Layer struct states
// extern bool L_2; // "
// extern bool L_3; // "
// extern bool L_4; // "
// extern bool L_1_2L; // "
extern bool ALT_L;
extern bool ALT_R;
extern bool CAPS_SLSH;
extern bool CAPS_ESC;

bool L2AltTab = false; // Specific state for Alt-Tab behavior, might need review

// DOUBLE_TAP_WINDOW is now defined in Protoboard.cpp
// static int last_double_tap_candidate_row = -1; // Will be part of Layer struct or managed differently
// static int last_double_tap_candidate_col = -1; // "
// static unsigned long last_double_tap_press_time = 0; // "

// prev_L_ flags are no longer needed as layer state is more complex
// bool prev_L_1 = 0;
// bool prev_L_2 = 0;
// bool prev_L_3 = 0;
// bool prev_L_4 = 0;
// bool prev_L_1_2L = 0;

// LYR0_row/col for restoring state after LYR0 not directly needed in this new model's first pass
// int LYR0_row = -1;
// int LYR0_col = -1;

extern bool loopTimer; // This seems to be a global toggle, not a layer. Keep for now.

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

// struct LayerResetAction { // Obsolete with new layer system
//   int code;
//   bool* layerFlag;
// };

// const LayerResetAction layerResets[] = { // Obsolete
//   {LAYER_1, &L_1},
//   {LAYER_2, &L_2},
//   {LAYER_3, &L_3},
//   {LAYER_4, &L_4},
//   {LOOP_COUNT, &loopTimer}, // loopTimer is handled directly now in keyPressed
// };

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

void keyPressed(Key* key, LayoutKey* layout) {
  #if EDGE_DEBUG
  Serial.print("Key pressed: row=");
  Serial.print(key->row);
  Serial.print(", col=");
  Serial.println(key->column);
  #endif

  uint8_t row = key->row;
  uint8_t col = key->column;
  KeyMapEntry currentKeyMapEntry = currentLayout[row][col];
  LayoutKey* primaryKey = currentKeyMapEntry.primaryKey;
  // LayoutKey* doubleTapKeyPtr = currentKeyMapEntry.doubleTapKey; // Old double tap, to be removed or integrated

  if (primaryKey == nullptr) primaryKey = NUL; // Ensure primaryKey is never null

  int pressedKeyCode = primaryKey->code;

  physicalKeyStates[row][col].isPressed = true;
  physicalKeyStates[row][col].activeCode = pressedKeyCode; // Store the code of the key definition that was active upon press
  physicalKeyStates[row][col].activeKey = primaryKey;   // Store a pointer to the key definition itself

  bool keyActionTaken = false; // Flag to check if any layer/toggle logic handled this press. If so, don't send raw key.
  unsigned long now = millis();

  // --- Handle Layer Activations and Toggles ---
  for (size_t i = 0; i < activeLayers.size(); ++i) { // Use size_t and activeLayers.size()
    Layer* currentLayer = &activeLayers[i];
    bool isActivationPress = false;
    for (uint8_t k = 0; k < currentLayer->numActivationKeys; ++k) {
        if (currentLayer->activationKeys[k] == pressedKeyCode) {
            isActivationPress = true;
            break;
        }
    }

    if (isActivationPress) {
      keyActionTaken = true; // This key press is related to layer management.
      updateNeeded = true;   // Signal that layer states might have changed.

      switch (currentLayer->activationType) {
        case LayerActivationType::SINGLE_PRESS:
          currentLayer->isActive = true;
          #if EDGE_DEBUG
          // Serial.print("Layer activated (SINGLE_PRESS): "); Serial.println(currentLayer->name);
          Serial.print("Layer activated (SINGLE_PRESS): Index "); Serial.println(i);
          #endif
          break;
        case LayerActivationType::COMBO_PRESS:
          // For combo, all keys must be pressed. This logic assumes this key is one of them.
          // We need to check if other combo keys are ALSO currently pressed.
          {
            bool allComboKeysPressed = true;
            for (uint8_t k = 0; k < currentLayer->numActivationKeys; ++k) {
              bool foundPressed = false;
              if (currentLayer->activationKeys[k] == pressedKeyCode) { // This is the currently pressed key
                foundPressed = true;
                continue;
              }
              // Check other keys in physicalKeyStates
              for(uint8_t r=0; r < rowsCount; ++r) {
                for(uint8_t c=0; c < columnsCount; ++c) {
                  if (physicalKeyStates[r][c].isPressed && physicalKeyStates[r][c].activeCode == currentLayer->activationKeys[k]) {
                    foundPressed = true;
                    break;
                  }
                }
                if (foundPressed && currentLayer->activationKeys[k] != pressedKeyCode) break;
              }
              if (!foundPressed) {
                allComboKeysPressed = false;
                break;
              }
            }
            if (allComboKeysPressed) {
              currentLayer->isActive = true;
              #if EDGE_DEBUG
              // Serial.print("Layer activated (COMBO_PRESS): "); Serial.println(currentLayer->name);
              Serial.print("Layer activated (COMBO_PRESS): Index "); Serial.println(i);
              #endif
            }
          }
          break;
        case LayerActivationType::TOGGLE:
          if (pressedKeyCode == currentLayer->activationKeys[0]) { // Assuming first key is the toggle key
            currentLayer->isActive = !currentLayer->isActive;
            #if EDGE_DEBUG
            // Serial.print("Layer toggled: "); Serial.print(currentLayer->name); Serial.println(currentLayer->isActive ? " ON" : " OFF");
            Serial.print("Layer toggled: Index "); Serial.print(i); Serial.println(currentLayer->isActive ? " ON" : " OFF");
            #endif
          }
          // if toggleOffKey is different and pressed, it's handled in keyReleased or a separate check.
          // For now, simple toggle on activationKey[0]
          break;
        case LayerActivationType::DOUBLE_TAP_HOLD:
          // Handles press-hold activation part of a double-tap sequence
          if (currentLayer->waitingForSecondTap &&
              (now - currentLayer->lastTapTime) < DOUBLE_TAP_WINDOW &&
              currentLayer->activationKeys[0] == pressedKeyCode) {
            currentLayer->isActive = true; // Active while held
            currentLayer->waitingForSecondTap = false;
            currentLayer->tapCount = 0;
            #if EDGE_DEBUG
            // Serial.print("Layer activated (DOUBLE_TAP_HOLD): "); Serial.println(currentLayer->name);
            Serial.print("Layer activated (DOUBLE_TAP_HOLD): Index "); Serial.println(i);
            #endif
          } else if (!currentLayer->isActive) { // Only start new sequence if not already active from a previous valid DT_HOLD that hasn't been released
            currentLayer->waitingForSecondTap = true;
            currentLayer->lastTapTime = now;
            currentLayer->tapCount = 1;
            #if EDGE_DEBUG
            // Serial.print("Layer waiting for 2nd tap (DOUBLE_TAP_HOLD): "); Serial.println(currentLayer->name);
            Serial.print("Layer waiting for 2nd tap (DOUBLE_TAP_HOLD): Index "); Serial.println(i);
            #endif
          }
          break;
        case LayerActivationType::DOUBLE_TAP_TOGGLE:
          if (currentLayer->isActive && pressedKeyCode == currentLayer->activationKeys[0] && !currentLayer->waitingForSecondTap) {
            // Layer is already active, its activation key is pressed, and we are NOT in the middle of a new tap sequence for this layer.
            // This means it's a single press to toggle OFF.
            currentLayer->isActive = false;
            currentLayer->waitingForSecondTap = false;
            currentLayer->tapCount = 0;
            #if EDGE_DEBUG
            // Serial.print("Layer DEactivated by single press (DOUBLE_TAP_TOGGLE): "); Serial.println(currentLayer->name);
            Serial.print("Layer DEactivated by single press (DOUBLE_TAP_TOGGLE): Index "); Serial.println(i);
            #endif
          } else if (currentLayer->waitingForSecondTap &&
              (now - currentLayer->lastTapTime) < DOUBLE_TAP_WINDOW &&
              currentLayer->activationKeys[0] == pressedKeyCode) {
            // This is the second tap of a double tap to activate
            currentLayer->isActive = true; // Toggle ON
            currentLayer->waitingForSecondTap = false;
            currentLayer->tapCount = 0;
            #if EDGE_DEBUG
            // Serial.print("Layer activated (DOUBLE_TAP_TOGGLE): "); Serial.println(currentLayer->name);
            Serial.print("Layer activated (DOUBLE_TAP_TOGGLE): Index "); Serial.println(i);
            #endif
          } else if (!currentLayer->isActive) {
            // Layer is not active, so this is the first tap of a potential double-tap to turn ON
            currentLayer->waitingForSecondTap = true;
            currentLayer->lastTapTime = now;
            currentLayer->tapCount = 1;
            #if EDGE_DEBUG
            // Serial.print("Layer waiting for 2nd tap (DOUBLE_TAP_TOGGLE): "); Serial.println(currentLayer->name);
            Serial.print("Layer waiting for 2nd tap (DOUBLE_TAP_TOGGLE): Index "); Serial.println(i);
            #endif
          }
          // If layer is active and a different key is pressed, or if it's the first tap of an activation sequence while already active (which shouldn't happen with current logic), no change.
          break;
        default:
          break;
      }
    }
  }

  // --- Handle Specific Key Toggles (not layers) ---
  if (pressedKeyCode == KEY_ALTL) {
    ALT_L = !ALT_L;
    updateNeeded = true; keyActionTaken = true;
  } else if (pressedKeyCode == KEY_ALTR) {
    ALT_R = !ALT_R;
    updateNeeded = true; keyActionTaken = true;
  } else if (pressedKeyCode == KEY_CAPS_SLASH) {
    CAPS_SLSH = !CAPS_SLSH;
    if (CAPS_SLSH) CAPS_ESC = false; // Mutually exclusive
    updateNeeded = true; keyActionTaken = true;
  } else if (pressedKeyCode == KEY_CAPS_ESC) {
    CAPS_ESC = !CAPS_ESC;
    if (CAPS_ESC) CAPS_SLSH = false; // Mutually exclusive
    updateNeeded = true; keyActionTaken = true;
  } else if (pressedKeyCode == LAYER_0) { // Layer 0 Override Key
    layer0_override_active = true;
    updateNeeded = true; keyActionTaken = true;
    #if EDGE_DEBUG
    Serial.println("LAYER_0 key pressed - override ACTIVE");
    #endif
  } else if (pressedKeyCode == LOOP_COUNT) { // Example of a simple toggle
      loopTimer = !loopTimer;
      keyActionTaken = true; // Consumes the key press
      #if EDGE_DEBUG
      Serial.print("loopTimer toggled: "); Serial.println(loopTimer);
      #endif
  }


  // --- Fallback to other key actions if not consumed by layer/toggle logic ---
  if (!keyActionTaken) {
    if (pressedKeyCode == KEY_NULL) {
      return; // Do nothing for explicit NUL keys
    }

    // Macro execution
    if (macroManager.executeMacro(pressedKeyCode)) {
      return; // Macro handled it
    }

    // Brightness controls
    for (uint8_t i = 0; i < sizeof(brightnessLevels) / sizeof(BrightnessLevel); i++) {
      if (pressedKeyCode == brightnessLevels[i].code) {
        brightness = brightnessLevels[i].brightnessValue;
        LEDS.setBrightness(brightness);
        Config::saveBrightness(brightness); // Save on change
        return;
      }
    }
    if (pressedKeyCode == LEDS_INC) { ledsINC(); return; }
    if (pressedKeyCode == LEDS_DEC) { ledsDEC(); return; }

    // Trillbar modes
    if (pressedKeyCode == TRILL_MODE1) { trillbar::setMode(trillbar::MODE_ARROWS); return; }
    if (pressedKeyCode == TRILL_MODE2) { trillbar::setMode(trillbar::MODE_SCROLL); return; }
    if (pressedKeyCode == TRILL_MODE3) { trillbar::setMode(trillbar::MODE_BRIGHTNESS); return; }

    // Mouse buttons
    if (pressedKeyCode == MOUSE_LCLICK) { Mouse.set_buttons(1,0,0); return;}
    if (pressedKeyCode == MOUSE_RCLICK) { Mouse.set_buttons(0,0,1); return;}

    // System keys
    if (pressedKeyCode == KEY_RELEASE) { Keyboard.releaseAll(); return; }
    if (pressedKeyCode == KEY_REBOOT) { _reboot_Teensyduino_(); return; }

    // Alt-Tab special handling
    if (pressedKeyCode == KEY_ALT_TAB) {
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.send_now(); // ensure ALT is registered before TAB
      Keyboard.press(KEY_TAB);
      Keyboard.release(KEY_TAB); // TAB is released quickly
      // L2AltTab = true; // This flag was used to release ALT when LAYER_2 was released. Needs new handling if still desired.
      // For now, ALT will be released when KEY_ALT_TAB itself is released.
      return;
    }

    // Shifted keys (sends key with SHIFT)
    for (uint8_t i = 0; i < sizeof(shiftedKeys) / sizeof(SimpleKeyAction); i++) {
      if (pressedKeyCode == shiftedKeys[i].code) {
        shiftedKey(shiftedKeys[i].keyToPress);
        return;
      }
    }

    // Emergency Layer Reset (KEY_SET0)
    if (pressedKeyCode == KEY_SET0) {
        for(size_t i=0; i < activeLayers.size(); ++i) activeLayers[i].isActive = false; // Use size_t
        layer0_override_active = false;
        ALT_L = false; ALT_R = false;
        CAPS_SLSH = false; CAPS_ESC = false;
        updateNeeded = true;
        L_check(); // For debug
        return;
    }

    // Default action: press the keycode
    Keyboard.press(pressedKeyCode);
  }
}

void keyReleased(Key* key, LayoutKey* layout) {
  // int code = layout->code; // This is the code from the CURRENT layout, which might have changed.
  uint8_t row = key->row;
  uint8_t col = key->column;

  // IMPORTANT: Use the key code that was active when the key was PRESSED,
  // not the one from the current layout, as the layout might have changed.
  LayoutKey* originallyPressedKey = physicalKeyStates[row][col].activeKey;
  uint16_t releasedKeyCode = originallyPressedKey ? originallyPressedKey->code : KEY_NULL; // Default to NUL if no active key was stored

  #if EDGE_DEBUG
  Serial.print("Key released: row="); Serial.print(row);
  Serial.print(", col="); Serial.print(col);
  Serial.print(", originallyPressedKeyCode="); Serial.print(releasedKeyCode, HEX);
  if (layout && layout->code != releasedKeyCode) {
    Serial.print(", currentLayoutCode="); Serial.print(layout->code, HEX);
  }
  Serial.println();
  #endif

  // Clear the key state tracking for this physical key FIRST.
  physicalKeyStates[row][col].isPressed = false;
  physicalKeyStates[row][col].activeCode = 0; // Clear the code too
  physicalKeyStates[row][col].activeKey = nullptr; // Clear the pointer

  bool keyActionTaken = false; // To decide if Keyboard.release(releasedKeyCode) should be called

  // --- Handle Layer Deactivations ---
  for (size_t i = 0; i < activeLayers.size(); ++i) { // Use size_t and activeLayers.size()
    Layer* currentLayer = &activeLayers[i];
    bool isActivationKeyRelease = false;
    for(uint8_t k=0; k < currentLayer->numActivationKeys; ++k) {
        if (currentLayer->activationKeys[k] == releasedKeyCode) {
            isActivationKeyRelease = true;
            break;
        }
    }

    if (isActivationKeyRelease) {
      // keyActionTaken = true; // Releasing a layer key itself usually means it was consumed.
      updateNeeded = true;

      switch (currentLayer->activationType) {
        case LayerActivationType::SINGLE_PRESS:
          currentLayer->isActive = false;
          #if EDGE_DEBUG
          // Serial.print("Layer deactivated (SINGLE_PRESS release): "); Serial.println(currentLayer->name);
          Serial.print("Layer deactivated (SINGLE_PRESS release): Index "); Serial.println(i);
          #endif
          keyActionTaken = true;
          break;
        case LayerActivationType::COMBO_PRESS:
          // If any key in a combo is released, the combo layer deactivates.
          currentLayer->isActive = false;
          #if EDGE_DEBUG
          // Serial.print("Layer deactivated (COMBO_PRESS release): "); Serial.println(currentLayer->name);
          Serial.print("Layer deactivated (COMBO_PRESS release): Index "); Serial.println(i);
          #endif
          keyActionTaken = true;
          break;
        case LayerActivationType::DOUBLE_TAP_HOLD:
          if (currentLayer->isActive) { // Only deactivate if it was successfully activated
            currentLayer->isActive = false;
            #if EDGE_DEBUG
            // Serial.print("Layer deactivated (DOUBLE_TAP_HOLD release): "); Serial.println(currentLayer->name);
            Serial.print("Layer deactivated (DOUBLE_TAP_HOLD release): Index "); Serial.println(i);
            #endif
          }
          // Reset tap states regardless, in case it was a partial tap
          currentLayer->waitingForSecondTap = false;
          currentLayer->tapCount = 0;
          keyActionTaken = true;
          break;
        case LayerActivationType::TOGGLE:
           // If activation key is also the deactivation key (toggleOffKey)
          if (currentLayer->toggleOffKey == releasedKeyCode && !currentLayer->isActive) {
             // This case could be for a "press to toggle on, press again to toggle off"
             // but current keyPressed handles the toggle. If toggleOffKey is different,
             // this is where it would be handled. For now, no action on release for basic toggles.
          }
          // For toggles, the key release itself doesn't usually change the layer state
          // unless it's a specific "toggle-off" key that's different from "toggle-on".
          // The current plan has toggle-on and toggle-off via the same key press.
          // However, we mark keyActionTaken = true because the press action was a layer action.
          keyActionTaken = true;
          break;
        case LayerActivationType::DOUBLE_TAP_TOGGLE:
          // Similar to TOGGLE, release does not change state after activation.
          // Reset tap states if it was a partial tap that didn't complete.
          if (currentLayer->waitingForSecondTap) { // If release happened before second tap
             // currentLayer->waitingForSecondTap = false; // This is handled by timeout or next press
             // currentLayer->tapCount = 0;
          }
          keyActionTaken = true; // The press was a layer action.
          break;
        default:
          break;
      }
    }
  }

  // --- Handle Specific Key Toggle Releases (usually no state change on release) ---
  if (releasedKeyCode == KEY_ALTL || releasedKeyCode == KEY_ALTR ||
      releasedKeyCode == KEY_CAPS_SLASH || releasedKeyCode == KEY_CAPS_ESC) {
    keyActionTaken = true; // These keys manage state on press, release is handled by default HID release
  } else if (releasedKeyCode == LAYER_0) { // Layer 0 Override Key
    layer0_override_active = false;
    updateNeeded = true;
    keyActionTaken = true;
    #if EDGE_DEBUG
    Serial.println("LAYER_0 key released - override INACTIVE");
    #endif
  } else if (releasedKeyCode == LOOP_COUNT) {
      keyActionTaken = true; // Consumed by press
  }


  // --- Fallback to other key release actions ---
  if (!keyActionTaken) {
    if (releasedKeyCode == KEY_NULL) { return; } // Should have been caught by activeKey check
    // if (macroManager.isMacroKey(releasedKeyCode)) { return; } // Removed: isMacroKey not a member.
    // Macros executed by executeMacro in keyPressed are often single-shot or self-managing for releases.

    // Brightness, Trill, System keys are typically momentary or handled by press
    // Check if it's one of those to avoid sending Keyboard.release if not needed
    bool isControlKey = false;
    for (uint8_t i = 0; i < sizeof(brightnessLevels) / sizeof(BrightnessLevel); i++) {
        if (releasedKeyCode == brightnessLevels[i].code) { isControlKey = true; break;}
    }
    if (releasedKeyCode == LEDS_INC || releasedKeyCode == LEDS_DEC ||
        releasedKeyCode == TRILL_MODE1 || releasedKeyCode == TRILL_MODE2 || releasedKeyCode == TRILL_MODE3 ||
        releasedKeyCode == KEY_RELEASE || releasedKeyCode == KEY_REBOOT || releasedKeyCode == KEY_SET0) {
        isControlKey = true;
    }
     for (uint8_t i = 0; i < sizeof(shiftedKeys) / sizeof(SimpleKeyAction); i++) { // Shifted keys are also single shot
        if (releasedKeyCode == shiftedKeys[i].code) {isControlKey = true; break;}
    }

    if (isControlKey) return;


    // Mouse buttons
    if (releasedKeyCode == MOUSE_LCLICK || releasedKeyCode == MOUSE_RCLICK) {
      Mouse.set_buttons(0,0,0); return;
    }

    // Alt-Tab: release the ALT key
    if (releasedKeyCode == KEY_ALT_TAB) {
        Keyboard.release(KEY_LEFT_ALT);
        // L2AltTab = false; // Reset if this mechanism is reused
        return;
    }

    // Default action: release the key that was originally pressed
    Keyboard.release(releasedKeyCode);
  }
}

#endif
