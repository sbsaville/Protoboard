#ifndef KEY_DEFINITIONS_H
#define KEY_DEFINITIONS_H

#include <map>
#include "rgbleds.h" // For CRGB definition (from FastLED.h via rgbleds.h)

// Define LedColor as an alias for CRGB
typedef CRGB LedColor;
using LedColor = CRGB; // C++11 style alias

// Declare global LED color category variables
extern LedColor Layer;
extern LedColor Letter;
extern LedColor Number;
extern LedColor Numnav;
extern LedColor Chara1;
extern LedColor Chara2;
extern LedColor Modifier;
extern LedColor Capslock;
extern LedColor Numlock;
extern LedColor Scrllock;
extern LedColor FKeys1;
extern LedColor FKeys1b;
extern LedColor FKeys2;
extern LedColor FKeys2b;
extern LedColor Special;
extern LedColor Nav;
extern LedColor LedAdj;
extern LedColor LEDoff;
extern LedColor Macro;
extern LedColor Toggle1;
extern LedColor Toggle2;
extern LedColor VimNav;

// Definition of a key's properties (remains the same)
struct KeyFinalDefinition {
    uint16_t keycode;
    LedColor* pActiveColor;
    LedColor* pInitialCategoryColor;
    LedColor uniqueInstanceColor;

    KeyFinalDefinition(uint16_t kc = 0, LedColor* category = nullptr) :
        keycode(kc), pInitialCategoryColor(category) {
        if (category) {
            pActiveColor = category;
            uniqueInstanceColor = *category;
        } else {
            // Default to LEDoff if no category. LEDoff must be initialized.
            // This constructor is called when G_KeyProperties map entries are created.
            // LEDoff will be initialized before initKeyProperties() is called.
            pActiveColor = &LEDoff;
            uniqueInstanceColor = LEDoff;
        }
    }
    KeyFinalDefinition() : keycode(0), pActiveColor(&LEDoff), pInitialCategoryColor(&LEDoff), uniqueInstanceColor(LEDoff) {}
};

// Global map to store all key definitions (remains the same)
extern std::map<uint16_t, KeyFinalDefinition> G_KeyProperties;

// Function to initialize all key properties (remains the same declaration)
void initKeyProperties();

#endif // KEY_DEFINITIONS_H
