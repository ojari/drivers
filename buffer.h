#pragma once


typedef struct buffer
{
    uint8_t position;
    uint8_t size;
    uint8_t data[50];
}
buffer_t;


extern void buffer_create(buffer_t *buf, uint8_t size);
extern void buffer_reset(buffer_t *buf);
extern void buffer_add_int(buffer_t *buf, uint16_t val);
extern void buffer_add_ch(buffer_t *buf, uint8_t ch);
extern void buffer_add_str(buffer_t *buf, const char* str);
    
