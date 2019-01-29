#pragma once

#include "hal_pins.h"
#include "buffer.h"

// Constants (wiring compatible see http://wiring.org.co/reference)
//
#define _INPUT  0
#define _OUTPUT 1

#define TRUE 1
#define FALSE 0

#define HIGH 1
#define LOW  0


extern void delay_us(uint16_t time);

// module input output
//
extern void io_init();
extern void pinMode(pin_t pin, uint8_t mode);
extern void digitalWrite(pin_t pin, uint8_t value);
extern uint8_t digitalRead(pin_t pin);

class SerialBase
{
public:
    void begin(uint16_t rate);
    uint8_t read( );
    void write(uint8_t ch);
    void print(uint8_t val);
    void println();
    uint8_t available();
    uint8_t peek();
    void flush();
    void end();
};

// module serial port
//
extern void uart_init(uint8_t port);
extern void uart_print(uint8_t port, buffer_t *buf);  // async send command
extern void uart_sync(uint8_t port, buffer_t *buf);
extern void uart_send(uint8_t port, char ch);    // old version use uart_print
extern void uart_sends(uint8_t port, char *buf); //
extern void uart_send_nl(uint8_t port);

// module timer
//
extern void timer2_init();

// module SPI serial bus
//
extern void spi_init(uint8_t port);
extern uint16_t spi_write(uint8_t port, uint16_t data);
