#ifndef LAYERS_H
#define LAYERS_H

#include "main.h"
#include "keydefs.h"
#include "rgbleds.h"
#include <cstdint> // Required for uint16_t
#include <vector>  // Required for std::vector

// Enum for Layer Activation Types
enum class LayerActivationType {
    LAYER_IS_DEFAULT, // Renamed from DEFAULT to avoid macro collision
    SINGLE_PRESS,   // Momentary: Active while key is held
    COMBO_PRESS,    // Momentary: Active while all combo keys are held
    TOGGLE,         // Toggle: Press once to activate, press again to deactivate
    DOUBLE_TAP_HOLD,// Double-Tap: Tap once, then press and hold second time to activate (momentary)
    DOUBLE_TAP_TOGGLE // Double-Tap: Tap twice quickly to toggle activation
    // TODO: OneShot functionality could be added here later
};

// Maximum number of keys that can be part of a combo to activate a layer
#define MAX_COMBO_KEYS 2 // For now, supporting 2-key combos like L1+L2

// Struct to define a layer
struct Layer {
    // const char* name; // Removed as per user feedback
    KeyMapEntry (*keymap)[columnsCount];
    LayerActivationType activationType;
    uint16_t activationKeys[MAX_COMBO_KEYS]; // Keycodes that activate this layer
    uint8_t numActivationKeys; // How many keys are in activationKeys

    // State variables for layer logic
    bool isActive;
    // For double-tap logic
    uint8_t tapCount;
    unsigned long lastTapTime; // For 1st tap of DT, or for 2nd tap press time when awaitingSecondTapRelease
    bool waitingForSecondTap; // True if first tap of a double tap has occurred
    bool awaitingSecondTapRelease; // True if 2nd tap occurred, waiting for its release to decide toggle vs momentary

    // For toggle layers, this specific key deactivates it.
    // For DOUBLE_TAP_TOGGLE, this is the same as activationKeys[0]
    // For other toggle types, it could be a different key.
    uint16_t toggleOffKey;

    // Constructor
    Layer(KeyMapEntry (*km)[columnsCount], LayerActivationType type,
          std::initializer_list<uint16_t> keys, uint16_t offKey = 0)
        : /*name(n),*/ keymap(km), activationType(type), numActivationKeys(0),
          isActive(false), tapCount(0), lastTapTime(0), waitingForSecondTap(false), awaitingSecondTapRelease(false),
          toggleOffKey(offKey) {
        // Copy activation keys from initializer_list
        // Ensure not to overflow activationKeys
        for (uint16_t key : keys) {
            if (numActivationKeys < MAX_COMBO_KEYS) {
                activationKeys[numActivationKeys++] = key;
            } else {
                // Handle error: too many keys for combo
                // For now, just ignore extra keys. A Serial.print warning could be added.
                break;
            }
        }
        if (activationType == LayerActivationType::TOGGLE || activationType == LayerActivationType::DOUBLE_TAP_TOGGLE) {
            if (offKey == 0 && numActivationKeys > 0) { // Default offKey to the first activation key for toggles
                toggleOffKey = activationKeys[0];
            }
        }
    }

     // Default constructor for placeholder/inactive layers if needed
    Layer() : /*name("Uninitialized"),*/ keymap(nullptr), activationType(LayerActivationType::LAYER_IS_DEFAULT), numActivationKeys(0), isActive(false), tapCount(0), lastTapTime(0), waitingForSecondTap(false), toggleOffKey(0) {}
};

// Global vector of active layers, defined in Protoboard.cpp
// Declared here AFTER Layer is fully defined.
extern std::vector<Layer> activeLayers;

