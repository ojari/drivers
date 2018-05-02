#include "hw.h"
#include "buffer.h"
#include <stdlib.h>
#include <string.h>

static const char *HEX_DIGIT = "0123456789ABCDEF";

void buffer_clear(buffer_t *buf)
{
    buf->position = 0;
    buf->size = 0;
}

void buffer_dec(buffer_t *buf, uint16_t val)
{
    if (val > 99)
	buffer_ch(buf, '0' + ((val/100) % 10));
    
    //if (val > 9)
    buffer_ch(buf, '0' + ((val/10) % 10));
    
    buffer_ch(buf, '0' + (val % 10));
}

void buffer_hex8(buffer_t *buf, uint8_t value)
{
    buffer_ch(buf, HEX_DIGIT[(value>>4) & 0x0F]);
    buffer_ch(buf, HEX_DIGIT[value & 0x0F]);
}

void buffer_hex16(buffer_t *buf, uint16_t value)
{
    buffer_ch(buf, HEX_DIGIT[(value>>12) & 0x0F]);
    buffer_ch(buf, HEX_DIGIT[(value>>8) & 0x0F]);
    buffer_ch(buf, HEX_DIGIT[(value>>4) & 0x0F]);
    buffer_ch(buf, HEX_DIGIT[value & 0x0F]);
}

void buffer_ch(buffer_t *buf, uint8_t ch)
{
    if (buf->size < MAX_BUFFER) {
	buf->data[buf->size] = ch;
	(buf->size)++;
    }
    else {
	_error(ERR_BUFFER_OVERFLOW);
    }
}

void buffer_str(buffer_t *buf, const char* str)
{
    for (uint8_t i=0; str[i] != 0; i++) {
	buffer_ch(buf, str[i]);
    }
}


void buffer_nl(buffer_t *buf)
{
    buffer_ch(buf, '\r');
    buffer_ch(buf, '\n');
}

void buffer_remove(buffer_t *buf)
{
    if (buf->size > 0)
	(buf->size)--;
}

uint8_t buffer_get(buffer_t *buf)
{
    uint8_t ret;
    if (buf->position < buf->size) {
	ret = buf->data[buf->position];
	(buf->position)++;
    }
    else {
	return 0;
    }
    return ret;
}

uint8_t buffer_empty(buffer_t *buf)
{
    return (buf->position == buf->size);
}
