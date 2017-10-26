#include "hw.h"
#include "ds1820.h"

#define USE_DS1820B

extern uint8_t ds1820_reset(uint8_t pin);

//------------------------------------------------------------------------------
void ds1820_init(uint8_t pin)
{
	io_mode(pin, IO_MODE_OUTPUT);
	io_set(pin);
}

//------------------------------------------------------------------------------
uint8_t ds1820_reset(uint8_t pin)
{
	uint8_t presence;
    uint8_t stat = ERR_NONE;

	// do reset
	io_clear(pin);
	delay_us(500);   // min 480us
	io_set(pin);
	io_mode(pin, IO_MODE_INPUT);

	// do presense
	delay_us(90);   // wait for DS1820 to send presence
	presence = io_read(pin);
	delay_us(410);
	if (presence)
		stat = ERR_NOT_FOUND;

    io_mode(pin, IO_MODE_OUTPUT);
    
    return stat;
}

//------------------------------------------------------------------------------
void ds1820_write(uint8_t pin, uint8_t data)
{
	uint8_t i;

	for (i=0; i<8; i++) {
		io_clear(pin);
		if (data & (1<<i)) {      // send bit 1
			delay_us(5);
			io_set(pin);
			delay_us(60);
		}
		else {                    // send bit 0
			delay_us(62);
			io_set(pin);
			delay_us(3);			
		}
	}
}

//------------------------------------------------------------------------------
uint8_t ds1820_read(uint8_t pin)
{
    uint8_t i;
    uint8_t ret = 0;

    io_set(pin);
    delay_us(2);
    for (i=1; i; i<<=1) {
	io_clear(pin);
	delay_us(4);
	io_mode(pin, IO_MODE_INPUT);
	delay_us(9);
	if (io_read(pin)) {
	    //if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13)) {
	    ret |= i;
	}
	delay_us(60);
	io_set(pin);
	io_mode(pin, IO_MODE_OUTPUT);
	delay_us(4);
    }
	
    return ret;
}

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
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

unsigned char ROM_NO[8];
uint8_t LastDiscrepancy;
uint8_t LastFamilyDiscrepancy;
uint8_t LastDeviceFlag;

uint8_t read_bit()
{
    return 0;
}
void write_bit()
{
}

// NOTE: this function is copied from energia onewire.cpp
//
uint8_t ds1820_search(uint8_t pin, uint8_t *newAddr)
{
    uint8_t id_bit_number;
    uint8_t last_zero, rom_byte_number, search_result;
    uint8_t id_bit, cmp_id_bit;
    unsigned char rom_byte_mask, search_direction;

    // initialize for search
    id_bit_number = 1;
    last_zero = 0;
    rom_byte_number = 0;
    rom_byte_mask = 1;
    search_result = 0;

    // if the last call was not the last one
    if (!LastDeviceFlag) { 
	// 1-Wire reset
	if (ds1820_reset(pin)) {
	    // reset the search
	    LastDiscrepancy = 0;
	    LastDeviceFlag = FALSE;
	    LastFamilyDiscrepancy = 0;
	    return FALSE;
	}

	ds1820_write(pin, DS1820_CMD_SEARCH);

	// loop to do the search
	do {
	    // read a bit and its complement
	    id_bit = read_bit();
	    cmp_id_bit = read_bit();

	    // check for no devices on 1-wire
	    if ((id_bit == 1) && (cmp_id_bit == 1))
		break;
	    else {
		// all devices coupled have 0 or 1
		if (id_bit != cmp_id_bit)
		    search_direction = id_bit;  // bit write value for search
		else {
		    // if this discrepancy if before the Last Discrepancy
		    // on a previous next then pick the same as last time
		    if (id_bit_number < LastDiscrepancy)
			search_direction = ((ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
		    else
			// if equal to last pick 1, if not then pick 0
			search_direction = (id_bit_number == LastDiscrepancy);

		    // if 0 was picked then record its position in LastZero
		    if (search_direction == 0) {
			last_zero = id_bit_number;

			// check for Last discrepancy in family
			if (last_zero < 9)
			    LastFamilyDiscrepancy = last_zero;
		    }
		}

		// set or clear the bit in the ROM byte rom_byte_number
		// with mask rom_byte_mask
		if (search_direction == 1)
		    ROM_NO[rom_byte_number] |= rom_byte_mask;
		else
		    ROM_NO[rom_byte_number] &= ~rom_byte_mask;

		// serial number search direction write bit
		write_bit(search_direction);

		// increment the byte counter id_bit_number
		// and shift the mask rom_byte_mask
		id_bit_number++;
		rom_byte_mask <<= 1;

		// if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
		if (rom_byte_mask == 0) {
		    rom_byte_number++;
		    rom_byte_mask = 1;
		}
	    }
	}
	while(rom_byte_number < 8);  // loop until through all ROM bytes 0-7

	// if the search was successful then
	if (!(id_bit_number < 65)) {
	    // search successful so set LastDiscrepancy,LastDeviceFlag,search_result
	    LastDiscrepancy = last_zero;

	    // check for last device
	    if (LastDiscrepancy == 0)
		LastDeviceFlag = TRUE;

	    search_result = TRUE;
	}
    }

    // if no device found then reset counters so next 'search' will be like a first
    if (!search_result || !ROM_NO[0]) {
	LastDiscrepancy = 0;
	LastDeviceFlag = FALSE;
	LastFamilyDiscrepancy = 0;
	search_result = FALSE;
    }
    for (int i = 0; i < 8; i++)
	newAddr[i] = ROM_NO[i];
    return search_result;
}
