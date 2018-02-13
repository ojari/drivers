#ifndef __RFM12B_H
#define __RFM12B_H

// http://www.hoperf.com/upload/rf/rfm12b.pdf

#include <stdint.h>

#define RFM12B_CMD_CFG 0x8000
#define RFM12B_CFG_EF BIT_5
#define RFM12B_CFG_EL BIT_6
#define RFM12B_CMD_PWR 0x8200
#define RFM12B_PWR_DC BIT_0
#define RFM12B_PWR_EW BIT_1
#define RFM12B_PWR_EB BIT_2
#define RFM12B_PWR_EX BIT_3
#define RFM12B_PWR_ES BIT_4
#define RFM12B_PWR_ET BIT_5
#define RFM12B_PWR_EBB BIT_6
#define RFM12B_PWR_ER BIT_7
#define RFM12B_CMD_FREQ 0xA000
#define RFM12B_CMD_DR 0xC600
#define RFM12B_DR_CS BIT_7
#define RFM12B_CMD_RCC 0x9000
#define RFM12B_RCC_P16 BIT_10
#define RFM12B_CMD_DATAFILTER 0xC200
#define RFM12B_DATAFILTER_S BIT_4
#define RFM12B_DATAFILTER_ML BIT_6
#define RFM12B_DATAFILTER_AL BIT_7
#define RFM12B_CMD_FIFOMODE 0xCA00
#define RFM12B_FIFOMODE_DR BIT_0
#define RFM12B_FIFOMODE_FF BIT_1
#define RFM12B_FIFOMODE_AL BIT_2
#define RFM12B_FIFOMODE_SP BIT_3
#define RFM12B_CMD_PATTERN 0xCE00
#define RFM12B_CMD_RECEIVE 0xB000
#define RFM12B_CMD_SEND 0xB800
#define RFM12B_CMD_TXCFG 0x9800
#define RFM12B_TXCFG_MP BIT_8


typedef struct {
    uint8_t spi_port;
    uint8_t pin_select;
    uint8_t pin_irq;
} rfm12b;

extern void rfm12b_init(rfm12b *self, int spi, int select, int irq);
extern void rfm12b_tx(rfm12b *self, uint8_t on);
extern void rfm12b_send(rfm12b *self, uint8_t* buffer, uint8_t size);
extern uint8_t rfm12b_receive(rfm12b *self);
extern void rfm12b_test(rfm12b *self);

#endif
