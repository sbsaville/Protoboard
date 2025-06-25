#ifndef KEYDEFS_H
#define KEYDEFS_H

#include "main.h"

typedef CRGB LedColor;
using LedColor = CRGB;

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

struct LayoutKey {
    uint16_t code;
    LedColor* ledColor;
    LedColor defaultColor;
    LayoutKey(uint16_t code, LedColor* ledColor)
        : code(code), ledColor(ledColor), defaultColor(*ledColor) {}
};

LayoutKey _LYR1_       = {LAYER_1,         &Layer};       LayoutKey* LYR1    = &_LYR1_;
LayoutKey _LYR2_       = {LAYER_2,         &Layer};       LayoutKey* LYR2    = &_LYR2_;
LayoutKey _LYR3_       = {LAYER_3,         &Layer};       LayoutKey* LYR3    = &_LYR3_;
LayoutKey _LYR4_       = {LAYER_4,         &Layer};       LayoutKey* LYR4    = &_LYR4_;
LayoutKey _L1_2L_      = {LAYER_1_2L,      &Special};     LayoutKey* L12L    = &_L1_2L_;
LayoutKey _CAPSLSH_    = {KEY_CAPS_SLASH,  &Special};     LayoutKey* CAPSLSH = &_CAPSLSH_;
LayoutKey _CAPSESC_    = {KEY_CAPS_ESC,    &Special};     LayoutKey* CAPSESC = &_CAPSESC_;
LayoutKey _ALTL_       = {KEY_ALTL,        &Special};     LayoutKey* ALTL    = &_ALTL_;
LayoutKey _ALTR_       = {KEY_ALTR,        &Special};     LayoutKey* ALTR    = &_ALTR_;
LayoutKey _LYR0_       = {LAYER_0,         &Layer};       LayoutKey* LYR0    = &_LYR0_;

LayoutKey _RLEASE_     = {KEY_RELEASE,     &Special};     LayoutKey* RLEASE  = &_RLEASE_;
LayoutKey _SET0_       = {KEY_SET0,        &Special};     LayoutKey* SET0    = &_SET0_;
LayoutKey _NULL_       = {KEY_NULL,        &LEDoff};      LayoutKey* NUL     = &_NULL_;

LayoutKey _GMAIL_      = {MACRO_GMAIL,     &Macro};       LayoutKey* GMAIL   = &_GMAIL_;
LayoutKey _HTML_       = {MACRO_HOTMAIL,   &Macro};       LayoutKey* HTML    = &_HTML_;
LayoutKey _AMRN_       = {MACRO_AIMARENA,  &Macro};       LayoutKey* AMRN    = &_AMRN_;
LayoutKey _LNBRK_      = {MACRO_LINEBREAK, &Macro};       LayoutKey* LNBRK   = &_LNBRK_;
LayoutKey _CMTST_      = {CMNTSTRT,        &Macro};       LayoutKey* CMTST   = &_CMTST_;
LayoutKey _CMTED_      = {CMNTEND,         &Macro};       LayoutKey* CMTED   = &_CMTED_;
LayoutKey _LOOPCT_     = {LOOP_COUNT,      &Special};     LayoutKey* LOOPCT  = &_LOOPCT_;
LayoutKey _SQRT_       = {MACRO_SQUAREROOT,&Macro};       LayoutKey* SQRT    = &_SQRT_;

