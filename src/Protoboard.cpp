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
unsigned long debounceTimers[rowsCount][columnsCount] = {0};

bool L_0 = 0;  // only used for overrides, layout0 is default when no other layer flags are active - adding this note so Claude Sonnet stops mentioning it
bool L_1 = 0;
bool L_2 = 0;
bool L_3 = 0;
bool L_4 = 0;
bool L_1_2L = 0;
bool ALT_R = 0;
bool ALT_L = 0;
bool CAPS_SLSH = 0;
bool CAPS_ESC = 0;

unsigned long loopStartTime = 0;
unsigned long loopDuration = 0;
bool loopTimer = false;

// Matrix to track physical key states across layer changes
PhysicalKeyState physicalKeyStates[rowsCount][columnsCount];

LayoutKey* (*currentLayout)[columnsCount] = layout0;

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
  return currentLayout[row][column];
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
  Serial.print("L_0=");       Serial.print(L_0);        Serial.print(" ");
  Serial.print("L_1=");       Serial.print(L_1);        Serial.print(" ");
  Serial.print("L_2=");       Serial.print(L_2);        Serial.print(" ");
  Serial.print("L_3=");       Serial.print(L_3);        Serial.print(" ");
  Serial.print("L_4=");       Serial.print(L_4);        Serial.print(" ");
  Serial.print("L_1_2L=");    Serial.print(L_1_2L);     Serial.println("");
  #endif
}


static unsigned long lastTime = 0;        // For keyboard scanning
static unsigned long lastLayerTime = 0;   // For layer updates
static bool updateNeeded = false;

