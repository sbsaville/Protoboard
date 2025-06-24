#ifndef KEYDEFS_H
#define KEYDEFS_H

#include <FastLED.h> // For CRGB type, used in LedColor typedef
#include <map>       // For std::map

// Define LedColor as an alias for CRGB (CRGB is provided by FastLED.h)
typedef CRGB LedColor;
using LedColor = CRGB;

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

// Definition of a key's properties
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

// Global map to store all key definitions
extern std::map<uint16_t, KeyFinalDefinition> G_KeyProperties;

// Function to initialize all key properties
void initKeyProperties();

#endif // KEYDEFS_H