const KeyMapEntry layer0_default[rowsCount][columnsCount] = {
  {{ESC},    {F1},    {F2},    {F3},    {F4},    {F5},    {F6},    {F7},    {F8},    {F9},     {F10},   {F11},        {F12},   {DEL}  },
  {{TILDE},  {NUM1},  {NUM2},  {NUM3},  {NUM4},  {NUM5},  {NUM6},  {NUM7},  {NUM8},  {NUM9},   {NUM0},  {MINUS},      {EQUAL}, {HOME} },
  {{TAB},    {Q},     {W},     {E},     {R},     {T},     {Y},     {U},     {I},     {O},      {P},     {LBRACK},     {RBRACK},{BSLSH}},
  {{ESC},    {A},     {S},     {D},     {F},     {G},     {H},     {J},     {K},     {L},      {SMCLN}, {QUOTE},      {ENTER}, {END}  },
  {{LSHFT},  {Z},     {X},     {C},     {V},     {B},     {N},     {M},     {COMMA}, {PERIOD}, {SLASH}, {RSHFT,CAPS}, {UP},    {RIGHT}},
  {{LCRTL},  {LGUI},  {LALT},  {LYR1},  {LYR2},  {SPC},   {BKSPC}, {LYR3},  {LYR4},  {RALT},   {RGUI},  {RCRTL},      {LEFT},  {DOWN} }
};

extern KeyMapEntry layer0[rowsCount][columnsCount];

