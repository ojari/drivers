#pragma once

#include "hal_pins.h"
#include "buffer.h"

// Constants (wiring compatible see http://wiring.org.co/reference)
//
#define INPUT  0
#define OUTPUT 1

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

// module serial port
//
class SerialBase
{
public:
    virtual void begin(uint16_t rate) = 0;
    virtual void write(uint8_t ch) = 0;
    virtual void end() = 0;

    uint8_t read();
    void print(uint8_t val);
    void println();
    void println(const char* str);
    uint8_t available();
    uint8_t peek();
    void flush();
};

extern void uart_init(uint8_t port);
extern void uart_print(uint8_t port, buffer_t *buf);  // async send command
extern void uart_sync(uint8_t port, buffer_t *buf);
extern void uart_send(uint8_t port, char ch);    // old version use uart_print
extern void uart_sends(uint8_t port, char *buf); //
extern void uart_send_nl(uint8_t port);

// module timer
//
extern void timer2_init();


// class for SPI bus configuration parameters
//
enum class SPIMode {
    SPI_MODE0 = 0,
    SPI_MODE1 = 1,
    SPI_MODE2 = 2,
    SPI_MODE3 = 4
};

enum class SPIBitOrder {
    MSBFIRST,
    LSBFIRST
};

class SPISettings
{
public:
    SPISettings(uint32_t clk, SPIBitOrder bo, SPIMode m) :
	clock{clk},
	bitOrder{bo},
	mode{m}
    {
    }
    friend class SpiBase;
protected:
    uint32_t clock;
    SPIBitOrder bitOrder;
    SPIMode mode;
};


// module SPI serial bus
//
class SpiBase
{
public:    
    virtual void beginTransaction(const SPISettings set) = 0;
    virtual uint8_t transfer(uint8_t byte) = 0;
    virtual uint16_t transfer16(uint16_t word) = 0;
    virtual void endTransaction() = 0;
};
