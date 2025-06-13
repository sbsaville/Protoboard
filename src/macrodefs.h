#ifndef MACRODEFS_H
#define MACRODEFS_H

#include "macros.h"
#include "main.h"

SimpleMacroManager macroManager;

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
