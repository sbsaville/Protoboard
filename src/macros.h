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

  const std::vector<SimpleMacro>& getAllMacros() const { return macros; }
  int getMacroCount() const { return macros.size(); }
  const std::vector<AltCodeSequence>& getAllAltCodes() const { return altCodes; }
  int getAltCodeCount() const { return altCodes.size(); }
};

SimpleMacroManager macroManager;

#define ADD_ALTCODE(id, ...) \
  do { \
    static const int seq[] = {__VA_ARGS__}; \
    macroManager.addAltCode(id, seq, sizeof(seq)/sizeof(seq[0])); \
  } while(0)

void initializeMacros();

void initializeMacros() {
  macroManager.addMacro(MACRO_GMAIL,      "scott.b.saville@gmail.com");
  macroManager.addMacro(MACRO_AIMARENA,   "aim arena");
  macroManager.addMacro(MACRO_LINEBREAK,  "</br>");
  macroManager.addMacro(CMNTSTRT,         "/*");
  macroManager.addMacro(CMNTEND,          "*/");
  macroManager.addMacro(MACRO_SQUAREROOT, "sqrt");
  macroManager.addMacro(APOSTROPHE_S,     "'s");
  macroManager.addMacro(APOSTROPHE_T,     "'t");
  macroManager.addMacro(APOSTROPHE_D,     "'d");
  macroManager.addMacro(APOSTROPHE_M,     "'m");
  macroManager.addMacro(APOSTROPHE_VE,    "'ve");
  macroManager.addMacro(APOSTROPHE_RE,    "'re");
  macroManager.addMacro(APOSTROPHE_LL,    "'ll");
  macroManager.addMacro(ML_PI,            "\\pi");
  macroManager.addMacro(ML_INF,           "\\inf");
  macroManager.addMacro(ML_SQRT,          "\\sqrt");
  macroManager.addMacro(ML_GREQ,          "<=");
  macroManager.addMacro(ML_LSEQ,          ">=");
  macroManager.addMacro(ML_UNN,           "\\cup");


  ADD_ALTCODE(KEY_DEGREES,    KEYPAD_PLUS, KEYPAD_0, KEYPAD_0, KEY_B, KEYPAD_0);
  ADD_ALTCODE(E_MACRON,       KEYPAD_PLUS, KEYPAD_0, KEYPAD_1, KEYPAD_1, KEYPAD_3);
  ADD_ALTCODE(PLUSORMINUS,    KEYPAD_PLUS, KEYPAD_0, KEYPAD_0, KEY_B, KEYPAD_1);
  ADD_ALTCODE(GREAT_EQUAL,    KEYPAD_2,    KEYPAD_4, KEYPAD_2);
  ADD_ALTCODE(LESS_EQUAL,     KEYPAD_2,    KEYPAD_4, KEYPAD_3);
  ADD_ALTCODE(NOT_EQUAL,      KEYPAD_PLUS, KEYPAD_2, KEYPAD_2, KEYPAD_6, KEYPAD_0);
  ADD_ALTCODE(KEY_APPROX,     KEYPAD_PLUS, KEYPAD_2, KEYPAD_2, KEYPAD_4, KEYPAD_8);
  ADD_ALTCODE(KEY_INFINITY,   KEYPAD_PLUS, KEYPAD_2, KEYPAD_2, KEYPAD_1, KEY_E);
  ADD_ALTCODE(KEY_UNION,      KEYPAD_PLUS, KEYPAD_2, KEYPAD_2, KEYPAD_2, KEY_A);
  ADD_ALTCODE(KEY_PI,         KEYPAD_PLUS, KEYPAD_0, KEYPAD_3, KEY_C, KEYPAD_0);
  ADD_ALTCODE(KEY_THETA,      KEYPAD_PLUS, KEYPAD_0, KEYPAD_3, KEY_B, KEYPAD_8);
  ADD_ALTCODE(KEY_ALPHA,      KEYPAD_PLUS, KEYPAD_0, KEYPAD_3, KEY_B, KEYPAD_1);
  ADD_ALTCODE(KEY_BETA,       KEYPAD_PLUS, KEYPAD_0, KEYPAD_3, KEY_B, KEYPAD_2);
  ADD_ALTCODE(KEY_GAMMA,      KEYPAD_PLUS, KEYPAD_0, KEYPAD_3, KEY_B, KEYPAD_3);
  ADD_ALTCODE(KEY_DELTA,      KEYPAD_PLUS, KEYPAD_0, KEYPAD_3, KEYPAD_9, KEYPAD_4);
  ADD_ALTCODE(KEY_EPSILON,    KEYPAD_PLUS, KEYPAD_0, KEYPAD_3, KEY_B, KEYPAD_5);
  ADD_ALTCODE(KEY_LAMBDA,     KEYPAD_PLUS, KEYPAD_0, KEYPAD_3, KEY_B, KEY_B);
  ADD_ALTCODE(KEY_MU,         KEYPAD_PLUS, KEYPAD_0, KEYPAD_3, KEY_B, KEY_C);
  ADD_ALTCODE(KEY_SIGMA,      KEYPAD_PLUS, KEYPAD_0, KEYPAD_3, KEY_A, KEYPAD_3);
  ADD_ALTCODE(KEY_PHI,        KEYPAD_PLUS, KEYPAD_0, KEYPAD_3, KEY_C, KEYPAD_6);
  ADD_ALTCODE(KEY_OMEGA,      KEYPAD_PLUS, KEYPAD_0, KEYPAD_3, KEY_A, KEYPAD_9);
  ADD_ALTCODE(KEY_RATIO,      KEYPAD_PLUS, KEYPAD_2, KEYPAD_2, KEYPAD_3, KEYPAD_6);
  ADD_ALTCODE(KEY_SOLIDUS,    KEYPAD_PLUS, KEYPAD_2, KEYPAD_9, KEY_F, KEYPAD_8);
  ADD_ALTCODE(L_KAGI_KAKKO,   KEYPAD_PLUS, KEYPAD_3, KEYPAD_0, KEYPAD_0, KEY_C);
  ADD_ALTCODE(R_KAGI_KAKKO,   KEYPAD_PLUS, KEYPAD_3, KEYPAD_0, KEYPAD_0, KEY_D);
  ADD_ALTCODE(LN_KAGI_KAKKO,  KEYPAD_PLUS, KEYPAD_3, KEYPAD_0, KEYPAD_0, KEY_E);
  ADD_ALTCODE(RN_KAGI_KAKKO,  KEYPAD_PLUS, KEYPAD_3, KEYPAD_0, KEYPAD_0, KEY_F);
  ADD_ALTCODE(L_DBL_BRACKET,  KEYPAD_PLUS, KEYPAD_2, KEYPAD_7, KEY_E, KEYPAD_6);
  ADD_ALTCODE(R_DBL_BRACKET,  KEYPAD_PLUS, KEYPAD_2, KEYPAD_7, KEY_E, KEYPAD_7);
  ADD_ALTCODE(L_DBL_PAREN,    KEYPAD_PLUS, KEYPAD_2, KEY_E, KEYPAD_2, KEYPAD_8);
  ADD_ALTCODE(R_DBL_PAREN,    KEYPAD_PLUS, KEYPAD_2, KEY_E, KEYPAD_2, KEYPAD_9);
  ADD_ALTCODE(SUPERSCRIPT_0,  KEYPAD_PLUS, KEYPAD_2, KEYPAD_0, KEYPAD_7, KEYPAD_0);
  ADD_ALTCODE(SUPERSCRIPT_1,  KEYPAD_0, KEYPAD_1, KEYPAD_8, KEYPAD_5);
  ADD_ALTCODE(SUPERSCRIPT_2,  KEYPAD_0, KEYPAD_1, KEYPAD_7, KEYPAD_8);
  ADD_ALTCODE(SUPERSCRIPT_3,  KEYPAD_0, KEYPAD_1, KEYPAD_7, KEYPAD_9);
  ADD_ALTCODE(SUPERSCRIPT_4,  KEYPAD_PLUS, KEYPAD_2, KEYPAD_0, KEYPAD_7, KEYPAD_4);
  ADD_ALTCODE(SUPERSCRIPT_5,  KEYPAD_PLUS, KEYPAD_2, KEYPAD_0, KEYPAD_7, KEYPAD_5);
  ADD_ALTCODE(SUPERSCRIPT_6,  KEYPAD_PLUS, KEYPAD_2, KEYPAD_0, KEYPAD_7, KEYPAD_6);
  ADD_ALTCODE(SUPERSCRIPT_7,  KEYPAD_PLUS, KEYPAD_2, KEYPAD_0, KEYPAD_7, KEYPAD_7);
  ADD_ALTCODE(SUPERSCRIPT_8,  KEYPAD_PLUS, KEYPAD_2, KEYPAD_0, KEYPAD_7, KEYPAD_8);
  ADD_ALTCODE(SUPERSCRIPT_9,  KEYPAD_PLUS, KEYPAD_2, KEYPAD_0, KEYPAD_7, KEYPAD_9);
  ADD_ALTCODE(KEY_EMDASH,     KEYPAD_PLUS, KEYPAD_2, KEYPAD_0, KEYPAD_1, KEYPAD_4);


}

#endif
