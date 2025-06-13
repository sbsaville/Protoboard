#ifndef MACROS_H
#define MACROS_H

#include "main.h"

struct SimpleMacro {
  uint16_t id;
  const char* text;
};

struct AltCodeSequence {
  uint16_t id;
  const int* sequence;
  uint8_t length;
};

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
  bool addMacro(uint16_t id, const char* text) {
    if (macroCount >= MAX_MACROS) return false;
    macros[macroCount].id = id;
    macros[macroCount].text = text;
    macroCount++;
    return true;
  }

  bool addAltCode(uint16_t id, const int* sequence, uint8_t length) {
    if (altCodeCount >= MAX_ALTCODES) return false;
    altCodes[altCodeCount].id = id;
    altCodes[altCodeCount].sequence = sequence;
    altCodes[altCodeCount].length = length;
    altCodeCount++;
    return true;
  }

  template<size_t N>
  bool addAltCode(uint16_t id, const int (&sequence)[N]) {
    return addAltCode(id, sequence, N);
  }

  bool executeMacro(uint16_t id) {
    for (int i = 0; i < macroCount; i++) {
      if (macros[i].id == id) {
        Keyboard.print(macros[i].text);
        return true;
      }
    }

    for (int i = 0; i < altCodeCount; i++) {
      if (altCodes[i].id == id) {
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

  SimpleMacro* getAllMacros() { return macros; }
  int getMacroCount() { return macroCount; }
  AltCodeSequence* getAllAltCodes() { return altCodes; }
  int getAltCodeCount() { return altCodeCount; }
};

extern SimpleMacroManager macroManager;

#define ADD_ALTCODE(id, ...) \
  do { \
    static const int seq[] = {__VA_ARGS__}; \
    macroManager.addAltCode(id, seq); \
  } while(0)

#endif
