#include "hw.h"
#include "hal.h"

static const char *HEX_DIGIT = "0123456789ABCDEF";

//------------------------------------------------------------------------------
void uart_nl(uint8_t port)
{
    uart_send(port, '\r');
    uart_send(port, '\n');
}

//------------------------------------------------------------------------------
void uart_hex8(uint8_t port, uint8_t value)
{
    uart_send(UART, HEX_DIGIT[(value>>4) & 0x0F]);
    uart_send(UART, HEX_DIGIT[value & 0x0F]);
}

//------------------------------------------------------------------------------
void uart_hex16(uint8_t port, uint16_t value)
{
    uart_send(UART, HEX_DIGIT[(value>>12) & 0x0F]);
    uart_send(UART, HEX_DIGIT[(value>>8) & 0x0F]);
    uart_send(UART, HEX_DIGIT[(value>>4) & 0x0F]);
    uart_send(UART, HEX_DIGIT[value & 0x0F]);
}

//------------------------------------------------------------------------------
void uart_dec8(uint8_t port, uint8_t value)
{
    if (value > 99)
	uart_send(UART, '0' + (value/100));
    
    uart_send(UART, '0' + ((value/10) % 10));
    uart_send(UART, '0' + (value % 10));
}
