// see https://www.mysensors.org/download/serial_api_20
//
// node-id ; child-sensor-id ; command ; ack ; type ; payload \n

#include "hw.h"
#include "mysensor.h"

#define CMD_PRESENT 0
#define CMD_SET     1

char gBuffer[40];
uint8_t gPosition;

//------------------------------------------------------------------------------
void add_ch(char ch)
{
    gBuffer[gPosition] = ch;
    gPosition++;
}

//------------------------------------------------------------------------------
void add_int(uint8_t n)
{
    if (n > 99)
	add_ch('0' + ((n/100) % 10));
    if (n > 9)
	add_ch('0' + ((n/10) % 10));
    add_ch('0' + (n % 10));
}

//------------------------------------------------------------------------------
char *mysensor_present(uint8_t nodeId,
		       uint8_t childId,
		       uint8_t type)
{
    gPosition = 0;
    
    add_int(nodeId);
    add_ch(';');
    add_int(childId);
    add_ch(';');
    add_int(CMD_PRESENT);
    add_ch(';');
    add_int(0);
    add_ch(';');
    add_int(type);
    add_ch(';');
    add_int(0);    
    add_ch('\r');
    add_ch('\n');
    add_ch(0); // string end mark

    return gBuffer;
}

//------------------------------------------------------------------------------
char *mysensor_set(uint8_t nodeId,
		   uint8_t childId,
		   uint8_t type,
		   int value)
{
    gPosition = 0;
    
    add_int(nodeId);
    add_ch(';');
    add_int(childId);
    add_ch(';');
    add_int(CMD_SET);
    add_ch(';');
    add_int(0);
    add_ch(';');
    add_int(type);
    add_ch(';');
    add_int(value);    
    add_ch('\r');
    add_ch('\n');
    add_ch(0);  // string end mark

    return gBuffer;
}
