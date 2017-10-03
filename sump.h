#ifndef _SUMP_H
#define _SUMP_H

// https://www.sump.org/projects/analyzer/protocol/
// http://dangerousprototypes.com/docs/The_Logic_Sniffer%27s_extended_SUMP_protocol

#define REAL_SUMP

#ifdef REAL_SUMP
// Real SUMP commands
//
#define SUMP_RESET     0x00
#define SUMP_RUN       0x01
#define SUMP_ID        0x02
#define SUMP_METADATA  0x04
#define SUMP_XON       0x11
#define SUMP_XOFF      0x13
#define SUMP_TRG_MASK  0xC0
#define SUMP_TRG_VAL   0xC1
#define SUMP_TRG_CFG   0xC2
#define SUMP_DIVIDER   0x80
#define SUMP_READ      0x81
#define SUMP_FLAGS     0x82
#else
// Simulated SUMP commands for testing with terminal
//
#define SUMP_RESET     'R'
#define SUMP_RUN       'x'
#define SUMP_ID        'i'
#define SUMP_METADATA  'M'
#define SUMP_XON       'a'
#define SUMP_XOFF      'b'
#define SUMP_TRG_MASK  'm'
#define SUMP_TRG_VAL   'v'
#define SUMP_TRG_CFG   'g'
#define SUMP_DIVIDER   'd'
#define SUMP_READ      'r'
#define SUMP_FLAGS     'f'
#endif

extern void sump_handle(uint8_t cmd);

#endif
