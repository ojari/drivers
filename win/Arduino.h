#pragma once

#include <string.h>
#include <stdint.h>
#include "hal.h"

/** Error codes
 */
typedef enum errors {
    ERR_MY     = 0x01,
} errorcode_t;

extern void _error(errorcode_t code);


class PcSPI {
public:
    uint8_t transfer(uint8_t data);
};

extern PcSPI SPI;
