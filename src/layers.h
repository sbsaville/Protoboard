#ifndef LAYERS_H
#define LAYERS_H

#include "main.h"
#include "keydefs.h"
#include "rgbleds.h"

LayoutKey* layout0[rowsCount][columnsCount] = {
  {ESC,    F1,    F2,    F3,    F4,    F5,    F6,    F7,    F8,    F9,     F10,   F11,    F12,    DEL  },
  {TILDE,  NUM1,  NUM2,  NUM3,  NUM4,  NUM5,  NUM6,  NUM7,  NUM8,  NUM9,   NUM0,  MINUS,  EQUAL,  PGDN },
  {TAB,    Q,     W,     E,     R,     T,     Y,     U,     I,     O,      P,     LBRACK, RBRACK, BSLSH},
  {CAPS,   A,     S,     D,     F,     G,     H,     J,     K,     L,      SMCLN, QUOTE,  ENTER,  HOME },
  {LSHFT,  Z,     X,     C,     V,     B,     N,     M,     COMMA, PERIOD, SLASH, RSHFT,  UP,     END  },
  {LCRTL,  LGUI,  LALT,  LYR1,  LYR2,  SPC,   BKSPC, LYR3,  LYR4,  RALT,   RCRTL, LEFT,   DOWN,   RIGHT}
};

LayoutKey* layout1[rowsCount][columnsCount] = {
  {NUL,  F13,   F14,   F15,   F16,   F17,   F18,   F19,   F20,   F21,   F22,   F23,   F24,   NUL},
  {PMUL, PDIV,  PADD,  PSUB,  NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL},
  {PAD7, PAD8,  PAD9,  QUOTE, NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL},
  {PAD4, PAD5,  PAD6,  DBLQ,  NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   ENTER, NUL},
  {PAD1, PAD2,  PAD3,  ENTER, NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL},
  {PAD0, PAD0,  PDOT,  LYR1,  LYR2,  SPC,   BKSPC, NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL}
};

LayoutKey* layout1_2[rowsCount][columnsCount] = {
  {ESC,    F13,   F14,   F15,   F16,   F17,   F18,   F19,   F20,   F21,   F22,   F23,   F24,   DEL},
  {LPAR,   PMUL,  PDIV,  PADD,  PSUB,  RPAR,  NUL,   NUL,   PMUL,  PDIV,  PADD,  PSUB,  DNEQL, NUL},
  {TAB,    PAD7,  PAD8,  PAD9,  CARAT, SQRT,  NUL,   NUL,   PAD7,  PAD8,  PAD9,  CARAT, NUL,   NUL},
  {NUL,    PAD4,  PAD5,  PAD6,  EQUAL, DBLQ,  NUL,   NUL,   PAD4,  PAD5,  PAD6,  NUL,   ENTER, NUL},
  {LSHFT,  PAD1,  PAD2,  PAD3,  PENT,  NUL,   NUL,   NUL,   PAD1,  PAD2,  PAD3,  NUL,   UP,    NMLCK},
  {L12L,   PAD0,  PDOT,  PAD0,  LYR0,  SPC,   BKSPC, LYR0,  PAD0,  PDOT,  PAD0,  LEFT,  DOWN,  L12L}
};

LayoutKey* layout2[rowsCount][columnsCount] = {
  {ESC,    F13,   F14,   F15,   F16,   F17,   F18,   F19,   F20,   F21,   F22,   F23,   F24,   NUL},
  {LPAR,   PMUL,  PDIV,  PADD,  PSUB,  RPAR,  NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL},
  {ALTT,   PAD7,  PAD8,  PAD9,  CARAT, QUOTE, NUL,   UNDS,  NUL,   NUL,   PRCNT, NUL,   NUL,   NUL},
  {NUL,    PAD4,  PAD5,  PAD6,  EQUAL, DBLQ,  MINUS, NUL,   NUL,   PADD,  NUL,   NUL,   ENTER, LCLK},
  {LSHFT,  PAD1,  PAD2,  PAD3,  PENT,  BSLSH, HASH,  AMPS,  NUL,   NUL,   NUL,   NUL,   PGUP,  NMLCK},
  {L12L,   PAD0,  PDOT,  LYR1,  LYR2,  SPC,   BKSPC, LYR3,  NUL,   RALT,  RCRTL, BKSPC, PGDN,  DEL}
};

