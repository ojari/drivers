#include "hw.h"
#include "ds1820.h"

#define MODE_INPUT  0
#define MODE_OUTPUT 1

#define USE_DS1820B

extern uint8_t ds1820_reset(uint8_t pin);

void ds1820_init(uint8_t pin)
{
	port_mode(pin, MODE_OUTPUT);
	port_set(pin);
}

uint8_t ds1820_reset(uint8_t pin)
{
	uint8_t presence;
    uint8_t stat = ERR_NONE;

	// do reset
	port_clear(pin);
	delay_us(500);   // min 480us
	port_set(pin);
	port_mode(pin, MODE_INPUT);

	// do presense
	delay_us(90);   // wait for DS1820 to send presence
	presence = port_read(pin);
	delay_us(410);
	if (presence)
		stat = ERR_NOT_FOUND;

    port_mode(pin, MODE_OUTPUT);
    
    return stat;
}

void ds1820_write(uint8_t pin, uint8_t data)
{
	uint8_t i;

	for (i=0; i<8; i++) {
		port_clear(pin);
		if (data & (1<<i)) {      // send bit 1
			delay_us(5);
			port_set(pin);
			delay_us(60);
		}
		else {                    // send bit 0
			delay_us(62);
			port_set(pin);
			delay_us(3);			
		}
	}
}

uint8_t ds1820_read(uint8_t pin)
{
	uint8_t i;
	uint8_t ret = 0;

	port_set(pin);
	delay_us(2);
	for (i=1; i; i<<=1) {
		port_clear(pin);
		delay_us(4);
		port_mode(pin, MODE_INPUT);
		delay_us(9);
		if (port_read(pin)) {
		//if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)) {
			ret |= i;
		}
		delay_us(60);
		port_set(pin);
		port_mode(pin, MODE_OUTPUT);
		delay_us(4);
	}
	
	return ret;
}

uint8_t ds1820_measure(uint8_t pin)
{
    uint8_t stat = ERR_NONE;
    
	stat = ds1820_reset(pin);
    if (stat)
        return stat;
        
	ds1820_write(pin, DS1820_CMD_SKIP_ROM);
	ds1820_write(pin, DS1820_CMD_CONVERT);
    
    return stat;
}

// based on DS18S20 OPERATION EXAMPLE 3
//
uint8_t ds1820_read_temp(uint8_t pin)
{
	uint8_t temp_lsb;
	uint8_t temp_msb;
#ifndef USE_DS1820B
	uint8_t count_remain;
	uint8_t count_per_c;
#endif

	ds1820_reset(pin);
	ds1820_write(pin, DS1820_CMD_SKIP_ROM);
	delay_us(3);
	ds1820_write(pin, DS1820_CMD_READ_SCRATCHPAD);


	// Read scratchpad
	//
	temp_lsb = ds1820_read(pin);
	temp_msb = ds1820_read(pin);
	ds1820_read(pin); // Th register or user byte 1
	ds1820_read(pin); // Tl register or user byte 2
	ds1820_read(pin); // reserved
	ds1820_read(pin); // reserved
#ifdef USE_DS1820B
	ds1820_read(pin); // reserved
	ds1820_read(pin); // reserved
#else
	count_remain = ds1820_read(pin);
	count_per_c  = ds1820_read(pin);
#endif
	ds1820_read(pin); // CRC

	ds1820_reset(pin);

	return temp_lsb;
}
