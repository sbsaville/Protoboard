#ifndef KEY_DEFINITIONS_H
#define KEY_DEFINITIONS_H

#include <map>
// Assuming LedColor is CRGB and rgbleds.h provides its definition or includes FastLED.h etc.
#include "rgbleds.h"

// Declare global LED color category variables (original names, no COL_ prefix)
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
            pActiveColor = &LEDoff;
            uniqueInstanceColor = LEDoff; // Ensure LEDoff is initialized when this is used.
        }
    }

    KeyFinalDefinition() : keycode(0), pActiveColor(&LEDoff), pInitialCategoryColor(&LEDoff), uniqueInstanceColor(LEDoff) {}
};

extern std::map<uint16_t, KeyFinalDefinition> G_KeyProperties;
void initKeyProperties();

#endif // KEY_DEFINITIONS_H
