#ifndef RGBLEDS_H
#define RGBLEDS_H
#define FASTLED_INTERNAL

#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>
#include <cmath>
#include <algorithm>

#include "main.h"
#include "layers.h"
#include "config.h"

class rgbleds {
  public:
    static void setup();
    static void loop();
};

#define NUM_LEDS 84
#define DATA_PIN 1

bool isNumOn(){
  return (keyboard_leds & 1) == 1;
}
bool isCapsOn(){
  return (keyboard_leds & 2) == 2;
}
bool isScrollOn(){
  return (keyboard_leds & 4) == 4;
}

bool numLockFound = false;
bool capsLockFound = false;
bool scrollLockFound = false;

int brightness;
const int brt0 = 0;
const int brt1 = 1;
const int brt2 = 2;
const int brt3 = 3;
const int brt4 = 6;
const int brt5 = 9;
const int brt6 = 12;
const int brt7 = 16;
const int brt8 = 20;
const int brt9 = 24;
const int brt10 = 32;


inline void ledsINC () {
  int maxStep = 128; // You can tweak this value
  float norm = brightness / 255.0f;
  int step = std::max(1, static_cast<int>(pow(norm, 2) * maxStep));
  brightness = std::min(brightness + step, 255);
  LEDS.setBrightness(brightness);
}
inline void ledsDEC () {
  int maxStep = 128;
  float norm = brightness / 255.0f;
  int step = std::max(1, static_cast<int>(pow(norm, 2) * maxStep));
  brightness = std::max(brightness - step, 1);
  LEDS.setBrightness(brightness);
}

CRGB leds[NUM_LEDS];

int XYMatrix[rowsCount][columnsCount] = {
  {13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
  {14,15,16,17,18,19,20,21,22,23,24,25,26,27},
  {41,40,39,38,37,36,35,34,33,32,31,30,29,28},
  {42,43,44,45,46,47,48,49,50,51,52,53,54,55},
  {69,68,67,66,65,64,63,62,61,60,59,58,57,56},
  {70,71,72,73,74,75,76,77,78,79,80,83,81,82}
};

void updateLockStates() {
  Capslock = (keyboard_leds & 2) ? Toggle : Modifier;
  Numlock = (keyboard_leds & 1) ? Toggle : Special;
  Numnav  = (keyboard_leds & 1) ? Number : Toggle;
  Scrllock = (keyboard_leds & 4) ? Special : Toggle;
}


void scanLEDs(KeyMapEntry layout[rowsCount][columnsCount]) {
  for (int row = 0; row < rowsCount; row++) {
    for (int col = 0; col < columnsCount; col++) {
      int ledIndex = XYMatrix[row][col];

      // Check if there's an active key being held from another layer
      bool isKeyPressed = physicalKeyStates[row][col].isPressed;
      LayoutKey* activeKeyFromState = physicalKeyStates[row][col].activeKey; // Renamed to avoid conflict

      LayoutKey* keyToUse = nullptr;

      if (isKeyPressed && activeKeyFromState != nullptr) {
        // If a key is physically pressed and we have its original LayoutKey, use that
        keyToUse = activeKeyFromState;
      } else {
        // Otherwise, use the primary key from the current layout's KeyMapEntry
        KeyMapEntry currentEntry = layout[row][col];
        if (currentEntry.primaryKey != nullptr) {
          keyToUse = currentEntry.primaryKey;
        } else {
          // Fallback to NUL if primaryKey is somehow null (should be rare)
          keyToUse = NUL;
        }
      }

      if (keyToUse != nullptr && keyToUse->ledColor != nullptr) { // Check for null pointers
        leds[ledIndex] = *(keyToUse->ledColor);

        if (keyToUse == NMLCK) {
          numLockFound = true;
        } else if (keyToUse == CAPS) {
          capsLockFound = true;
        } else if (keyToUse == SCRLL) {
          scrollLockFound = true;
        }
      } else {
        // This case should ideally not be reached if NUL is used as a fallback.
        // If keyToUse is NUL, its ledColor should be LEDoff (black).
        leds[ledIndex] = CRGB::Black;
      }
    }
  }
  if (numLockFound || capsLockFound || scrollLockFound) {
    updateLockStates();
  }
}

// Wrapper functions for each layout
void leds0()     { scanLEDs(layer0); }
void leds1()     { scanLEDs(layer1); }
void leds1_2()   { scanLEDs(layer1_2); }
void leds2()     { scanLEDs(layer2); }
void leds2_3()   { scanLEDs(layer2_3); }
void leds3()     { scanLEDs(layer3); }
void leds3_4()   { scanLEDs(layer3_4); }
void leds4()     { scanLEDs(layer4); }


void rgbleds::setup() {

  // Load brightness from SD card (fallback to default if not found)
  brightness = Config::loadBrightness(20);

  LEDS.addLeds<WS2812SERIAL, DATA_PIN, BRG>(leds, NUM_LEDS);
  LEDS.setBrightness(brightness);
  leds0();

  // Flash all LEDs with Layer color twice at the end of setup
  // Flash sequence: ON (100ms) -> OFF (100ms) -> ON (100ms) -> OFF (100ms)
  // Temporarily reduce brightness for startup flash
  int originalBrightness = brightness;
  LEDS.setBrightness(brightness / 4);  // Quarter brightness for startup flash

  for (int flash = 0; flash < 2; flash++) {
    // Turn on all LEDs with Layer color
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = Layer;
    }
    FastLED.show();
    delay(100);

    // Turn off all LEDs
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
    FastLED.show();
    delay(100);
  }

  // Restore original brightness
  LEDS.setBrightness(originalBrightness);

  // Restore original LED state
  leds0();
  FastLED.show();
}



void rgbleds::loop() {

  FastLED.show();

}

#endif







