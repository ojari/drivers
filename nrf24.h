#pragma once

#define NRF24_PIPE0 0x01
#define NRF24_PIPE1 0x02
#define NRF24_PIPE2 0x04
#define NRF24_PIPE3 0x08
#define NRF24_PIPE4 0x10
#define NRF24_PIPE5 0x20

#define NRF24_CONFIG_RX     0x01
#define NRF24_CONFIG_POWER  0x02
#define NRF24_CONFIG_CRC2B  0x04
#define NRF24_CONFIG_CRC    0x08
#define NRF24_CONFIG_MAX_RT 0x10
#define NRF24_CONFIG_TX_DS  0x20
#define NRF24_CONFIG_RX_DR  0x40

#define NRF24_ADR_WIDTH_3   0x01
#define NRF24_ADR_WIDTH_4   0x02
#define NRF24_ADR_WIDTH_5   0x03

typedef struct {
    uint8_t spi_port;
    pin_t   pin_ce;
    pin_t   pin_csn;
    pin_t   pin_irq;
} nrf24;

extern void nrf24_init(nrf24* self, uint8_t spi, pin_t ce, pin_t csn, pin_t irq);
extern void nrf24_tx(nrf24* self);
extern void nrf24_rx(nrf24* self);
