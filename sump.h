#ifndef _SUMP_H
#define _SUMP_H

// https://www.sump.org/projects/analyzer/protocol/

#define SUMP_RESET     0x00
#define SUMP_RUN       0x01
#define SUMP_ID        0x02
#define SUMP_XON       0x11
#define SUMP_XOFF      0x13
#define SUMP_TRG_MASK  0xC0
#define SUMP_TRG_VAL   0xC1
#define SUMP_TRG_CFG   0xC2
#define SUMP_DIVIDER   0x80
#define SUMP_READ      0x81
#define SUMP_FLAGS     0x82

extern void sump_handle(uint8_t cmd);
extern void sump_run();

#endif
