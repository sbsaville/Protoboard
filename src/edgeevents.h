#ifndef EDGEEVENTS_H
#define EDGEEVENTS_H

#include "main.h"
#include "layers.h"
#include "trillbar.h"
#include "keydefs.h"
#include "rgbleds.h"
#include "sdconfig.h"
#include "macros.h"

#if DEBUG
  #define EDGE_DEBUG 0
#endif

extern KeyMapEntry (*currentLayout)[columnsCount];

extern bool ALT_L;
extern bool ALT_R;
extern bool CAPS_SLSH;
extern bool CAPS_ESC;

bool L2AltTab = false; // Specific state for Alt-Tab behavior, might need review

// For Key-Specific Double Taps (like RShift -> CapsLock)
// These are now global within the compilation unit (Protoboard.cpp via include)
int key_specific_dt_candidate_row = -1;
int key_specific_dt_candidate_col = -1;
unsigned long key_specific_dt_press_time = 0;

// static int last_double_tap_candidate_row = -1; // Will be part of Layer struct or managed differently
// static int last_double_tap_candidate_col = -1; // "
// static unsigned long last_double_tap_press_time = 0; // "

extern bool loopTimer;

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

void pressHyper() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
};

void releaseHyper() {
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_LEFT_SHIFT);
  Keyboard.release(KEY_LEFT_GUI);
};

void pressMeh() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
};

void releaseMeh() {
  Keyboard.release(KEY_LEFT_ALT);
  Keyboard.release(KEY_LEFT_CTRL);
  Keyboard.release(KEY_LEFT_SHIFT);
};

struct MouseMovementState {
  bool up = false;
  bool down = false;
  bool left = false;
  bool right = false;
  
  bool upHeld = false;
  bool downHeld = false;
  bool leftHeld = false;
  bool rightHeld = false;
  
  unsigned long lastUpTime = 0;
  unsigned long lastDownTime = 0;
  unsigned long lastLeftTime = 0;
  unsigned long lastRightTime = 0;
} mouseState;

unsigned long lastMouseMoveTime = 0;
const unsigned long MOUSE_MOVE_INTERVAL = 2;

void startMouseMovement(int direction) {
  unsigned long now = millis();
  
  switch(direction) {
    case MOUSE_MOVE_UP:
      mouseState.upHeld = true;
      mouseState.up = true;
      mouseState.lastUpTime = now;
      if (mouseState.downHeld && mouseState.lastDownTime < now) {
        mouseState.down = false; // SOCD: up beats down
      }
      break;
    case MOUSE_MOVE_DOWN:
      mouseState.downHeld = true;
      mouseState.down = true;
      mouseState.lastDownTime = now;
      if (mouseState.upHeld && mouseState.lastUpTime < now) {
        mouseState.up = false; // SOCD: down beats up
      }
      break;
    case MOUSE_MOVE_LEFT:
      mouseState.leftHeld = true;
      mouseState.left = true;
      mouseState.lastLeftTime = now;
      if (mouseState.rightHeld && mouseState.lastRightTime < now) {
        mouseState.right = false; // SOCD: left beats right
      }
      break;
    case MOUSE_MOVE_RIGHT:
      mouseState.rightHeld = true;
      mouseState.right = true;
      mouseState.lastRightTime = now;
      if (mouseState.leftHeld && mouseState.lastLeftTime < now) {
        mouseState.left = false; // SOCD: right beats left
      }
      break;
  }
}

void stopMouseMovement(int direction) {
  switch(direction) {
    case MOUSE_MOVE_UP: 
      mouseState.upHeld = false;
      mouseState.up = false;
      if (mouseState.downHeld) {
        mouseState.down = true;
      }
      break;
    case MOUSE_MOVE_DOWN: 
      mouseState.downHeld = false;
      mouseState.down = false;
      if (mouseState.upHeld) {
        mouseState.up = true;
      }
      break;
    case MOUSE_MOVE_LEFT: 
      mouseState.leftHeld = false;
      mouseState.left = false;
      if (mouseState.rightHeld) {
        mouseState.right = true;
      }
      break;
    case MOUSE_MOVE_RIGHT: 
      mouseState.rightHeld = false;
      mouseState.right = false;
      if (mouseState.leftHeld) {
        mouseState.left = true;
      }
      break;
  }
}

