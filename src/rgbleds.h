#ifndef RGBLEDS_H
#define RGBLEDS_H

#include <WS2812Serial.h>
#include <cmath>
#include <algorithm>

#include "main.h"
#include "layers.h"
#include "sdconfig.h"

class rgbleds {
  public:
    static void setup();
    static void loop();
    static void ledsINC();
    static void ledsDEC();
    static void scanLEDs(KeyMapEntry layout[rowsCount][columnsCount]);
};

#define NUM_LEDS 84
#define DATA_PIN 1
#define FPS 200

// Create the LED objects
byte drawingMemory[NUM_LEDS * 3];
DMAMEM byte displayMemory[NUM_LEDS * 12];
WS2812Serial leds(NUM_LEDS, displayMemory, drawingMemory, DATA_PIN, WS2812_BRG);

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

// Brightness level constants
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

// Helper function to apply brightness to a color
uint32_t applyBrightness(uint32_t color, uint8_t br) {
    if (br == 255) return color;
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;
    r = (r * br) >> 8;
    g = (g * br) >> 8;
    b = (b * br) >> 8;
    return (r << 16) | (g << 8) | b;
}

void rgbleds::ledsINC () {
  int maxStep = 128; // You can tweak this value
  float norm = brightness / 255.0f;
  int step = std::max(1, static_cast<int>(pow(norm, 2) * maxStep));
  brightness = std::min(brightness + step, 255);
}
void rgbleds::ledsDEC () {
  int maxStep = 128;
  float norm = brightness / 255.0f;
  int step = std::max(1, static_cast<int>(pow(norm, 2) * maxStep));
  brightness = std::max(brightness - step, 1);
}

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
  Scrlock = (keyboard_leds & 4) ? Toggle : Special;
}


void rgbleds::scanLEDs(KeyMapEntry layout[rowsCount][columnsCount]) {
  for (int row = 0; row < rowsCount; row++) {
    for (int col = 0; col < columnsCount; col++) {
      int ledIndex = XYMatrix[row][col];

      bool isKeyPressed = physicalKeyStates[row][col].isPressed;
      LayoutKey* activeKeyFromState = physicalKeyStates[row][col].activeKey;

      LayoutKey* keyToUse = nullptr;

      if (isKeyPressed && activeKeyFromState != nullptr) {
        keyToUse = activeKeyFromState;
      } else {
        KeyMapEntry currentEntry = layout[row][col];
        if (currentEntry.primaryKey != nullptr) {
          keyToUse = currentEntry.primaryKey;
        } else {
          keyToUse = NUL;
        }
      }

      if (keyToUse != nullptr && keyToUse->ledColor != nullptr) {
        leds.setPixel(ledIndex, applyBrightness(*(keyToUse->ledColor), brightness));

        if (keyToUse == NMLCK) {
          numLockFound = true;
        } else if (keyToUse == CAPS) {
          capsLockFound = true;
        } else if (keyToUse == SCRLLK) {
          scrollLockFound = true;
        }
      } else {
        leds.setPixel(ledIndex, 0x000000); // Black
      }
    }
  }
  if (numLockFound || capsLockFound || scrollLockFound) {
    updateLockStates();
  }
}

void leds0()         { rgbleds::scanLEDs(layer0); }
void leds1()         { rgbleds::scanLEDs(layer1); }
void leds2DT()       { rgbleds::scanLEDs(layer2DT); }
void leds2()         { rgbleds::scanLEDs(layer2); }
void ledsSymbols()   { rgbleds::scanLEDs(layerSymbols); }
void leds3()         { rgbleds::scanLEDs(layerAppostrophe); }
void leds3DT()       { rgbleds::scanLEDs(layer3DT); }
void leds4()         { rgbleds::scanLEDs(layer4); }
void leds4DT()       { rgbleds::scanLEDs(layer4DT); }


void rgbleds::setup() {

  // Load brightness from SD card (fallback to default if not found)
  brightness = sdconfig::loadBrightness(20);

  leds.begin();
  leds0();

  // Flash all LEDs with Layer color twice at the end of setup
  uint8_t startupBrightness = std::max(1, brightness / 4);

  for (int flash = 0; flash < 2; flash++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds.setPixel(i, applyBrightness(LayerKey, startupBrightness));
    }
    leds.show();
    delay(100);

    for (int i = 0; i < NUM_LEDS; i++) {
      leds.setPixel(i, 0x000000); // Black
    }
    leds.show();
    delay(100);
  }

  leds0();
  leds.show();
}


unsigned long lastLedUpdateTime = 0;

void rgbleds::loop() {
  if (millis() - lastLedUpdateTime > 1000 / FPS) {
    leds.show();
    lastLedUpdateTime = millis();
  }
}

#endif







