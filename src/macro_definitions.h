#ifndef MACRO_DEFINITIONS_H
#define MACRO_DEFINITIONS_H

#include "macros.h"
#include "main.h"

// Global macro manager instance
SimpleMacroManager macroManager;

// Alt-code sequences - define them here (matching the original sequences from edgeevents.h)
static const int seq_DEGREE[]     = {KEYPAD_PLUS, KEYPAD_0, KEYPAD_0, KEY_B, KEYPAD_0};
static const int seq_PLUSMINUS[]  = {KEYPAD_PLUS, KEYPAD_0, KEYPAD_0, KEY_B, KEYPAD_1};
static const int seq_EMACRON[]    = {KEYPAD_PLUS, KEYPAD_0, KEYPAD_1, KEYPAD_1, KEYPAD_3};
static const int seq_GREATEQUAL[] = {KEYPAD_2, KEYPAD_4, KEYPAD_2};
static const int seq_LESSEQUAL[]  = {KEYPAD_2, KEYPAD_4, KEYPAD_3};
static const int seq_NOTEQUAL[]   = {KEYPAD_PLUS, KEYPAD_2, KEYPAD_2, KEYPAD_6, KEYPAD_0};

// Initialize all macros and alt-codes - called during setup
void initializeMacros() {
  // Add all text macros here - just one line each!
  macroManager.addMacro(MACRO_GMAIL,      "scott.b.saville@gmail.com");
  macroManager.addMacro(MACRO_AIMARENA,   "aim arena");
  macroManager.addMacro(MACRO_LINEBREAK,  "</br>");
  macroManager.addMacro(CMNTSTRT,         "/*");
  macroManager.addMacro(CMNTEND,          "*/");
  macroManager.addMacro(MACRO_SQUAREROOT, "sqrt");

  // Add all alt-codes here - just one line each!
  macroManager.addAltCode(KEY_DEGREES,    seq_DEGREE,      5);
  macroManager.addAltCode(PLUS_MINUS,     seq_PLUSMINUS,   5);
  macroManager.addAltCode(E_MACRON,       seq_EMACRON,     5);
  macroManager.addAltCode(GREAT_EQUAL,    seq_GREATEQUAL,  3);
  macroManager.addAltCode(LESS_EQUAL,     seq_LESSEQUAL,   3);
  macroManager.addAltCode(NOT_EQUAL,      seq_NOTEQUAL,    5);

  // To add a new macro, just add one line like:
  // macroManager.addMacro(MACRO_HELLO, "Hello World!");
  //
  // To add a new alt-code, define the sequence above and add one line like:
  // macroManager.addAltCode(ALT_HELLO, seq_HELLO, 4);
  //
  // Then define the constant in main.h and use it in your layouts!
}

#endif