LayoutKey _ESC_        = {KEY_ESC,         &Modifier};    LayoutKey* ESC     = &_ESC_;
LayoutKey _F1_         = {KEY_F1,          &FKeys1};      LayoutKey* F1      = &_F1_;
LayoutKey _F2_         = {KEY_F2,          &FKeys1};      LayoutKey* F2      = &_F2_;
LayoutKey _F3_         = {KEY_F3,          &FKeys1};      LayoutKey* F3      = &_F3_;
LayoutKey _F4_         = {KEY_F4,          &FKeys1};      LayoutKey* F4      = &_F4_;
LayoutKey _F5_         = {KEY_F5,          &FKeys1b};     LayoutKey* F5      = &_F5_;
LayoutKey _F6_         = {KEY_F6,          &FKeys1b};     LayoutKey* F6      = &_F6_;
LayoutKey _F7_         = {KEY_F7,          &FKeys1b};     LayoutKey* F7      = &_F7_;
LayoutKey _F8_         = {KEY_F8,          &FKeys1b};     LayoutKey* F8      = &_F8_;
LayoutKey _F9_         = {KEY_F9,          &FKeys1};      LayoutKey* F9      = &_F9_;
LayoutKey _F10_        = {KEY_F10,         &FKeys1};      LayoutKey* F10     = &_F10_;
LayoutKey _F11_        = {KEY_F11,         &FKeys1};      LayoutKey* F11     = &_F11_;
LayoutKey _F12_        = {KEY_F12,         &FKeys1};      LayoutKey* F12     = &_F12_;
LayoutKey _F13_        = {KEY_F13,         &FKeys2};      LayoutKey* F13     = &_F13_;
LayoutKey _F14_        = {KEY_F14,         &FKeys2};      LayoutKey* F14     = &_F14_;
LayoutKey _F15_        = {KEY_F15,         &FKeys2};      LayoutKey* F15     = &_F15_;
LayoutKey _F16_        = {KEY_F16,         &FKeys2};      LayoutKey* F16     = &_F16_;
LayoutKey _F17_        = {KEY_F17,         &FKeys2b};     LayoutKey* F17     = &_F17_;
LayoutKey _F18_        = {KEY_F18,         &FKeys2b};     LayoutKey* F18     = &_F18_;
LayoutKey _F19_        = {KEY_F19,         &FKeys2b};     LayoutKey* F19     = &_F19_;
LayoutKey _F20_        = {KEY_F20,         &FKeys2b};     LayoutKey* F20     = &_F20_;
LayoutKey _F21_        = {KEY_F21,         &FKeys2};      LayoutKey* F21     = &_F21_;
LayoutKey _F22_        = {KEY_F22,         &FKeys2};      LayoutKey* F22     = &_F22_;
LayoutKey _F23_        = {KEY_F23,         &FKeys2};      LayoutKey* F23     = &_F23_;
LayoutKey _F24_        = {KEY_F24,         &FKeys2};      LayoutKey* F24     = &_F24_;

LayoutKey _PRNT_       = {KEY_PRINTSCREEN, &Special};     LayoutKey* PRNT    = &_PRNT_;
LayoutKey _SCRLL_      = {KEY_SCROLL_LOCK, &Scrllock};    LayoutKey* SCRLL   = &_SCRLL_;
LayoutKey _PSBRK_      = {KEY_PAUSE,       &Special};     LayoutKey* PSBRK   = &_PSBRK_;

LayoutKey _NUM1_       = {KEY_1,           &Number};      LayoutKey* NUM1    = &_NUM1_;
LayoutKey _NUM2_       = {KEY_2,           &Number};      LayoutKey* NUM2    = &_NUM2_;
LayoutKey _NUM3_       = {KEY_3,           &Number};      LayoutKey* NUM3    = &_NUM3_;
LayoutKey _NUM4_       = {KEY_4,           &Number};      LayoutKey* NUM4    = &_NUM4_;
LayoutKey _NUM5_       = {KEY_5,           &Number};      LayoutKey* NUM5    = &_NUM5_;
LayoutKey _NUM6_       = {KEY_6,           &Number};      LayoutKey* NUM6    = &_NUM6_;
LayoutKey _NUM7_       = {KEY_7,           &Number};      LayoutKey* NUM7    = &_NUM7_;
LayoutKey _NUM8_       = {KEY_8,           &Number};      LayoutKey* NUM8    = &_NUM8_;
LayoutKey _NUM9_       = {KEY_9,           &Number};      LayoutKey* NUM9    = &_NUM9_;
LayoutKey _NUM0_       = {KEY_0,           &Number};      LayoutKey* NUM0    = &_NUM0_;
LayoutKey _MINUS_      = {KEY_MINUS,       &Chara1};      LayoutKey* MINUS   = &_MINUS_;
LayoutKey _EQUAL_      = {KEY_EQUAL,       &Chara1};      LayoutKey* EQUAL   = &_EQUAL_;
LayoutKey _BSLSH_      = {KEY_BACKSLASH,   &Chara1};      LayoutKey* BSLSH   = &_BSLSH_;
LayoutKey _BKSPC_      = {KEY_BACKSPACE,   &Letter};      LayoutKey* BKSPC   = &_BKSPC_;

