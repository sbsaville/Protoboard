#include <Arduino.h>
#include <Trill.h>
#include <Mouse.h>
#include <cstdint>

#include "main.h"
#include "rgbleds.h"
#include "layers.h"
#include "trillbar.h"
#include "config.h"
#include "macros.h"

#define DEBUG 0
#define LOOP_TIMER_DEBUG 0

#define DEBOUNCE_TIME 8  // milliseconds
#define DOUBLE_TAP_WINDOW 200 // milliseconds

unsigned long debounceTimers[rowsCount][columnsCount] = {0};

// --- Layer Management ---
// Array to hold all defined layers
// The order matters: higher index layers have higher priority if multiple are active.
// Layer 0 is handled implicitly as the default.
#define MAX_LAYERS 10 // Maximum number of configurable layers (excluding layer 0)
Layer activeLayers[MAX_LAYERS];
uint8_t definedLayerCount = 0; // Number of layers actually defined in activeLayers

// --- End Layer Management ---

// Global state flags for specific key behaviors (not directly layer toggles)
// These are modified by edgeevents.h (keyPressed/keyReleased)
bool ALT_R_active = 0;
bool ALT_L_active = 0;
bool CAPS_SLSH_toggled = 0;
bool CAPS_ESC_toggled = 0;

// This is also modified by edgeevents.h
bool layer0_override_active = false;


unsigned long loopStartTime = 0;
unsigned long loopDuration = 0;
bool loopTimer = false;

// Matrix to track physical key states across layer changes
PhysicalKeyState physicalKeyStates[rowsCount][columnsCount];

// Define the actual storage for the working layer0 map
KeyMapEntry layer0[rowsCount][columnsCount];
KeyMapEntry (*currentLayout)[columnsCount] = layer0; // currentLayout will point to the working layer0

Key keys[rowsCount][columnsCount] = {
 {{0, 0, false},{0, 1, false},{0, 2, false},{0, 3, false},{0, 4, false},{0, 5, false},{0, 6, false},{0, 7, false},{0, 8, false},{0, 9, false},{0, 10, false},{0, 11, false},{0, 12, false},{0, 13, false}},
 {{1, 0, false},{1, 1, false},{1, 2, false},{1, 3, false},{1, 4, false},{1, 5, false},{1, 6, false},{1, 7, false},{1, 8, false},{1, 9, false},{1, 10, false},{1, 11, false},{1, 12, false},{1, 13, false}},
 {{2, 0, false},{2, 1, false},{2, 2, false},{2, 3, false},{2, 4, false},{2, 5, false},{2, 6, false},{2, 7, false},{2, 8, false},{2, 9, false},{2, 10, false},{2, 11, false},{2, 12, false},{2, 13, false}},
 {{3, 0, false},{3, 1, false},{3, 2, false},{3, 3, false},{3, 4, false},{3, 5, false},{3, 6, false},{3, 7, false},{3, 8, false},{3, 9, false},{3, 10, false},{3, 11, false},{3, 12, false},{3, 13, false}},
 {{4, 0, false},{4, 1, false},{4, 2, false},{4, 3, false},{4, 4, false},{4, 5, false},{4, 6, false},{4, 7, false},{4, 8, false},{4, 9, false},{4, 10, false},{4, 11, false},{4, 12, false},{4, 13, false}},
 {{5, 0, false},{5, 1, false},{5, 2, false},{5, 3, false},{5, 4, false},{5, 5, false},{5, 6, false},{5, 7, false},{5, 8, false},{5, 9, false},{5, 10, false},{5, 11, false},{5, 12, false},{5, 13, false}}
};

Key* getKey(uint8_t row, uint8_t column) {
  return &keys[row][column];
}

LayoutKey* getLayoutKey(uint8_t row, uint8_t column) {
  // Return the primary key from the KeyMapEntry
  // Add null check for safety, though ideally entries always have a primaryKey (even if it's NUL)
  KeyMapEntry entry = currentLayout[row][column];
  if (entry.primaryKey == nullptr) {
    // This case should ideally not happen if layouts are defined correctly.
    // Return a pointer to the NUL key definition as a safe default.
    return NUL;
  }
  return entry.primaryKey;
}