void updateMouseMovement() {
  if (millis() - lastMouseMoveTime >= MOUSE_MOVE_INTERVAL) {
    int deltaX = 0, deltaY = 0;
    
    if (mouseState.left) deltaX -= 1;
    if (mouseState.right) deltaX += 1;
    if (mouseState.up) deltaY -= 1;
    if (mouseState.down) deltaY += 1;
    
    if (deltaX != 0 || deltaY != 0) {
      Mouse.move(deltaX, deltaY);
    }
    
    lastMouseMoveTime = millis();
  }
}

struct BrightnessLevel {
  int code;
  int brightnessValue;
};

struct SimpleKeyAction {
  int code;
  int keyToPress;
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
  {EXCLMAMATION,   KEY_1},
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
  LayoutKey* keySpecificDoubleTapKey = currentKeyMapEntry.doubleTapKey;

  if (primaryKey == nullptr) primaryKey = NUL; // Ensure primaryKey is never null

  int pressedKeyCode = primaryKey->code; // This is the code for the primary key function

  physicalKeyStates[row][col].isPressed = true;
  physicalKeyStates[row][col].activeCode = pressedKeyCode;
  physicalKeyStates[row][col].activeKey = primaryKey;

  bool keyActionTaken = false;
  unsigned long now = millis();

  // --- Handle Key-Specific Double-Tap ---
  // Check if the current key press completes a pending key-specific double-tap
  if (key_specific_dt_candidate_row == row &&
      key_specific_dt_candidate_col == col &&
      (now - key_specific_dt_press_time) < DOUBLE_TAP_WINDOW) {

    // currentKeyMapEntry is for the *second* press. We need the KME of the *first* press (candidate)
    // to get its doubleTapKey. However, they are the same physical key, so currentKeyMapEntry is fine.
    if (keySpecificDoubleTapKey != nullptr && keySpecificDoubleTapKey->code != KEY_NULL) {
        #if EDGE_DEBUG
        Serial.print("Key-specific double-tap COMPLETED! Key at [");
        Serial.print(row); Serial.print("]["); Serial.print(col);
        Serial.print("] ("); Serial.print(primaryKey->code, HEX); Serial.print(")");
        Serial.print(" -> DT Key: "); Serial.println(keySpecificDoubleTapKey->code, HEX);
        #endif

        Keyboard.press(keySpecificDoubleTapKey->code);
        Keyboard.release(keySpecificDoubleTapKey->code);
        keyActionTaken = true; // Double-tap action performed, consume the event.
    }
    // Always reset candidate after a second press, regardless of whether it had a DT action or not
    key_specific_dt_candidate_row = -1;
    key_specific_dt_candidate_col = -1;
    key_specific_dt_press_time = 0;
  } else {
    // Not a second tap completion. Check if this current key press is a *first* tap for a new sequence.
    if (keySpecificDoubleTapKey != nullptr && keySpecificDoubleTapKey->code != KEY_NULL) {
      // This key *can* start a double-tap sequence.
      key_specific_dt_candidate_row = row;
      key_specific_dt_candidate_col = col;
      key_specific_dt_press_time = now;
      #if EDGE_DEBUG
      Serial.print("Key-specific double-tap INITIATED. Candidate: [");
      Serial.print(row); Serial.print("]["); Serial.print(col);
      Serial.print("] ("); Serial.print(primaryKey->code, HEX); Serial.print(")");
      Serial.println();
      #endif
      // For the first tap, keyActionTaken remains false. Its primary action will proceed.
    } else {
      // This key cannot start a double-tap sequence (no doubleTapKey defined for it).
      // Clear any pending candidate from a *different* key.
      key_specific_dt_candidate_row = -1;
      key_specific_dt_candidate_col = -1;
      key_specific_dt_press_time = 0;
    }
  }

