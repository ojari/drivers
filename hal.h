#pragma once

#include "hal_pins.h"

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
extern void uart_send(uint8_t port, char ch);
extern void uart_sends(uint8_t port, char *buf);
extern void uart_send_nl(uint8_t port);

extern void timer2_init();

extern void spi_init(uint8_t port);
extern uint16_t spi_write(uint8_t port, uint16_t data);
