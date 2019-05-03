#pragma once

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

enum class nrfPipe {
  pipe0 = 0x01,
  pipe1 = 0x02,
  pipe2 = 0x04,
  pipe3 = 0x08,
  pipe4 = 0x10,
  pipe5 = 0x20
};

enum class nrfCmd {
  read_reg = 0x00,
  write_reg = 0x20,
  rx_payload = 0x61,
  tx_payload = 0xA0,
  flush_tx   = 0xE1,
  flush_rx   = 0xE2,
  nop        = 0xFF,
  tx_addr    = 0x30,
  rx_addr0   = 0x2A
};

enum class nrfReg {
  config    = 0x00,
  aa        = 0x01,  // auto ack
  rxaddr    = 0x02,
  aw        = 0x03,  // address width
  retrans   = 0x04,
  rf_ch     = 0x05,
  rf_set    = 0x06,
  status    = 0x07,
  rx_addr0  = 0x0A, // RX address pipe0..
  rx_addr1  = 0x0B,
  rx_addr2  = 0x0C,
  rx_addr3  = 0x0D,
  rx_addr4  = 0x0E,
  rx_addr5  = 0x0F,
  tx_addr   = 0x10,
  rx_pw0    = 0x11, // RX payload size pipe0..
  rx_pw1    = 0x12,
  rx_pw2    = 0x13,
  rx_pw3    = 0x14,
  rx_pw4    = 0x15,
  rx_pw5    = 0x16,
  fifo_stat = 0x17,
  dynpd     = 0x1C,
  feature   = 0x1D
};
  
//------------------------------------------------------------------------------
class Nrf24
{
public:
    void begin();
    void end();


    void reg(nrfReg reg, uint8_t value);
    uint8_t reg(nrfReg reg);

private:
    uint8_t spi_port;
    pin_t   pin_ce;
    pin_t   pin_csn;
    pin_t   pin_irq;
};

//extern void nrf24_init(nrf24* self, uint8_t spi, pin_t ce, pin_t csn, pin_t irq);
//extern void nrf24_tx(nrf24* self);
//extern void nrf24_rx(nrf24* self);
