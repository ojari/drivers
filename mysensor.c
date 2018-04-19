// see https://www.mysensors.org/download/serial_api_20
//
// node-id ; child-sensor-id ; command ; ack ; type ; payload \n

#include "hw.h"
#include "buffer.h"
#include "mysensor.h"

#define CMD_PRESENT 0
#define CMD_SET     1

buffer_t mysensor_buffer;

//------------------------------------------------------------------------------
void mysensor_init()
{
}

//------------------------------------------------------------------------------
char *mysensor_present(uint8_t nodeId,
		       uint8_t childId,
		       uint8_t type)
{
    buffer_clear(&mysensor_buffer);
    
    buffer_dec(&mysensor_buffer, nodeId);
    buffer_ch( &mysensor_buffer, ';');
    buffer_dec(&mysensor_buffer, childId);
    buffer_ch( &mysensor_buffer, ';');
    buffer_dec(&mysensor_buffer, CMD_PRESENT);
    buffer_ch( &mysensor_buffer, ';');
    buffer_dec(&mysensor_buffer, 0);
    buffer_ch( &mysensor_buffer, ';');
    buffer_dec(&mysensor_buffer, type);
    buffer_ch( &mysensor_buffer, ';');
    buffer_dec(&mysensor_buffer, 0);    
    buffer_ch( &mysensor_buffer, '\r');
    buffer_ch( &mysensor_buffer, '\n');
    buffer_ch( &mysensor_buffer, 0); // string end mark

    return (char*)mysensor_buffer.data;
}

//------------------------------------------------------------------------------
char *mysensor_set(uint8_t nodeId,
		   uint8_t childId,
		   uint8_t type,
		   int value)
{
    buffer_clear(&mysensor_buffer);
    
    buffer_dec(&mysensor_buffer, nodeId);
    buffer_ch( &mysensor_buffer, ';');
    buffer_dec(&mysensor_buffer, childId);
    buffer_ch( &mysensor_buffer, ';');
    buffer_dec(&mysensor_buffer, CMD_SET);
    buffer_ch( &mysensor_buffer, ';');
    buffer_dec(&mysensor_buffer, 0);
    buffer_ch( &mysensor_buffer, ';');
    buffer_dec(&mysensor_buffer, type);
    buffer_ch( &mysensor_buffer, ';');
    buffer_dec(&mysensor_buffer, value);    
    buffer_ch( &mysensor_buffer, '\r');
    buffer_ch( &mysensor_buffer, '\n');
    buffer_ch( &mysensor_buffer, 0);  // string end mark

    return (char*)mysensor_buffer.data;
}