LayoutKey* layout2_3[rowsCount][columnsCount] = {
  {NUL,    F13,   F14,   F15,   F16,   F17,   F18,   F19,   F20,   F21,   F22,   F23,   F24,   NUL},
  {NUL,    NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL},
  {NUL,    QSTN,  NUL,   EXCLM, ASTR,  NUL,   NUL,   UNDS,  NUL,   NUL,   PRCNT, NUL,   NUL,   NUL},
  {NUL,    AT,    SLASH, DLLR,  NUL,   DEGR,  MINUS, NUL,   NUL,   PADD,  NUL,   NUL,   ENTER, NUL},
  {NUL,    NUL,   ASTR,  CARAT, NUL,   BSLSH, HASH,  AMPS,  NUL,   NUL,   NUL,   NUL,   NUL,   NUL},
  {NUL,    NUL,   NUL,   NUL,   LYR2,  SPC,   BKSPC, LYR3,  NUL,   NUL,   NUL,   NUL,   NUL,   NUL}
};

LayoutKey* layout3[rowsCount][columnsCount] = {
  {NUL,    F13,   F14,   F15,   F16,   F17,   F18,   F19,   F20,   F21,   F22,   F23,   F24,   NUL},
  {NUL,    NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   PLSMNS,DNEQL, NUL},
  {NUL,    QUOTE, DBLQ,  EXCLM, ASTR,  LCHEV, RCHEV, UNDS,  NUL,   NUL,   PIPE,  NUL,   NUL,   NUL},
  {NUL,    NUL,   NUL,   LBRACE,LBRACK,LPAR,  RPAR,  RBRACK,RBRACE,NUL,   NUL,   NUL,   ENTER, NUL},
  {NUL,    NUL,   NUL,   NUL,   CMTST, BSLSH, NUL,   CMTED, LSEQL, GREQL, NUL,   NUL,   PGUP,  NUL},
  {NUL,    NUL,   NUL,   NUL,   LYR2,  ENTER, BKSPC, LYR3,  LYR4,  NUL,   NUL,   BKSPC, PGDN,  DEL}
};

LayoutKey* layout3_4[rowsCount][columnsCount] = {
  {NUL,    SF13,  SF14,  SF15,  SF16,  SF17,  SF18,  SF19,  SF20,  SF21,  SF22,  SF23,  SF24,  NUL},
  {LOOPCT, NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   PMUL,  PDIV,  PADD,  PSUB,  NUL,   NUL},
  {NUL,    NUL,   NUL,   EMCRN, NUL,   NUL,   NUL,   NUL,   PAD7,  PAD8,  PAD9,  CARAT, NUL,   NUL},
  {NUL,    AMRN,  NUL,   NUL,   NUL,   GMAIL, NUL,   NUL,   PAD4,  PAD5,  PAD6,  NUL,   ENTER, NUL},
  {NUL,    NUL,   NUL,   NUL,   NUL,   LNBRK, NUL,   NUL,   PAD1,  PAD2,  PAD3,  NUL,   NUL,   NMLCK},
  {NUL,    NUL,   NUL,   NUL,   NUL,   SPC,   BKSPC, LYR3,  LYR4,  PAD0,  PDOT,  NUL,   NUL,   NUL}
};

LayoutKey* layout4[rowsCount][columnsCount] = {
  {CAPSESC,F13,   F14,   F15,   F16,   F17,   F18,   F19,   F20,   F21,   F22,   F23,   F24,   BKSPC},
  {BR0,    BR1,   BR2,   BR3,   BR4,   BR5,   BR6,   BR7,   BR8,   BR9,   BR10,  NUL,   NUL,   INCR},
  {TAB,    NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   INSRT, NUL,   PSBRK, NUL,   NUL,   DECR},
  {CAPSLSH,NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   SCRLL, NUL,   NUL,   ENTER, NUL},
  {SET0,   NUL,   NUL,   NUL,   NUL,   NUL,   PRNT,  NUL,   NUL,   NUL,   NUL,   RWND,  REC,   FFWD},
  {RLEASE, NUL,   NUL,   NUL,   ALTL,  SPC,   ALTR,  LYR3,  LYR4,  NUL,   NUL,   PREV,  PLYPS, NEXT}
};


/*
LayoutKey* layoutNUL[rowsCount][columnsCount] = {
  {NUL,    NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL},
  {NUL,    NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL},
  {NUL,    NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL},
  {NUL,    NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL},
  {NUL,    NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL},
  {NUL,    NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL,   NUL}
};
*/

#endif