LayoutKey _INSRT_      = {KEY_INSERT,      &Chara1};      LayoutKey* INSRT   = &_INSRT_;
LayoutKey _DEL_        = {KEY_DELETE,      &Modifier};    LayoutKey* DEL     = &_DEL_;
LayoutKey _HOME_       = {KEY_HOME,        &Modifier};    LayoutKey* HOME    = &_HOME_;
LayoutKey _END_        = {KEY_END,         &Modifier};    LayoutKey* END     = &_END_;
LayoutKey _PGUP_       = {KEY_PAGE_UP,     &Modifier};    LayoutKey* PGUP    = &_PGUP_;
LayoutKey _PGDN_       = {KEY_PAGE_DOWN,   &Modifier};    LayoutKey* PGDN    = &_PGDN_;
LayoutKey _UP_         = {KEY_UP_ARROW,    &Nav};         LayoutKey* UP      = &_UP_;
LayoutKey _DOWN_       = {KEY_DOWN_ARROW,  &Nav};         LayoutKey* DOWN    = &_DOWN_;
LayoutKey _LEFT_       = {KEY_LEFT_ARROW,  &Nav};         LayoutKey* LEFT    = &_LEFT_;
LayoutKey _RIGHT_      = {KEY_RIGHT_ARROW, &Nav};         LayoutKey* RIGHT   = &_RIGHT_;

LayoutKey _NMLCK_      = {KEY_NUM_LOCK,    &Numlock};     LayoutKey* NMLCK   = &_NMLCK_;
LayoutKey _PDIV_       = {KEYPAD_SLASH,    &Chara2};      LayoutKey* PDIV    = &_PDIV_;
LayoutKey _PMUL_       = {KEYPAD_ASTERIX,  &Chara2};      LayoutKey* PMUL    = &_PMUL_;
LayoutKey _PADD_       = {KEYPAD_PLUS,     &Chara2};      LayoutKey* PADD    = &_PADD_;
LayoutKey _PSUB_       = {KEYPAD_MINUS,    &Chara2};      LayoutKey* PSUB    = &_PSUB_;
LayoutKey _PENT_       = {KEYPAD_ENTER,    &Letter};      LayoutKey* PENT    = &_PENT_;
LayoutKey _PAD0_       = {KEYPAD_0,        &Number};      LayoutKey* PAD0    = &_PAD0_;
LayoutKey _PAD1_       = {KEYPAD_1,        &Number};      LayoutKey* PAD1    = &_PAD1_;
LayoutKey _PAD2_       = {KEYPAD_2,        &Numnav};      LayoutKey* PAD2    = &_PAD2_;
LayoutKey _PAD3_       = {KEYPAD_3,        &Number};      LayoutKey* PAD3    = &_PAD3_;
LayoutKey _PAD4_       = {KEYPAD_4,        &Numnav};      LayoutKey* PAD4    = &_PAD4_;
LayoutKey _PAD5_       = {KEYPAD_5,        &Number};      LayoutKey* PAD5    = &_PAD5_;
LayoutKey _PAD6_       = {KEYPAD_6,        &Numnav};      LayoutKey* PAD6    = &_PAD6_;
LayoutKey _PAD7_       = {KEYPAD_7,        &Number};      LayoutKey* PAD7    = &_PAD7_;
LayoutKey _PAD8_       = {KEYPAD_8,        &Numnav};      LayoutKey* PAD8    = &_PAD8_;
LayoutKey _PAD9_       = {KEYPAD_9,        &Number};      LayoutKey* PAD9    = &_PAD9_;
LayoutKey _PDOT_       = {KEYPAD_PERIOD,   &Chara2};      LayoutKey* PDOT    = &_PDOT_;

