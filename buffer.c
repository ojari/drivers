#include "hw.h"
#include "buffer.h"
#include <stdlib.h>
#include <string.h>

void buffer_create(buffer_t *buf, uint8_t size)
{
    buf->position = 0;
    buf->size = size;
//    buf->data = malloc(sizeof(buffer_t));
}

void buffer_reset(buffer_t *buf)
{
    buf->position = 0;
}

void buffer_add_int(buffer_t *buf, uint16_t val)
{
    if (val > 99)
	buffer_add_ch(buf, '0' + ((val/100) % 10));
    
    if (val > 9)
	buffer_add_ch(buf, '0' + ((val/10) % 10));
    
    buffer_add_ch(buf, '0' + (val % 10));
}

void buffer_add_ch(buffer_t *buf, uint8_t ch)
{
    buf->data[buf->position] = ch;

    (buf->position)++;
}

void buffer_add_str(buffer_t *buf, const char* str)
{
}
