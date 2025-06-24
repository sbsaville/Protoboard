#ifndef KEYBOARD_CONFIG_H
#define KEYBOARD_CONFIG_H

#include <cstdint> // For uint8_t, uint16_t
#include <cstddef> // For std::nullptr_t if needed by KeyFinalDefinition forward, though bool is more direct

// Define core matrix dimensions
const uint8_t rowsCount = 6;
const uint8_t columnsCount = 14;

// Forward declaration for KeyFinalDefinition, which is fully defined in keydefs.h
struct KeyFinalDefinition;

// Definition of a physical key's state (used in main.h and rgbleds.h)
struct Key {
    uint8_t row;
    uint8_t column;
    bool pressed; // Using bool, ensure consistency if original was Arduino 'boolean'
};

struct PhysicalKeyState {
    bool isPressed;
    uint16_t activeCode;
    const KeyFinalDefinition* activeKey; // Pointer to the definition of the active key
};

#endif // KEYBOARD_CONFIG_H