LayoutKey _TAB_        = {KEY_TAB,         &Modifier};    LayoutKey* TAB     = &_TAB_;
LayoutKey _TILDE_      = {KEY_TILDE,       &Chara1};      LayoutKey* TILDE   = &_TILDE_;
LayoutKey _CAPS_       = {KEY_CAPS_LOCK,   &Capslock};    LayoutKey* CAPS    = &_CAPS_;
LayoutKey _LSHFT_      = {KEY_LEFT_SHIFT,  &Modifier};    LayoutKey* LSHFT   = &_LSHFT_;
LayoutKey _LCRTL_      = {KEY_LEFT_CTRL,   &Modifier};    LayoutKey* LCRTL   = &_LCRTL_;
LayoutKey _LGUI_       = {KEY_LEFT_GUI,    &Modifier};    LayoutKey* LGUI    = &_LGUI_;
LayoutKey _LALT_       = {KEY_LEFT_ALT,    &Modifier};    LayoutKey* LALT    = &_LALT_;
LayoutKey _SPC_        = {KEY_SPACE,       &Letter};      LayoutKey* SPC     = &_SPC_;

LayoutKey _Q_          = {KEY_Q,           &Letter};      LayoutKey* Q       = &_Q_;
LayoutKey _W_          = {KEY_W,           &Letter};      LayoutKey* W       = &_W_;
LayoutKey _E_          = {KEY_E,           &Letter};      LayoutKey* E       = &_E_;
LayoutKey _R_          = {KEY_R,           &Letter};      LayoutKey* R       = &_R_;
LayoutKey _T_          = {KEY_T,           &Letter};      LayoutKey* T       = &_T_;
LayoutKey _Y_          = {KEY_Y,           &Letter};      LayoutKey* Y       = &_Y_;
LayoutKey _U_          = {KEY_U,           &Letter};      LayoutKey* U       = &_U_;
LayoutKey _I_          = {KEY_I,           &Letter};      LayoutKey* I       = &_I_;
LayoutKey _O_          = {KEY_O,           &Letter};      LayoutKey* O       = &_O_;
LayoutKey _P_          = {KEY_P,           &Letter};      LayoutKey* P       = &_P_;
LayoutKey _A_          = {KEY_A,           &Letter};      LayoutKey* A       = &_A_;
LayoutKey _S_          = {KEY_S,           &Letter};      LayoutKey* S       = &_S_;
LayoutKey _D_          = {KEY_D,           &Letter};      LayoutKey* D       = &_D_;
LayoutKey _F_          = {KEY_F,           &Letter};      LayoutKey* F       = &_F_;
LayoutKey _G_          = {KEY_G,           &Letter};      LayoutKey* G       = &_G_;
LayoutKey _H_          = {KEY_H,           &Letter};      LayoutKey* H       = &_H_;
LayoutKey _J_          = {KEY_J,           &Letter};      LayoutKey* J       = &_J_;
LayoutKey _K_          = {KEY_K,           &Letter};      LayoutKey* K       = &_K_;
LayoutKey _L_          = {KEY_L,           &Letter};      LayoutKey* L       = &_L_;
LayoutKey _Z_          = {KEY_Z,           &Letter};      LayoutKey* Z       = &_Z_;
LayoutKey _X_          = {KEY_X,           &Letter};      LayoutKey* X       = &_X_;
LayoutKey _C_          = {KEY_C,           &Letter};      LayoutKey* C       = &_C_;
LayoutKey _V_          = {KEY_V,           &Letter};      LayoutKey* V       = &_V_;
LayoutKey _B_          = {KEY_B,           &Letter};      LayoutKey* B       = &_B_;
LayoutKey _N_          = {KEY_N,           &Letter};      LayoutKey* N       = &_N_;
LayoutKey _M_          = {KEY_M,           &Letter};      LayoutKey* M       = &_M_;

