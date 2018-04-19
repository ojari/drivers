#pragma once

#define MAX_BUFFER 32

typedef struct buffer
{
    uint8_t position;
    uint8_t size;
    uint8_t data[MAX_BUFFER];
}
buffer_t;


extern void buffer_clear(buffer_t *buf);

extern void buffer_dec(buffer_t *buf, uint16_t val);
extern void buffer_hex8(buffer_t *buf, uint8_t val);
extern void buffer_hex16(buffer_t *buf, uint16_t val);
extern void buffer_ch(buffer_t *buf, uint8_t ch);
extern void buffer_str(buffer_t *buf, const char* str);
extern void buffer_nl(buffer_t *buf);
extern void buffer_remove(buffer_t *buf);
extern uint8_t buffer_get(buffer_t *buf);
extern uint8_t buffer_empty(buffer_t *buf);

#define BUFFER_DATA(buf) (buf->data)
#define BUFFER_SIZE(buf) (buf->size)
