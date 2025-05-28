#ifndef MACROS_H
#define MACROS_H

#include "main.h"

// Simple text macro structure
struct SimpleMacro {
  uint16_t id;
  const char* text;
};

// Alt-code sequence structure
struct AltCodeSequence {
  uint16_t id;
  const int* sequence;
  uint8_t length;
};

// Combined macro manager - handles both text macros and alt-codes
class SimpleMacroManager {
private:
  static const int MAX_MACROS = 50;
  static const int MAX_ALTCODES = 20;
  SimpleMacro macros[MAX_MACROS];
  AltCodeSequence altCodes[MAX_ALTCODES];
  int macroCount;
  int altCodeCount;

public:
  SimpleMacroManager() : macroCount(0), altCodeCount(0) {}

  // Add a text macro
  bool addMacro(uint16_t id, const char* text) {
    if (macroCount >= MAX_MACROS) return false;
    macros[macroCount].id = id;
    macros[macroCount].text = text;
    macroCount++;
    return true;
  }

  // Add an alt-code sequence
  bool addAltCode(uint16_t id, const int* sequence, uint8_t length) {
    if (altCodeCount >= MAX_ALTCODES) return false;
    altCodes[altCodeCount].id = id;
    altCodes[altCodeCount].sequence = sequence;
    altCodes[altCodeCount].length = length;
    altCodeCount++;
    return true;
  }

  // Execute a macro or alt-code by ID
  bool executeMacro(uint16_t id) {
    // Check text macros first
    for (int i = 0; i < macroCount; i++) {
      if (macros[i].id == id) {
        Keyboard.print(macros[i].text);
        return true;
      }
    }

    // Check alt-codes
    for (int i = 0; i < altCodeCount; i++) {
      if (altCodes[i].id == id) {
        // Send alt-code sequence
        Keyboard.press(KEY_RIGHT_ALT);
        for (uint8_t j = 0; j < altCodes[i].length; j++) {
          Keyboard.press(altCodes[i].sequence[j]);
          Keyboard.release(altCodes[i].sequence[j]);
        }
        Keyboard.release(KEY_RIGHT_ALT);
        return true;
      }
    }

    return false;
  }

  // Get all macros (for future GUI/config)
  SimpleMacro* getAllMacros() { return macros; }
  int getMacroCount() { return macroCount; }
  AltCodeSequence* getAllAltCodes() { return altCodes; }
  int getAltCodeCount() { return altCodeCount; }
};

// Global macro manager instance
extern SimpleMacroManager macroManager;

#endif
