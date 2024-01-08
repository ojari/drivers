#pragma once

#include <string.h>
#include <stdint.h>
#include "hal.h"

/** Error codes
 */
typedef enum errors {
    ERR_MY     = 0x01,
    ERR_SPI_OPEN,
    ERR_SPI_SET_MODE,
    ERR_SPI_SET_BITS,
    ERR_SPI_SET_SPEED,
    ERR_SPI_TRANSFER,
    ERR_GPIO_INIT,
    ERR_GPIO_GETLINE,
    ERR_GPIO_MODE_OUT,
    ERR_GPIO_MODE_IN,
    ERR_GPIO_INVALID_MODE
} errorcode_t;

extern void _error(errorcode_t code);
extern void digitalInit();

class PcSPI {
public:
    void beginTransaction(const SPISettings& set);
    uint8_t transfer(uint8_t data);
    void endTransaction();
private:
    int fd;
};

extern PcSPI SPI;
