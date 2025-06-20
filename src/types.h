#ifndef TYPES_H
#define TYPES_H

// This header defines fundamental types like LedColor.

// Include FastLED for CRGB definition.
// This assumes FastLED.h is available in the include paths.
#include <FastLED.h>

// Define LedColor as an alias for CRGB
typedef CRGB LedColor;
// C++11 style alias, often preferred
using LedColor = CRGB;

#endif // TYPES_H
