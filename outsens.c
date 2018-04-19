#include "hw.h"
#include "buffer.h"
#include "outsens.h"

buffer_t outsens_buffer;

//------------------------------------------------------------------------------
void outsens_init()
{
    buffer_clear(&outsens_buffer);
}

//------------------------------------------------------------------------------
char *outsens_set(uint8_t  index,
		  uint16_t values[],
		  uint8_t  count)
{
    uint8_t i;

    buffer_clear(&outsens_buffer);
    
    buffer_dec(&outsens_buffer, index);
    for (i=0; i<count; i++) {
	buffer_ch( &outsens_buffer, ';');
	buffer_dec(&outsens_buffer, values[i]);
    }
    buffer_ch( &outsens_buffer, '\r');
    buffer_ch( &outsens_buffer, '\n');
    buffer_ch( &outsens_buffer, 0);  // string end mark

    return (char*)outsens_buffer.data;
}