LayoutKey _LBRACK_     = {KEY_LEFT_BRACE,   &Chara1};     LayoutKey* LBRACK  = &_LBRACK_;
LayoutKey _RBRACK_     = {KEY_RIGHT_BRACE,  &Chara1};     LayoutKey* RBRACK  = &_RBRACK_;
LayoutKey _SMCLN_      = {KEY_SEMICOLON,    &Chara1};     LayoutKey* SMCLN   = &_SMCLN_;
LayoutKey _QUOTE_      = {KEY_QUOTE,        &Chara1};     LayoutKey* QUOTE   = &_QUOTE_;
LayoutKey _ENTER_      = {KEY_ENTER,        &Letter};     LayoutKey* ENTER   = &_ENTER_;
LayoutKey _COMMA_      = {KEY_COMMA,        &Chara1};     LayoutKey* COMMA   = &_COMMA_;
LayoutKey _PERIOD_     = {KEY_PERIOD,       &Chara1};     LayoutKey* PERIOD  = &_PERIOD_;
LayoutKey _SLASH_      = {KEY_SLASH,        &Chara1};     LayoutKey* SLASH   = &_SLASH_;
LayoutKey _RSHFT_      = {KEY_RIGHT_SHIFT,  &Modifier};   LayoutKey* RSHFT   = &_RSHFT_;
LayoutKey _RCRTL_      = {KEY_RIGHT_CTRL,   &Modifier};   LayoutKey* RCRTL   = &_RCRTL_;
LayoutKey _RGUI_       = {KEY_RIGHT_GUI,    &Modifier};   LayoutKey* RGUI    = &_RGUI_;
LayoutKey _RALT_       = {KEY_RIGHT_ALT,    &Modifier};   LayoutKey* RALT    = &_RALT_;
// The context menu key goes here when I find out what it is
LayoutKey _MUTE_       = {KEY_MEDIA_MUTE,         &Modifier}; LayoutKey* MUTE  = &_MUTE_;
LayoutKey _PREV_       = {KEY_MEDIA_PREV_TRACK,   &Special};  LayoutKey* PREV  = &_PREV_;
LayoutKey _NEXT_       = {KEY_MEDIA_NEXT_TRACK,   &Special};  LayoutKey* NEXT  = &_NEXT_;
LayoutKey _RWND_       = {KEY_MEDIA_REWIND,       &Special};  LayoutKey* RWND  = &_RWND_;
LayoutKey _FFWD_       = {KEY_MEDIA_FAST_FORWARD, &Special};  LayoutKey* FFWD  = &_FFWD_;
LayoutKey _REC_        = {KEY_MEDIA_RECORD,       &Special};  LayoutKey* REC   = &_REC_;
LayoutKey _PLYPS_      = {KEY_MEDIA_PLAY_PAUSE,   &Special};  LayoutKey* PLYPS = &_PLYPS_;
LayoutKey _VUP_        = {KEY_MEDIA_VOLUME_INC,   &Modifier}; LayoutKey* VUP   = &_VUP_;
LayoutKey _VDN_        = {KEY_MEDIA_VOLUME_DEC,   &Modifier}; LayoutKey* VDN   = &_VDN_;