  // --- Handle Layer Activations and Toggles (only if not handled by a completed key-specific DT)---
  if (!keyActionTaken) {
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
          if (currentLayer->isActive && pressedKeyCode == currentLayer->activationKeys[0] && !currentLayer->waitingForSecondTap && !currentLayer->awaitingSecondTapRelease) {
            // Layer is ON, and this is a new, single press of its activation key (not part of an ongoing DT sequence)
            currentLayer->isActive = false; // Toggle OFF
            currentLayer->tapCount = 0;     // Reset tap count
             #if EDGE_DEBUG
            Serial.print("Layer DEactivated by single press (DT_TOGGLE): Index "); Serial.println(i);
            #endif
          } else if (currentLayer->waitingForSecondTap && (now - currentLayer->lastTapTime) < DOUBLE_TAP_WINDOW && pressedKeyCode == currentLayer->activationKeys[0]) {
            // This is the SECOND PRESS of a double tap sequence
            currentLayer->isActive = true; // Activate the layer
            currentLayer->waitingForSecondTap = false;
            currentLayer->awaitingSecondTapRelease = true; // Now waiting for the release of this second tap
            currentLayer->lastTapTime = now; // Record time of this second press for hold duration check
            currentLayer->tapCount = 2; // Mark as 2nd tap processed
            #if EDGE_DEBUG
            Serial.print("Layer ACTIVE, awaiting 2nd tap release (DT_TOGGLE): Index "); Serial.println(i);
            #endif
          } else if (!currentLayer->isActive && !currentLayer->awaitingSecondTapRelease) {
            // This is the FIRST PRESS of a double tap sequence (layer is off, not already awaiting release of 2nd tap)
            currentLayer->waitingForSecondTap = true;
            currentLayer->lastTapTime = now; // Record time of this first press
            currentLayer->tapCount = 1;
            #if EDGE_DEBUG
            Serial.print("Layer waiting for 2nd tap (DT_TOGGLE): Index "); Serial.println(i);
            #endif
          }
          // Note: if currentLayer->awaitingSecondTapRelease is true, a new press of the same key before release is ignored here.
          // It will be handled by keyReleased or timeout.
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
        sdconfig::saveBrightness(brightness); // Save on change
        leds0();
        return;
      }
    }
    if (pressedKeyCode == LEDS_INC) { rgbleds::ledsINC(); leds0(); return; }
    if (pressedKeyCode == LEDS_DEC) { rgbleds::ledsDEC(); leds0(); return; }

    if (pressedKeyCode == TRILL_MODE1) { trillbar::setMode(trillbar::MODE_ARROWS); return; }
    if (pressedKeyCode == TRILL_MODE2) { trillbar::setMode(trillbar::MODE_SCROLL); return; }
    if (pressedKeyCode == TRILL_MODE3) { trillbar::setMode(trillbar::MODE_BRIGHTNESS); return; }

    if (pressedKeyCode == MOUSE_LCLICK) { Mouse.set_buttons(1,0,0); return;}
    if (pressedKeyCode == MOUSE_LCLICK) { Mouse.set_buttons(0,1,0); return;}
    if (pressedKeyCode == MOUSE_RCLICK) { Mouse.set_buttons(0,0,1); return;}

    if (pressedKeyCode == MOUSE_MOVE_UP || pressedKeyCode == MOUSE_MOVE_DOWN || 
        pressedKeyCode == MOUSE_MOVE_LEFT || pressedKeyCode == MOUSE_MOVE_RIGHT) {
      startMouseMovement(pressedKeyCode);
      return;
    }

    if (pressedKeyCode == KEY_RELEASE) { Keyboard.releaseAll(); return; }
    if (pressedKeyCode == KEY_REBOOT) { _reboot_Teensyduino_(); return; }

    if (pressedKeyCode == KEY_ALT_TAB) {
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.send_now();
      Keyboard.press(KEY_TAB);
      Keyboard.release(KEY_TAB);
      L2AltTab = true;
      return; 
    }

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
        Keyboard.releaseAll();
        updateNeeded = true;
        L_check(); // For debug
        return;
    }

    switch (pressedKeyCode) {
      case KEY_HYPER:
        pressHyper();
        keyActionTaken = true;
        break;
      case KEY_MEH:
        pressMeh();
        keyActionTaken = true;
        break;
    }

    // Default action: press the keycode
    Keyboard.press(pressedKeyCode);
  }
} // End of if(!keyActionTaken)
} // End of keyPressed function - THIS IS THE INTENDED FIX

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
          if (releasedKeyCode == LAYER_2 && L2AltTab) {
            Keyboard.release(KEY_LEFT_ALT);
            L2AltTab = false;
          }
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
          if (currentLayer->awaitingSecondTapRelease && releasedKeyCode == currentLayer->activationKeys[0]) {
            // This is the release of the second tap
            currentLayer->awaitingSecondTapRelease = false;
            unsigned long holdDuration = millis() - currentLayer->lastTapTime; // lastTapTime was set at 2nd press

            if (holdDuration >= DOUBLE_TAP_WINDOW) { // Held longer than the window (or your DT_CONFIRM_WINDOW)
              currentLayer->isActive = false; // Deactivate (momentary behavior)
              #if EDGE_DEBUG
              Serial.print("Layer DEactivated (DT_TOGGLE, long hold on 2nd tap): Index "); Serial.println(i);
              #endif
            } else {
              // Short release, layer remains active (toggled ON)
              #if EDGE_DEBUG
              Serial.print("Layer REMAINS active (DT_TOGGLE, short release on 2nd tap): Index "); Serial.println(i);
              #endif
            }
            currentLayer->tapCount = 0; // Reset tap count
            keyActionTaken = true;
          } 
          else if (currentLayer->waitingForSecondTap && releasedKeyCode == currentLayer->activationKeys[0]) {
            // This is the release of the FIRST tap.
            // waitingForSecondTap remains true, timeout will handle it if no second tap comes.
            // Or next press will check it.
            // No change in isActive state here.
            keyActionTaken = true; // The press was a layer action.
          } 
          else {
            // This release is not part of an active DT sequence for this layer,
            // but if the layer is active and this is its activation key,
            // the press might have turned it off.
             keyActionTaken = true; // The press was a layer action.
          }
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
  } 
  else if (releasedKeyCode == LAYER_0) { // Layer 0 Override Key
    layer0_override_active = false;
    updateNeeded = true;
    keyActionTaken = true;
    #if EDGE_DEBUG
    Serial.println("LAYER_0 key released - override INACTIVE");
    #endif
  } 
  else if (releasedKeyCode == LOOP_COUNT) {
      keyActionTaken = true; // Consumed by press
  } 
  else if (releasedKeyCode == KEY_HYPER) {
    releaseHyper();
    keyActionTaken = true;
  } 
  else if (releasedKeyCode == KEY_MEH) {
    releaseMeh(); 
    keyActionTaken = true;
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

    if (releasedKeyCode == MOUSE_LCLICK || releasedKeyCode == MOUSE_RCLICK || releasedKeyCode == MOUSE_MCLICK) {
      Mouse.set_buttons(0,0,0); return;
    }

    if (releasedKeyCode == MOUSE_MOVE_UP || releasedKeyCode == MOUSE_MOVE_DOWN || 
        releasedKeyCode == MOUSE_MOVE_LEFT || releasedKeyCode == MOUSE_MOVE_RIGHT) {
      stopMouseMovement(releasedKeyCode);
      return;
    }

    Keyboard.release(releasedKeyCode);
  }
}

#endif