// Function to initialize the key tracking matrix
void initKeyTrackingMatrix() {
  for (uint8_t i = 0; i < rowsCount; i++) {
    for (uint8_t j = 0; j < columnsCount; j++) {
      physicalKeyStates[i][j].isPressed = false;
      physicalKeyStates[i][j].activeCode = 0;
      physicalKeyStates[i][j].activeKey = nullptr;
    }
  }
}

void sendKeys() {
    Keyboard.send_now();
}

// Layer key diagnostic tool

void L_check() {
  #if DEBUG
  Serial.println("Layer States:");
  for (uint8_t i = 0; i < definedLayerCount; ++i) {
    Serial.print(activeLayers[i].name);
    Serial.print(" (");
    Serial.print(activeLayers[i].isActive ? "Active" : "Inactive");
    if (activeLayers[i].activationType == LayerActivationType::DOUBLE_TAP_HOLD || activeLayers[i].activationType == LayerActivationType::DOUBLE_TAP_TOGGLE) {
        Serial.print(", Taps: "); Serial.print(activeLayers[i].tapCount);
        Serial.print(", Waiting: "); Serial.print(activeLayers[i].waitingForSecondTap);
    }
    Serial.print("), Key(s): ");
    for(int k=0; k < activeLayers[i].numActivationKeys; ++k) {
        Serial.print(activeLayers[i].activationKeys[k], HEX);
        if (k < activeLayers[i].numActivationKeys -1) Serial.print(" + ");
    }
    Serial.println("");
  }
  Serial.print("CAPS_SLSH_toggled="); Serial.print(CAPS_SLSH_toggled); Serial.print(" ");
  Serial.print("CAPS_ESC_toggled=");  Serial.print(CAPS_ESC_toggled);  Serial.println("");
  #endif
}


static unsigned long lastTime = 0;        // For keyboard scanning
static unsigned long lastLayerTime = 0;   // For layer updates
static bool updateNeeded = false;

// Function to add layers to the activeLayers array
void addLayer(const char* name, KeyMapEntry (*keymap)[columnsCount], LayerActivationType type, std::initializer_list<uint16_t> keys, uint16_t offKey = 0) {
    if (definedLayerCount < MAX_LAYERS) {
        activeLayers[definedLayerCount++] = Layer(name, keymap, type, keys, offKey);
    } else {
        // Handle error: too many layers defined
        #if DEBUG
        Serial.println("Error: Maximum number of layers reached. Cannot add more.");
        #endif
    }
}

void setup() {
  // Initialize layers
  // Note: The order of definition determines priority in getActiveLayout if multiple layers could be active.
  // Higher index in activeLayers means higher priority.
  // For now, order is similar to old L_ flag checks.
  // Higher index = higher priority. Double-tap layers should probably have high priority.

  // Base momentary layers
  addLayer("Layer1", layer1, LayerActivationType::SINGLE_PRESS, {LAYER_1}); // Key: LYR1
  addLayer("Layer2", layer2, LayerActivationType::SINGLE_PRESS, {LAYER_2}); // Key: LYR2 (momentary)
  addLayer("Layer3", layer3, LayerActivationType::SINGLE_PRESS, {LAYER_3}); // Key: LYR3 (momentary)
  addLayer("Layer4", layer4, LayerActivationType::SINGLE_PRESS, {LAYER_4}); // Key: LYR4

  // Double-tap toggle layers - these should have higher priority than the single-press layers they are attached to.
  // So, define them after the single-press versions if their trigger keys are the same.
  // However, the current getActiveLayout iterates from highest index down, so order of addLayer matters.
  // To make DT layers override, they should be added *later* (higher index).

  // Renamed layers as per request:
  // Original layer1_2 keymap is now layout2DT, triggered by double-tapping LAYER_2 key.
  // For DOUBLE_TAP_TOGGLE, the activationKey[0] is also the toggleOffKey by default.
  addLayer("layout2DT", layer1_2, LayerActivationType::DOUBLE_TAP_TOGGLE, {LAYER_2});

  // Original layer3_4 keymap is now layout3DT, triggered by double-tapping LAYER_3 key.
  addLayer("layout3DT", layer3_4, LayerActivationType::DOUBLE_TAP_TOGGLE, {LAYER_3});

  // Removing old combo/toggle layers that are being replaced or are not specified to be kept:
  // addLayer("Layer1_2_Combo", layer1_2, LayerActivationType::COMBO_PRESS, {LAYER_1, LAYER_2}); // Old L1+L2 combo
  // addLayer("Layer1_2_Toggle", layer1_2, LayerActivationType::TOGGLE, {LAYER_1_2L}); // Old L_1_2L toggle
  // addLayer("Layer2_3_Combo", layer2_3, LayerActivationType::COMBO_PRESS, {LAYER_2, LAYER_3}); // Old L2+L3 combo

  // LYR0 for layer0 override is handled directly in keyPressed/keyReleased.

  Keyboard.begin();
  Mouse.begin();
  Serial.begin(115200);

  // Initialize the key tracking matrix
  initKeyTrackingMatrix();

  memcpy(layer0, layer0_default, sizeof(layer0_default));

  delay(1000);

  for (uint8_t j=0; j<columnsCount; j++) {
    pinMode(columns[j], INPUT_PULLUP);
  }

  for (uint8_t i=0; i<rowsCount; i++) {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], HIGH);
  }

  // Initialize SD card for config storage
  Config::init();

  // Initialize macro system
  initializeMacros();

  trillbar::setup();
  rgbleds::setup();
}