LayoutKey _EXCLM_      = {EXCLMAMATION,     &Chara2};     LayoutKey* EXCLM   = &_EXCLM_;
LayoutKey _AT_         = {KEY_AT,           &Chara2};     LayoutKey* AT      = &_AT_;
LayoutKey _HASH_       = {KEY_HASH,         &Chara2};     LayoutKey* HASH    = &_HASH_;
LayoutKey _DLLR_       = {KEY_DOLLAR,       &Chara2};     LayoutKey* DLLR    = &_DLLR_;
LayoutKey _PRCNT_      = {KEY_PERCENT,      &Chara2};     LayoutKey* PRCNT   = &_PRCNT_;
LayoutKey _CARAT_      = {KEY_CARAT,        &Chara2};     LayoutKey* CARAT   = &_CARAT_;
LayoutKey _AMPS_       = {AMPERSAND,        &Chara2};     LayoutKey* AMPS    = &_AMPS_;
LayoutKey _ASTR_       = {KEY_ASTERISK,     &Chara2};     LayoutKey* ASTR    = &_ASTR_;
LayoutKey _LPAR_       = {L_PARENTHESIS,    &Chara2};     LayoutKey* LPAR    = &_LPAR_;
LayoutKey _RPAR_       = {R_PARENTHESIS,    &Chara2};     LayoutKey* RPAR    = &_RPAR_;
LayoutKey _UNDS_       = {UNDERSCORE,       &Chara2};     LayoutKey* UNDS    = &_UNDS_;
LayoutKey _PIPE_       = {KEY_PIPE,         &Chara2};     LayoutKey* PIPE    = &_PIPE_;
LayoutKey _LCHEV_      = {LEFT_CHEVRON,     &Chara2};     LayoutKey* LCHEV   = &_LCHEV_;
LayoutKey _RCHEV_      = {RIGHT_CHEVRON,    &Chara2};     LayoutKey* RCHEV   = &_RCHEV_;
LayoutKey _GREQL_      = {GREAT_EQUAL,      &Chara2};     LayoutKey* GREQL   = &_GREQL_;
LayoutKey _LSEQL_      = {LESS_EQUAL,       &Chara2};     LayoutKey* LSEQL   = &_LSEQL_;
LayoutKey _DNEQL_      = {NOT_EQUAL,        &Chara2};     LayoutKey* DNEQL   = &_DNEQL_;
LayoutKey _PLSMNS_     = {PLUS_MINUS,       &Chara2};     LayoutKey* PLSMNS  = &_PLSMNS_;
LayoutKey _QSTN_       = {QUESTION_MARK,    &Chara2};     LayoutKey* QSTN    = &_QSTN_;
LayoutKey _COLN_       = {KEY_COLON,        &Chara2};     LayoutKey* COLN    = &_COLN_;
LayoutKey _DBLQ_       = {KEY_DBLQUOTE,     &Chara2};     LayoutKey* DBLQ    = &_DBLQ_;
LayoutKey _LBRACE_     = {CURL_L_BRACE,     &Chara2};     LayoutKey* LBRACE  = &_LBRACE_;
LayoutKey _RBRACE_     = {CURL_R_BRACE,     &Chara2};     LayoutKey* RBRACE  = &_RBRACE_;
LayoutKey _TILD_       = {SHIFT_TILDE,      &Chara2};     LayoutKey* TILD    = &_TILD_;
LayoutKey _PLUS_       = {KEY_PLUS,         &Chara2};     LayoutKey* PLUS    = &_PLUS_;
LayoutKey _DEGR_       = {KEY_DEGREES,      &Chara2};     LayoutKey* DEGR    = &_DEGR_;
LayoutKey _TRL1_       = {TRILL_MODE1,      &Special};    LayoutKey* TRL1    = &_TRL1_;
LayoutKey _TRL2_       = {TRILL_MODE2,      &Special};    LayoutKey* TRL2    = &_TRL2_;
LayoutKey _TRL3_       = {TRILL_MODE3,      &Special};    LayoutKey* TRL3    = &_TRL3_;
LayoutKey _ALTT_       = {KEY_ALT_TAB,      &Special};    LayoutKey* ALTT    = &_ALTT_;
LayoutKey _RBOT_       = {KEY_REBOOT,       &Special};    LayoutKey* RBOT    = &_RBOT_;
LayoutKey _LCLK_       = {MOUSE_LCLICK,     &Special};    LayoutKey* LCLK    = &_LCLK_;
LayoutKey _RCLK_       = {MOUSE_RCLICK,     &Special};    LayoutKey* RCLK    = &_RCLK_;
LayoutKey _BR0_        = {LEDS_BR0,         &LedAdj};     LayoutKey* BR0     = &_BR0_;
LayoutKey _BR1_        = {LEDS_BR1,         &LedAdj};     LayoutKey* BR1     = &_BR1_;
LayoutKey _BR2_        = {LEDS_BR2,         &LedAdj};     LayoutKey* BR2     = &_BR2_;
LayoutKey _BR3_        = {LEDS_BR3,         &LedAdj};     LayoutKey* BR3     = &_BR3_;
LayoutKey _BR4_        = {LEDS_BR4,         &LedAdj};     LayoutKey* BR4     = &_BR4_;
LayoutKey _BR5_        = {LEDS_BR5,         &LedAdj};     LayoutKey* BR5     = &_BR5_;
LayoutKey _BR6_        = {LEDS_BR6,         &LedAdj};     LayoutKey* BR6     = &_BR6_;
LayoutKey _BR7_        = {LEDS_BR7,         &LedAdj};     LayoutKey* BR7     = &_BR7_;
LayoutKey _BR8_        = {LEDS_BR8,         &LedAdj};     LayoutKey* BR8     = &_BR8_;
LayoutKey _BR9_        = {LEDS_BR9,         &LedAdj};     LayoutKey* BR9     = &_BR9_;
LayoutKey _BR10_       = {LEDS_BR10,        &LedAdj};     LayoutKey* BR10    = &_BR10_;
LayoutKey _INCR_       = {LEDS_INC,         &LedAdj};     LayoutKey* INCR    = &_INCR_;
LayoutKey _DECR_       = {LEDS_DEC,         &LedAdj};     LayoutKey* DECR    = &_DECR_;
LayoutKey _EMCRN_      = {E_MACRON,         &Letter};     LayoutKey* EMCRN   = &_EMCRN_;

