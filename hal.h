#pragma once

#include "hal_pins.h"
#include "buffer.h"

#define IO_MODE_INPUT  0
#define IO_MODE_OUTPUT 1

#define TRUE 1
#define FALSE 0

extern void delay_us(uint16_t time);

extern void io_init();
extern void io_pin_init(pin_t pin, uint8_t mode);
extern void io_mode(pin_t, uint8_t mode);
extern void io_set(pin_t pin);
extern void io_clear(pin_t pin);
extern uint8_t io_read(pin_t pin);

extern void uart_init(uint8_t port);
extern void uart_print(uint8_t port, buffer_t *buf);  // async send command
extern void uart_sync(uint8_t port, buffer_t *buf);

extern void uart_send(uint8_t port, char ch);    // old version use uart_print
extern void uart_sends(uint8_t port, char *buf); //
extern void uart_send_nl(uint8_t port);

//extern void uart_nl(uint8_t port);                    // in hal_common
//extern void uart_hex8(uint8_t port, uint8_t value);   // in hal_common
//extern void uart_hex16(uint8_t port, uint16_t value); // in hal_common
//extern void uart_dec8(uint8_t port, uint8_t value);   // in hal_common

extern void timer2_init();

extern void spi_init(uint8_t port);
extern uint16_t spi_write(uint8_t port, uint16_t data);