// Global flag to force layer 0 (e.g. via a specific key press)
bool layer0_override_active = false;

KeyMapEntry (*getActiveLayout())[columnsCount] {
    KeyMapEntry (*selectedLayout)[columnsCount] = layer0; // Default to layer0
    // int highestPriorityActiveLayer = -1; // Not strictly needed here but good for debugging

    if (layer0_override_active) {
        trillbar::setMode(trillbar::MODE_ARROWS); // Default for layer0
        #if DEBUG
        Serial.println("getActiveLayout: Layer 0 override active.");
        #endif
        return layer0;
    }

    // Iterate from highest priority to lowest (higher index in activeLayers array = higher priority)
    for (int i = definedLayerCount - 1; i >= 0; --i) {
        if (activeLayers[i].isActive) {
            selectedLayout = activeLayers[i].keymap;
            // highestPriorityActiveLayer = i; // For debugging
            #if DEBUG
            Serial.print("getActiveLayout: Active layer found: "); Serial.println(activeLayers[i].name);
            #endif

            // TODO: This trillbar mode setting needs to be more robust.
            // Maybe add a trillbarMode field to the Layer struct.
            if (strcmp(activeLayers[i].name, "Layer1") == 0 || strcmp(activeLayers[i].name, "Layer4") == 0) {
                trillbar::setMode(trillbar::MODE_BRIGHTNESS);
            } else if (strcmp(activeLayers[i].name, "Layer2") == 0) {
                trillbar::setMode(trillbar::MODE_SCROLL);
            } else if (strcmp(activeLayers[i].name, "Layer1_2") == 0 || strcmp(activeLayers[i].name, "Layer1_2_Toggle") == 0) {
                trillbar::setMode(trillbar::MODE_ARROWS);
            } else {
                trillbar::setMode(trillbar::MODE_ARROWS); // Default for other layers or unhandled ones
            }
            return selectedLayout; // Return the highest priority active layer found
        }
    }

    // If no other layer is active, layer0 is used
    #if DEBUG
    Serial.println("getActiveLayout: No specific layer active, defaulting to Layer 0.");
    #endif
    trillbar::setMode(trillbar::MODE_ARROWS); // Default for layer0
    return layer0;
}

#include "edgeevents.h" // This will likely need heavy modifications for the new layer system