LayoutKey _SF13_       = {KEYSF13,          &FKeys2b};    LayoutKey* SF13    = &_SF13_;
LayoutKey _SF14_       = {KEYSF14,          &FKeys2b};    LayoutKey* SF14    = &_SF14_;
LayoutKey _SF15_       = {KEYSF15,          &FKeys2b};    LayoutKey* SF15    = &_SF15_;
LayoutKey _SF16_       = {KEYSF16,          &FKeys2b};    LayoutKey* SF16    = &_SF16_;
LayoutKey _SF17_       = {KEYSF17,          &FKeys2};     LayoutKey* SF17    = &_SF17_;
LayoutKey _SF18_       = {KEYSF18,          &FKeys2};     LayoutKey* SF18    = &_SF18_;
LayoutKey _SF19_       = {KEYSF19,          &FKeys2};     LayoutKey* SF19    = &_SF19_;
LayoutKey _SF20_       = {KEYSF20,          &FKeys2};     LayoutKey* SF20    = &_SF20_;
LayoutKey _SF21_       = {KEYSF21,          &FKeys2b};    LayoutKey* SF21    = &_SF21_;
LayoutKey _SF22_       = {KEYSF22,          &FKeys2b};    LayoutKey* SF22    = &_SF22_;
LayoutKey _SF23_       = {KEYSF23,          &FKeys2b};    LayoutKey* SF23    = &_SF23_;
LayoutKey _SF24_       = {KEYSF24,          &FKeys2b};    LayoutKey* SF24    = &_SF24_;





#endif