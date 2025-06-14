#include "key_definitions.h"
// main.h is included for usb_keyboard.h keycodes, needed for KEY_SPEC_STD if it uses them by name.
// However, KEY_SPEC_STD will use the keycode value directly as passed from key_specifications.h
#include "main.h"
// rgbleds.h is already included via key_definitions.h for LedColor/CRGB

// Define and initialize global LED color category variables (remains the same)
LedColor Layer    = CRGB(0x00FFFF);
LedColor Letter   = CRGB(0x8000FF);
LedColor Number   = CRGB(0x0000FF);
LedColor Numnav   = CRGB(0x0000FF);
LedColor Chara1   = CRGB(0xFF3300);
LedColor Chara2   = CRGB(0xFF3300);
LedColor Modifier = CRGB(0xFF0000);
LedColor Capslock = CRGB(0xFF0000);
LedColor Numlock  = CRGB(0xFFFF00);
LedColor Scrllock = CRGB(0xFFFF00);
LedColor FKeys1   = CRGB(0xFF2200);
LedColor FKeys1b  = CRGB(0xFF0000);
LedColor FKeys2   = CRGB(0x3300FF);
LedColor FKeys2b  = CRGB(0xFF00FF);
LedColor Special  = CRGB(0xFFFF00);
LedColor Nav      = CRGB(0x0000FF);
LedColor LedAdj   = CRGB(0xFFFFFF);
LedColor LEDoff   = CRGB(0x000000);
LedColor Macro    = CRGB(0xFF69B4);
LedColor Toggle1  = CRGB(0xFF0000);
LedColor Toggle2  = CRGB(0x8000FF);
LedColor VimNav   = CRGB(0x33FF33);

// Define the global map for key properties (remains the same)
std::map<uint16_t, KeyFinalDefinition> G_KeyProperties;

// Function to initialize all key properties using X-Macros
void initKeyProperties() {
    // Define macros for populating G_KeyProperties
    // KEY_SPEC is for custom keys (NumericId will be ORed with 0xA000 by the macro in main.h for declaration,
    // but here we might need to do it explicitly if ConstName is not yet the final value,
    // or pass the final keycode value directly from key_specifications.h)
    // Let's assume key_specifications.h will provide the *final* keycode value for simplicity here.
    // So, KEY_SPEC(FinalKeyCodeConstName, FinalNumericValue, ColorCategoryPtr)
    // And KEY_SPEC_STD(FinalKeyCodeConstName_From_usb_keyboard, ColorCategoryPtr)

    // Revised macro definitions for this file:
    // ConstName parameter will be the actual uint16_t keycode value.
    #define KEY_SPEC(KeycodeValue, ColorCategoryPtr) \
        G_KeyProperties[KeycodeValue] = KeyFinalDefinition(KeycodeValue, ColorCategoryPtr)

    #define KEY_SPEC_STD(UsbKeyCodeValue, ColorCategoryPtr) \
        G_KeyProperties[UsbKeyCodeValue] = KeyFinalDefinition(UsbKeyCodeValue, ColorCategoryPtr)

    // Include the new file that will contain all the KEY_SPEC and KEY_SPEC_STD calls
    // This file will be created in the next step.
    // For now, this line will include a non-existent file, which is fine for this subtask
    // as we are only modifying key_definitions.cpp. The build would fail until key_specifications.h is created.
    #include "key_specifications.h"

    // Undefine the macros to prevent conflicts
    #undef KEY_SPEC
    #undef KEY_SPEC_STD
}