// Helper function to check if a key is involved in ANY layer's activation or deactivation
bool isLayerActivationKey(uint16_t code) {
    if (code == LAYER_0) return true; // Layer 0 override key is always a layer activation key

    for (uint8_t i = 0; i < definedLayerCount; ++i) {
        for (uint8_t k = 0; k < activeLayers[i].numActivationKeys; ++k) {
            if (activeLayers[i].activationKeys[k] == code) {
                return true;
            }
        }
        // Also check toggleOffKey if it's different and relevant for the layer type
        if ((activeLayers[i].activationType == LayerActivationType::TOGGLE ||
             activeLayers[i].activationType == LayerActivationType::DOUBLE_TAP_TOGGLE) &&
            activeLayers[i].toggleOffKey != 0 && activeLayers[i].toggleOffKey == code) {
            // Only return true if it's not already covered by activationKeys,
            // or if it's explicitly meant to be an off key that's different.
            // For simplicity now, if it's a toggleOffKey, consider it an activation key.
            return true;
        }
    }
    return false;
}

/**
 * Test function to verify key preservation across layer changes
 * This helps debug the key preservation system by showing currently pressed keys
 */
void testKeyPreservation() {
  #if DEBUG
  Serial.println("Key preservation test:");

  // Check for any currently pressed keys
  for (uint8_t i = 0; i < rowsCount; i++) {
    for (uint8_t j = 0; j < columnsCount; j++) {
      if (physicalKeyStates[i][j].isPressed) {
        Serial.print("Key pressed at [");
        Serial.print(i);
        Serial.print("][");
        Serial.print(j);
        Serial.print("]: code=");

        if (physicalKeyStates[i][j].activeKey) {
          Serial.print(physicalKeyStates[i][j].activeKey->code);
          Serial.print(", color=0x");
          uint32_t color = ((uint32_t)physicalKeyStates[i][j].activeKey->ledColor->r << 16) |
                           ((uint32_t)physicalKeyStates[i][j].activeKey->ledColor->g << 8) |
                           physicalKeyStates[i][j].activeKey->ledColor->b;
          Serial.println(color, HEX);
        } else {
          Serial.println("NULL activeKey");
        }
      }
    }
  }
  #endif
}

void updateLayerMappings() {
  KeyMapEntry (*newLayout)[columnsCount] = getActiveLayout();
  if (newLayout != currentLayout) {
    #if DEBUG
    Serial.println("Layout changed - updating key mappings");
    #endif
    currentLayout = newLayout;
  }
}

void remapKeys() {
  // Update base layer0 mappings based on toggle states
  layer0[5][4] = (ALT_L_active == 1) ? KeyMapEntry{LALT} : layer0_default[5][4];
  layer0[5][6] = (ALT_R_active == 1) ? KeyMapEntry{RALT} : layer0_default[5][6];
  layer0[0][13] = (ALT_R_active == 1) ? KeyMapEntry{BKSPC} : layer0_default[0][13]; // This seems like an odd remap for ALT_R, but keeping original logic
  layer0[3][0]  = (CAPS_SLSH_toggled == 1) ? KeyMapEntry{BSLSH} :
                   (CAPS_ESC_toggled == 1) ? KeyMapEntry{ESC} : layer0_default[3][0];

  // Update LED colors based on toggle states
  if (ALT_L_active == 1) {
    ALTL->ledColor = &Modifier; 
  } else {
    ALTL->ledColor = &ALTL->defaultColor; // Assuming LayoutKey struct has defaultColor
  }

  if (ALT_R_active == 1) {
    ALTR->ledColor = &Modifier;
  } else {
    ALTR->ledColor = &ALTR->defaultColor; // Assuming LayoutKey struct has defaultColor
  }

  if (CAPS_SLSH_toggled == 1) {
    // CAPS_ESC_toggled = 0; // Mutual exclusivity handled in keyPressed/keyReleased for these specific keys
    CAPSLSH->ledColor = &Toggle;
  } else {
    CAPSLSH->ledColor = &CAPSLSH->defaultColor; // Assuming LayoutKey struct has defaultColor
  }

  if (CAPS_ESC_toggled == 1) {
    // CAPS_SLSH_toggled = 0; // Mutual exclusivity handled in keyPressed/keyReleased
    CAPSESC->ledColor = &Chara1; // Or some other toggle indicator color
    // If ESC key itself should change color when this toggle is active:
    // ESC->ledColor = &Chara1; // This was in original, implies ESC key itself changes
  } else {
    CAPSESC->ledColor = &CAPSESC->defaultColor; // Assuming LayoutKey struct has defaultColor
    // ESC->ledColor = &ESC->defaultColor; // Reset ESC color if it was changed
  }
   // Ensure ESC key color is reset if CAPS_ESC is not active, but ESC is on base layer.
  if (!CAPS_ESC_toggled && layer0_default[0][0].primaryKey == ESC) {
    ESC->ledColor = &ESC->defaultColor;
  } else if (CAPS_ESC_toggled && layer0_default[3][0].primaryKey != ESC && layer0_default[0][0].primaryKey == ESC){
    // If CAPS_ESC is toggled, AND it remaps key (3,0) to ESC, then the original ESC key at (0,0) should also change color
     ESC->ledColor = &Chara1;
  }


}


