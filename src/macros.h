#ifndef MACROS_H
#define MACROS_H

#include "main.h"
#include <vector>

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
  std::vector<SimpleMacro> macros;
  std::vector<AltCodeSequence> altCodes;

public:
  SimpleMacroManager() {}

  bool addMacro(uint16_t id, const char* text) {
    macros.push_back({id, text});
    return true;
  }

  bool addAltCode(uint16_t id, const int* sequence, uint8_t length) {
    altCodes.push_back({id, sequence, length});
    return true;
  }

  template<size_t N>
  bool addAltCode(uint16_t id, const int (&sequence)[N]) {
    return addAltCode(id, sequence, N);
  }

  bool executeMacro(uint16_t id) {
    for (const auto& macro : macros) {
      if (macro.id == id) {
        Keyboard.print(macro.text);
        return true;
      }
    }

    for (const auto& altCode : altCodes) {
      if (altCode.id == id) {
        Keyboard.press(KEY_RIGHT_ALT);
        for (uint8_t j = 0; j < altCode.length; j++) {
          Keyboard.press(altCode.sequence[j]);
          Keyboard.release(altCode.sequence[j]);
        }
        Keyboard.release(KEY_RIGHT_ALT);
        return true;
      }
    }

    return false;
  }

  std::vector<SimpleMacro>& getAllMacros() { return macros; }
  int getMacroCount() { return macros.size(); }
  std::vector<AltCodeSequence>& getAllAltCodes() { return altCodes; }
  int getAltCodeCount() { return altCodes.size(); }
};

SimpleMacroManager macroManager;

#define ADD_ALTCODE(id, ...) \
  do { \
    static const int seq[] = {__VA_ARGS__}; \
    macroManager.addAltCode(id, seq); \
  } while(0)

void initializeMacros() {
  macroManager.addMacro(MACRO_GMAIL,      "scott.b.saville@gmail.com");
  macroManager.addMacro(MACRO_AIMARENA,   "aim arena");
  macroManager.addMacro(MACRO_LINEBREAK,  "</br>");
  macroManager.addMacro(CMNTSTRT,         "/*");
  macroManager.addMacro(CMNTEND,          "*/");
  macroManager.addMacro(MACRO_SQUAREROOT, "sqrt");

  ADD_ALTCODE(KEY_DEGREES,    KEYPAD_PLUS, KEYPAD_0, KEYPAD_0, KEY_B, KEYPAD_0);
  ADD_ALTCODE(PLUS_MINUS,     KEYPAD_PLUS, KEYPAD_0, KEYPAD_0, KEY_B, KEYPAD_1);
  ADD_ALTCODE(E_MACRON,       KEYPAD_PLUS, KEYPAD_0, KEYPAD_1, KEYPAD_1, KEYPAD_3);
  ADD_ALTCODE(GREAT_EQUAL,    KEYPAD_2, KEYPAD_4, KEYPAD_2);
  ADD_ALTCODE(LESS_EQUAL,     KEYPAD_2, KEYPAD_4, KEYPAD_3);
  ADD_ALTCODE(NOT_EQUAL,      KEYPAD_PLUS, KEYPAD_2, KEYPAD_2, KEYPAD_6, KEYPAD_0);

}

#endif
