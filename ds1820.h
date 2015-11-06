#ifndef __DS18B20_H
#define __DS18B20_H

//
// http://datasheets.maximintegrated.com/en/ds/DS18S20.pdf
// http://datasheets.maximintegrated.com/en/ds/DS18B20.pdf

#define DS1820_CMD_CONVERT           0x44
#define DS1820_CMD_WRITE_SCRATCHPAD  0x4E
#define DS1820_CMD_READ_SCRATCHPAD   0xBE
#define DS1820_CMD_SKIP_ROM          0xCC

extern void ds1820_init(uint8_t pin);
extern void ds1820_write(uint8_t pin, uint8_t data);
extern uint8_t ds1820_measure(uint8_t pin);
extern uint8_t ds1820_read_temp(uint8_t pin);

#endif