KeyMapEntry layer1[rowsCount][columnsCount] = {
  {{ESC,SET0},{F13},   {F14},   {F15},   {F16},   {F17},   {F18},   {F19},   {F20},   {F21},    {F22},   {F23},   {F24},   {NUL}},
  {{PMUL},    {PDIV},  {PADD},  {PSUB},  {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},    {NUL},   {NUL},   {NUL},   {NUL}},
  {{PAD7},    {PAD8},  {PAD9},  {QUOTE}, {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},    {NUL},   {NUL},   {NUL},   {NUL}},
  {{PAD4},    {PAD5},  {PAD6},  {DBLQ},  {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {APST_LL},{NUL},   {NUL},   {ENTER}, {NUL}},
  {{PAD1},    {PAD2},  {PAD3},  {ENTER}, {NUL},   {NUL},   {NUL},   {APST_M},{NUL},   {NUL},    {NUL},   {NUL},   {NUL},   {NUL}},
  {{PAD0},    {PAD0},  {PDOT},  {LYR1},  {LYR2},  {SPC},   {BKSPC}, {NUL},   {NUL},   {NUL},    {NUL},   {NUL},   {NUL},   {NUL}}
};

KeyMapEntry layer2[rowsCount][columnsCount] = {
  {{ESC,SET0},{F13},   {F14},   {F15},   {F16},   {F17},   {F18},   {F19},   {F20},   {F21},   {F22},   {F23},   {F24},   {NUL}},
  {{LPAR},    {PMUL},  {PDIV},  {PADD},  {PSUB},  {RPAR},  {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL}},
  {{ALTTAB},  {PAD7},  {PAD8},  {PAD9},  {CARAT}, {NUL},   {HOME},  {PGDN},  {PGUP},  {END},   {NUL},   {NUL},   {NUL},   {NUL}},
  {{LYR2B},   {PAD4},  {PAD5},  {PAD6},  {EQUAL}, {PENT},  {LEFT},  {DOWN},  {UP},    {RIGHT}, {NUL},   {NUL},   {ENTER}, {LCLK}},
  {{HYPER},   {PAD1},  {PAD2},  {PAD3},  {PDOT},  {PENT},  {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {RSHFT}, {NUL},   {NMLCK}},
  {{MEH},     {PAD0},  {PAD0},  {LYR1},  {LYR2},  {SPC},   {DEL},   {LYR3},  {NUL},   {RALT},  {RGUI},  {RCRTL}, {NUL},   {NUL}}
};

KeyMapEntry layer2DT[rowsCount][columnsCount] = {
  {{ESC,SET0},{F13},   {F14},   {F15},   {F16},   {F17},   {F18},   {F19},   {F20},   {F21},   {F22},   {F23},   {F24},   {DEL}},
  {{LPAR},    {PMUL},  {PDIV},  {PADD},  {PSUB},  {RPAR},  {NUL},   {NUL},   {NUL},   {NUL},   {PMUL},  {PSUB},  {PADD},  {HOME}},
  {{TAB},     {PAD7},  {PAD8},  {PAD9},  {CARAT}, {MLSQRT},{NUL},   {MLUNN}, {MLINF}, {NUL},   {MLPI},  {LBRACK},{RBRACK},{PDIV}},
  {{NUL},     {PAD4},  {PAD5},  {PAD6},  {EQUAL}, {NUL},   {LEFT},  {DOWN},  {UP},    {RIGHT}, {NUL},   {NUL},   {ENTER}, {END}},
  {{LSHFT},   {PAD1},  {PAD2},  {PAD3},  {PENT},  {NUL},   {NOTEQL},{MLLSEQ},{COMMA}, {PERIOD},{MLGREQ},{RSHFT}, {NUL},   {NMLCK}},
  {{LCRTL},   {PAD0},  {PAD0},  {PDOT},  {LYR2},  {SPC},   {BKSPC}, {LYR0},  {LYR4},  {RALT},  {RGUI},  {RCRTL}, {NUL},   {NUL}}
};

KeyMapEntry layerLNav[rowsCount][columnsCount] = {
  {{ESC,SET0},{F13},   {F14},   {F15},   {F16},   {F17},   {F18},   {F19},   {F20},   {F21},   {F22},   {F23},   {F24},   {NUL}},
  {{NUL},     {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL}},
  {{TAB},     {HOME},  {UP},    {END},   {PGUP},  {NUL},   {HOME},  {PGDN},  {PGUP},  {END},   {NUL},   {NUL},   {NUL},   {NUL}},
  {{LYR2B},   {LEFT},  {DOWN},  {RIGHT}, {PGDN},  {PENT},  {LEFT},  {DOWN},  {UP},    {RIGHT}, {NUL},   {NUL},   {ENTER}, {LCLK}},
  {{LSHFT},   {NUL},   {NUL},   {NUL},   {NUL},   {PENT},  {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {RSHFT}, {NUL},   {NMLCK}},
  {{LCRTL},   {LGUI},  {LALT},  {LCRTL}, {LALT},  {DEL},   {BKSPC}, {LYR3},  {NUL},   {RALT},  {RGUI},  {RCRTL}, {NUL},   {NUL}}
};

/* Old layer2_3 for temporary reference
KeyMapEntry layerSymbols[rowsCount][columnsCount] = {
  {{ESC,SET0},{F13},   {F14},   {F15},   {F16},   {F17},   {F18},   {F19},   {F20},   {F21},   {F22},   {F23},   {F24},   {NUL}},
  {{NUL},     {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL}},
  {{NUL},     {QSTN},  {NUL},   {EXCLM}, {ASTR},  {NUL},   {NUL},   {UNDS},  {NUL},   {NUL},   {PRCNT}, {NUL},   {NUL},   {NUL}},
  {{NUL},     {AT},    {SLASH}, {DLLR},  {NUL},   {DEGR},  {MINUS}, {NUL},   {NUL},   {PADD},  {NUL},   {LYR2B}, {ENTER}, {NUL}},
  {{NUL},     {NUL},   {ASTR},  {CARAT}, {NUL},   {BSLSH}, {HASH},  {AMPS},  {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL}},
  {{NUL},     {NUL},   {NUL},   {NUL},   {LYR2},  {SPC},   {BKSPC}, {LYR3},  {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL}}
}; 
*/

KeyMapEntry layerSymbols[rowsCount][columnsCount] = {
  {{CAPSESC,SET0},{SF13},  {SF14},  {SF15},  {SF16},  {SF17},  {SF18},  {SF19},  {SF20},  {SF21},  {SF22},  {SF23},  {SF24},  {NUL}},
  {{NUL},         {SS_1},  {SS_2},  {SS_3},  {SS_4},  {SS_5},  {SS_6},  {SS_7},  {SS_8},  {SS_9},  {SS_0},  {PLSMNS},{NOTEQL},{NUL}},
  {{NUL},         {QUOTE}, {DBLQ},  {EXCLM}, {ASTR},  {LCHEV}, {RCHEV}, {UNDS},  {NUL},   {NUL},   {PIPE},  {NUL},   {NUL},   {NUL}},
  {{ESC},         {NUL},   {DLLR},  {LBRACE},{LBRACK},{LPAR},  {RPAR},  {RBRACK},{RBRACE},{NUL},   {NUL},   {NUL},   {ENTER}, {NUL}},
  {{LSHFT},       {DEGR},  {NUL},   {PRCNT}, {CMTST}, {BSLSH}, {HASH},  {CMTED}, {LSEQL}, {GREQL}, {NUL},   {RSHFT}, {NUL},   {NUL}},
  {{LCRTL},       {LGUI},  {LALT},  {LYR2},  {LYR2},  {DEL},   {BKSPC}, {LYR3},  {LYR4},  {RALT},  {RGUI},  {RCRTL}, {NUL},   {NUL}}
}; 

KeyMapEntry layerAppostrophe[rowsCount][columnsCount] = {
  {{ESC,SET0},{F13},   {F14},   {F15},   {F16},    {F17},   {F18},   {F19},   {F20},   {F21},    {F22},   {F23},   {F24},   {BKSPC}},
  {{NUL},     {SS_1},  {SS_2},  {SS_3},  {SS_4},   {SS_5},  {SS_6},  {SS_7},  {SS_8},  {SS_9},   {SS_0},  {MDASH}, {NUL},   {NUL}},
  {{NUL},     {QUOTE}, {DBLQ},  {NUL},   {APST_RE},{APST_T},{NUL},   {NUL},   {NUL},   {NUL},    {NUL},   {NUL},   {NUL},   {NUL}},
  {{NUL},     {NUL},   {APST_S},{APST_D},{NUL},    {NUL},   {NUL},   {NUL},   {NUL},   {APST_LL},{NUL},   {LYR3B}, {ENTER}, {NUL}},
  {{LSHFT},   {NUL},   {NUL},   {NUL},   {APST_VE},{NUL},   {NUL},   {APST_M},{NUL},   {NUL},    {NUL},   {HYPER}, {NUL},   {NUL}},
  {{LCRTL},   {LGUI},  {LALT},  {LYR2},  {LYR2},   {DEL},   {BKSPC}, {LYR3},  {LYR4},  {RALT},   {RGUI},  {RCRTL}, {NUL},   {NUL}}
};

KeyMapEntry layer3DT[rowsCount][columnsCount] = {
  {{ESC,SET0},{SF13},  {SF14},  {SF15},  {SF16},  {SF17},  {SF18},  {SF19},  {SF20},  {SF21},  {SF22},  {SF23},  {SF24},  {NUL}},
  {{NUL},     {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {PMUL},  {PDIV},  {PADD},  {PSUB},  {NUL},   {NUL}},
  {{TAB},     {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {PAD7},  {PAD8},  {PAD9},  {CARAT}, {NUL},   {NUL}},
  {{NUL},     {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {PAD4},  {PAD5},  {PAD6},  {NUL},   {ENTER}, {NUL}},
  {{LSHFT},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {PAD1},  {PAD2},  {PAD3},  {NUL},   {NUL},   {NMLCK}},
  {{LCRTL},   {LGUI},  {LALT},  {NUL},   {LYR0},  {SPC},   {BKSPC}, {LYR3},  {PAD0},  {PAD0},  {PDOT},  {RCRTL}, {NUL},   {NUL}}
};

KeyMapEntry layerRNav[rowsCount][columnsCount] = {
  {{ESC,SET0},{F13},   {F14},   {F15},   {F16},   {F17},   {F18},  {F19},   {F20},   {F21},   {F22},   {F23},   {F24},   {NUL}},
  {{NUL},     {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},  {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL}},
  {{TAB},     {HOME},  {UP},    {END},   {PGUP},  {NUL},   {NUL},  {PGUP},  {HOME},  {UP},    {END},   {NUL},   {NUL},   {NUL}},
  {{NUL},     {LEFT},  {DOWN},  {RIGHT}, {PGDN},  {NUL},   {NUL},  {PGDN},  {LEFT},  {DOWN},  {RIGHT}, {LYR3B}, {ENTER}, {LCLK}},
  {{LSHFT},   {NUL},   {NUL},   {NUL},   {PENT},  {NUL},   {NUL},  {NUL},   {NUL},   {NUL},   {NUL},   {RSHFT}, {PGUP},  {NMLCK}},
  {{LCRTL},   {LGUI},  {LALT},  {LCRTL}, {LALT},  {DEL},   {BKSPC},{LYR3},  {NUL},   {RALT},  {RGUI},  {RCRTL}, {PGDN},  {PGDN}}
};

KeyMapEntry layer4[rowsCount][columnsCount] = {
  {{ESC,SET0},{F13},   {F14},   {F15},   {F16},    {F17},   {F18},   {F19},   {F20},   {F21},    {F22},   {F23},   {F24},   {BKSPC}},
  {{NUL},     {LNKK},  {LKK},   {NUL},   {RKK},    {RNKK},  {NUL},   {NUL},   {NUL},   {LDBPAR}, {RDBPAR},{PLSMNS},{APPROX},{NOTEQL}},
  {{TAB},     {NUL},   {NUL},   {EPSILON},{NUL},   {THETA}, {NUL},   {UNION}, {INFNY}, {NUL},    {GRKPI}, {LDBBRK},{RDBBRK},{NUL}},
  {{CAPSLSH}, {ALPHA}, {SIGMA}, {DELTA}, {PHI},    {GAMMA}, {NUL},   {NUL},   {NUL},   {LAMBDA}, {RATIO}, {NUL},   {ENTER}, {NUL}},
  {{LSHFT},   {OMEGA}, {NUL},   {NUL},   {NUL},    {BETA},  {NUL},   {MU},    {LSEQL}, {GREQL},  {SLDS},  {RSHFT}, {NUL},   {NUL}},
  {{LCRTL},   {LGUI},  {LALT},  {NUL},   {ALTL},   {SPC},   {ALTR},  {LYR3},  {LYR4},  {RALT},   {RGUI},  {RCRTL}, {NUL},   {NUL}}
};

KeyMapEntry layer4DT[rowsCount][columnsCount] = {
  {{CAPSESC,SET0},{F13},   {F14},   {F15},   {F16},   {F17},   {F18},   {F19},   {F20},   {F21},   {F22},   {F23},   {F24},   {BKSPC}},
  {{BR0},         {BR1},   {BR2},   {BR3},   {BR4},   {BR5},   {BR6},   {BR7},   {BR8},   {BR9},   {BR10},  {NUL},   {NUL},   {INCR}},
  {{TAB},         {NUL},   {NUL},   {EMCRN}, {NUL},   {NUL},   {NUL},   {NUL},   {INSRT}, {NUL},   {PSBRK}, {NUL},   {NUL},   {DECR}},
  {{CAPSLSH},     {AMRN},  {NUL},   {NUL},   {NUL},   {GMAIL}, {NUL},   {NUL},   {NUL},   {SCRLL}, {NUL},   {NUL},   {ENTER}, {NUL}},
  {{SET0},        {NUL},   {NUL},   {NUL},   {NUL},   {LNBRK}, {PRNT},  {NUL},   {NUL},   {NUL},   {NUL},   {RWND},  {REC},   {FFWD}},
  {{RLEASE},      {RBOOT}, {NUL},   {NUL},   {ALTL},  {SPC},   {ALTR},  {LYR3},  {LYR4},  {NUL},   {NUL},   {PREV},  {PLYPS}, {NEXT}}
};

/*
KeyMapEntry layoutNUL[rowsCount][columnsCount] = {
  {{NUL},    {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL}},
  {{NUL},    {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL}},
  {{NUL},    {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL}},
  {{NUL},    {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL}},
  {{NUL},    {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL}},
  {{NUL},    {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL},   {NUL}}
};
*/

#endif