void loop() {
  if (loopTimer) {
    loopStartTime = micros();
  }

  unsigned long now = millis();

  if (now - lastTime >= 1) {
    lastTime = now;

    for (uint8_t i = 0; i < rowsCount; i++) {
      digitalWrite(rows[i], LOW);
      delayMicroseconds(1); // this is needed on physical prototype V2 for some reason or keys one row down will be pressed at the same time

      for (uint8_t j = 0; j < columnsCount; j++) {
        uint8_t pin = columns[j];
        uint8_t port = digitalPinToPort(pin);
        volatile uint8_t* inputRegister = portInputRegister(port);
        uint8_t bitMask = digitalPinToBitMask(pin);

        Key* key = getKey(i, j);
        boolean current = !(*inputRegister & bitMask);
        boolean previous = key->pressed;

        if (current != previous) {
          if (now - debounceTimers[i][j] >= DEBOUNCE_TIME) {
            key->pressed = current;
            debounceTimers[i][j] = now;

            LayoutKey* layout = getLayoutKey(key->row, key->column);
            if (current) {
              keyPressed(key, layout);

              // Get the actual code that was stored during keyPressed
              uint16_t activeCode = physicalKeyStates[key->row][key->column].activeCode;

              // Set layer change flag if a layer key was pressed
              if (isLayerActivationKey(activeCode)) {
                  updateNeeded = true;
              }
            }
            else {
              keyReleased(key, layout);

              // Check both the current layout code and the stored activeCode for layer keys
              LayoutKey* activeKey = physicalKeyStates[key->row][key->column].activeKey;
              uint16_t actualCode = activeKey ? activeKey->code : layout->code;

              if (isLayerActivationKey(actualCode)) {
                  updateNeeded = true;
              }
            }
          }
        } else {
          // Reset debounce timer when state is stable
          debounceTimers[i][j] = now;
        }
      }

      // Deactivate the row when done
      digitalWrite(rows[i], HIGH);
    }
  }

  trillbar::loop();

  // Check for double-tap timeouts
  for (uint8_t i = 0; i < definedLayerCount; ++i) {
    if (activeLayers[i].waitingForSecondTap && (now - activeLayers[i].lastTapTime > DOUBLE_TAP_WINDOW)) {
      #if DEBUG || EDGE_DEBUG // Use EDGE_DEBUG if it's more specific for this kind of log
      Serial.print("Double tap timed out for layer: "); Serial.println(activeLayers[i].name);
      #endif
      activeLayers[i].waitingForSecondTap = false;
      activeLayers[i].tapCount = 0;
      updateNeeded = true; // May need to update LEDs if tap state changed visual feedback
    }
  }

  if (updateNeeded || (now - lastLayerTime >= 50)) { // Reduced interval for faster responsiveness, was 50
    lastLayerTime = now;
    updateNeeded = false;

    updateLayerMappings(); // This will call getActiveLayout()

    if (!trillbar::isLedOverride()) {
      scanLEDs(currentLayout); // currentLayout is updated by updateLayerMappings()
    }
    remapKeys(); // Update LEDs for toggles like ALT, CAPS_SLSH etc.

    #if DEBUG
    testKeyPreservation(); // Check physical key states
    L_check(); // Check layer states
    #endif
  }

  rgbleds::loop();

  if (loopTimer) {
    #if LOOP_TIMER_DEBUG
    loopDuration = micros() - loopStartTime;
    Serial.print("Loop: ");
    Serial.print(loopDuration);
    Serial.println(" µs");
    #endif
  }
}