#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <usb_keyboard.h>
#include <usb_mouse.h>

// Project-specific headers - Order matters for dependencies

// Include base types and configurations first
#include "keyboard_config.h" // Defines PhysicalKeyState (with fwd decl KeyFinalDefinition), rowsCount, columnsCount
#include "keydefs.h"           // Defines KeyFinalDefinition, LedColor, extern color category variables

// Configuration for Keycode ID generation (must be defined before X-Macros are used)
#define USE_EXPLICIT_KEYCODE_IDS 1   // Set to 0 to use auto-generated sequential IDs for custom keys,
                                     // Set to 1 to use the explicit 'NumericId' from keyspecs.h
#define CUSTOM_KEYCODE_BASE_ID 0     // Base for __COUNTER__ if auto-generating IDs (e.g., 0 or 1)

// Now, define the keycode constants using X-Macros
// Define X-Macros for generating keycode constants
#if USE_EXPLICIT_KEYCODE_IDS
    #define KEY_SPEC(ConstName, NumericId, ColorCategoryPtr) \
        const uint16_t ConstName = ((NumericId) | 0xA000);
#else // Use auto-generated IDs; NumericId from keyspecs.h is effectively ignored by this KEY_SPEC definition
    #define KEY_SPEC(ConstName, NumericId, ColorCategoryPtr) \
        const uint16_t ConstName = ((CUSTOM_KEYCODE_BASE_ID + __COUNTER__) | 0xA000);
#endif

#define KEY_SPEC_STD(UsbKeyCodeName, ColorCategoryPtr) \
    /* Standard USB keycodes like KEY_A, KEY_ESC are already globally defined */ \
    /* by <usb_keyboard.h>, so this macro does nothing for constant declaration. */ \
    /* It's defined to allow keyspecs.h to be included without error. */

// Include the specifications file to generate the constants
#include "keyspecs.h" // This generates the const uint16_t KEY_XXX declarations

// Undefine the macros to prevent conflicts
#undef KEY_SPEC
#undef KEY_SPEC_STD

// Include headers that depend on the above constants and types
#include "rgbleds.h"           // Provides rgbleds::setup/loop, uses types/constants from above

// Remaining global declarations
void L_check();

const uint8_t rows[rowsCount] = {39, 38, 37, 36, 35, 34};

const uint8_t columns[columnsCount] = {17, 16, 15, 14, 13, 24, 25, 26, 27, 28, 29, 30, 31, 32};
                                    // c0  c1  c2  c3  c4  c5  c6  c7  c8  c9  10  11  12  13

// Global matrix to track physical key states across layer changes
extern PhysicalKeyState physicalKeyStates[rowsCount][columnsCount];

// Function to initialize the key tracking matrix
void initKeyTrackingMatrix();

#endif // MAIN_H