void setup() {

  Keyboard.begin();
  Mouse.begin();
  Serial.begin(115200);

  // Initialize the key tracking matrix
  initKeyTrackingMatrix();

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



LayoutKey* (*getActiveLayout())[columnsCount] {
  if (L_1 == 0 && L_2 == 0 && L_3 == 0 && L_4 == 0 && L_1_2L == 0) {
    trillbar::setMode(trillbar::MODE_ARROWS);
    return layout0;
  }
  else if (L_1 == 1 && L_2 == 0) {
    trillbar::setMode(trillbar::MODE_BRIGHTNESS);
    return layout1;
  }
  else if (L_1 == 0 && L_2 == 1 && L_3 == 0) {
    trillbar::setMode(trillbar::MODE_SCROLL);
    return layout2;
  }
  else if ((L_1 == 1 && L_2 == 1) || (L_1_2L == 1)) {
    trillbar::setMode(trillbar::MODE_ARROWS);
    return layout1_2;
  }
  else if (L_2 == 1 && L_3 == 1) {
    return layout2_3;
  }
  else if (L_3 == 1 && L_2 == 0 && L_4 == 0) {
    return layout3;
  }
  else if (L_3 == 1 && L_4 == 1) {
    return layout3_4;
  }
  else if (L_4 == 1) {
    trillbar::setMode(trillbar::MODE_BRIGHTNESS);
    return layout4;
  }
  return layout0;
}

#include "edgeevents.h"

// Helper function to check if a key is a layer switching key
bool isLayerKey(uint16_t code) {
  return (code == LAYER_0 || code == LAYER_1 || code == LAYER_2 ||
          code == LAYER_3 || code == LAYER_4 || code == LAYER_1_2L);
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

// Updates key mappings when changing layers while preserving physical key states
void updateLayerMappings() {
  // Get the current active layout
  LayoutKey* (*newLayout)[columnsCount] = getActiveLayout();

  // Only proceed if the layout has changed
  if (newLayout != currentLayout) {
    #if DEBUG
    Serial.println("Layout changed - updating key mappings");
    #endif

    // Generic key preservation system:
    // When a key is held during layer change, its original function is preserved
    // This is handled automatically by storing the original LayoutKey pointers
    // in physicalKeyStates when keys are first pressed

    // Update the current layout reference
    currentLayout = newLayout;
  }
}

void remapKeys() {
  // The generic key preservation system ensures that any keys pressed in one layer
  // retain their original function when changing to another layer, including LYR0
  // This works by tracking the original LayoutKey pointer when a key is first pressed

  // Handle toggle state changes (these still need to be applied)
  layout0[5][4] = (ALT_L == 1) ? LALT : LYR2;
  layout0[5][6] = (ALT_R == 1) ? RALT : BKSPC;
  layout0[0][13] = (ALT_R == 1) ? BKSPC : DEL;
  layout0[3][0]  = (CAPS_SLSH == 1) ? BSLSH :
                   (CAPS_ESC == 1) ? ESC : CAPS;
  if (ALT_L == 1) {
    ALTL->ledColor = &Modifier;
  } else {
    ALTL->ledColor = &ALTL->defaultColor;
  }
  if (ALT_R == 1) {
    ALTR->ledColor = &Modifier;
  } else {
    ALTR->ledColor = &ALTL->defaultColor;
  }
  if (CAPS_SLSH == 1) {
    CAPS_ESC = 0;
    CAPSLSH->ledColor = &Toggle;
  } else {
    CAPSLSH->ledColor = &ALTL->defaultColor;
  }
  if (CAPS_ESC == 1) {
    CAPS_SLSH = 0;
    CAPSESC->ledColor = &Toggle;
    ESC->ledColor = &Toggle;
  } else {
    CAPSESC->ledColor = &CAPSESC->defaultColor;
    ESC->ledColor = &ESC->defaultColor;
  }
}


void loop() {
  if (loopTimer) {
    loopStartTime = micros();
  }

  unsigned long now = millis();

  // Keyboard matrix scanning
  if (now - lastTime >= 1) {
    lastTime = now;

    for (uint8_t i = 0; i < rowsCount; i++) {
      // Activate the current row
      digitalWrite(rows[i], LOW);
      delayMicroseconds(1); // this is needed on physical prototype V2 for some reason or keys one row down will be pressed at the same time

      // Read all columns for the current row
      for (uint8_t j = 0; j < columnsCount; j++) {
        // Get correct port and bitmask for each individual column
        uint8_t pin = columns[j];
        uint8_t port = digitalPinToPort(pin);
        volatile uint8_t* inputRegister = portInputRegister(port);
        uint8_t bitMask = digitalPinToBitMask(pin);

        // Read the current key state
        Key* key = getKey(i, j);
        boolean current = !(*inputRegister & bitMask); // Active low logic
        boolean previous = key->pressed;

        // Only process state changes or update debounce timer
        if (current != previous) {
          if (now - debounceTimers[i][j] >= DEBOUNCE_TIME) {
            key->pressed = current;
            debounceTimers[i][j] = now;

            // Only fetch layout key if we need it (state changed and debounced)
            LayoutKey* layout = getLayoutKey(key->row, key->column);
              // Process the key event
            if (current) {
              keyPressed(key, layout);

              // Get the actual code that was stored during keyPressed
              uint16_t activeCode = physicalKeyStates[key->row][key->column].activeCode;

              // Set layer change flag if a layer key was pressed
              if (isLayerKey(activeCode)) {
                  updateNeeded = true;
              }
            }
            else {
              keyReleased(key, layout);

              // Check both the current layout code and the stored activeCode for layer keys
              LayoutKey* activeKey = physicalKeyStates[key->row][key->column].activeKey;
              uint16_t actualCode = activeKey ? activeKey->code : layout->code;

              if (isLayerKey(actualCode)) {
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

  // Process trill bar
  trillbar::loop();
    // Check if we need to update layouts due to layer changes
  if (updateNeeded || (now - lastLayerTime >= 50)) {
    lastLayerTime = now;
    updateNeeded = false;

    updateLayerMappings();

    // Always update LEDs when any flag changes
    if (!trillbar::isLedOverride()) {
      scanLEDs(currentLayout);
    }
    remapKeys();

    #if DEBUG
    // Test key preservation when layer changes
    testKeyPreservation();
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