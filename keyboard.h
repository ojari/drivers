#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <stdint.h>

#define KEYBOARD_ROWS 2
#define KEYBOARD_COLS 2
#define KEYBOARD_LAYOUTS 3

// USB HID keyboard IDs
// see http://www.usb.org/developers/hidpage/Hut1_12v2.pdf
//
#define K_A      0x04
#define K_B      0x05
#define K_C      0x06
#define K_D      0x07
#define K_E      0x08
#define K_F      0x09
#define K_G      0x0A
#define K_H      0x0B
#define K_I      0x0C
#define K_J      0x0D
#define K_K      0x0E
#define K_L      0x0F
#define K_M      0x10
#define K_N      0x11
#define K_O      0x12
#define K_P      0x13
#define K_Q      0x14
#define K_R      0x15
#define K_S      0x16
#define K_T      0x17
#define K_U      0x18
#define K_V      0x19
#define K_W      0x1A
#define K_X      0x1B
#define K_Y      0x1C
#define K_Z      0x1D

#define K_1      0x1E
#define K_2      0x1F
#define K_3      0x20
#define K_4      0x21
#define K_5      0x22
#define K_6      0x23
#define K_7      0x24
#define K_8      0x25
#define K_9      0x26
#define K_0      0x27

#define K_RETURN 0x28
#define K_ESC    0x29
#define K_BACKSP 0x2A
#define K_TAB    0x2B
#define K_SPACE  0x2C
#define K_MINUS  0x2D
#define K_EQUAL  0x2E
#define K_LBRACK 0x2F
#define K_RBRACK 0x30
#define K_BSLASH 0x31
#define K_HASH   0x32
#define K_SEMICO 0x33
#define K_QUOTE  0x34
#define K_TILDE  0x35
#define K_COMMA  0x36
#define K_PERIOD 0x37
#define K_SLASH  0x38
#define K_CAPSLK 0x39
#define K_F1     0x3A
#define K_F2     0x3B
#define K_F3     0x3C
#define K_F4     0x3D
#define K_F5     0x3E
#define K_F6     0x3F
#define K_F7     0x40
#define K_F8     0x41
#define K_F9     0x42
#define K_F10    0x43
#define K_F11    0x44
#define K_F12    0x45

#define K_RIGHT  0x4F
#define K_LEFT   0x50
#define K_DOWN   0x51
#define K_UP     0x52

#define K_LCTRL  0xE0
#define K_LSHIFT 0xE1
#define K_LALT   0xE2
#define K_LGUI   0xE3
#define K_RCTRL  0xE4
#define K_RSHIFT 0xE5
#define K_RALT   0xE6
#define K_RGUI   0xE7


typedef struct {
    uint8_t pin_rows[KEYBOARD_ROWS];
    uint8_t pin_cols[KEYBOARD_COLS];
    uint8_t modifiers;
} keyboard; 

extern void keyboard_init(keyboard *self);
extern void keyboard_scan(keyboard *self);

#endif // __KEYBOARD_H
