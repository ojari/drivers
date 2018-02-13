#include "hw.h"
#include <stdio.h> 
#include "rfm12b.h"

const uint16_t rfm12b_config[] = {
    0x80ED, // 868MHz
    0x8209, // ex+dc
    0xA640, // set frequency
    0xC691, //BR = 2400bps
    0x94A0, //VDI,FAST,BW:134kHz,LNA:0dBm,DRSSI:-103dBm
    0xC2AC, //Data Filter,DQD
    0xCA80, //
    0xCA83, //FIFO8,SYNC,2DD4
    0xCED4, //
    0xC49B, //enable AFC
    0x9810, //434M,Max=8dbm ; 868M/915M,Max=6dbm
    0xCC77, //
    0xE69C, //waker up timer 10000ms
    0xC80e, //NOT USE
    0xC060, //CLK 2.0MHz,LBD 2.2V
    0

/*
 RFXX_WRT_CMD(0x80D8);//EL,EF,433band,12.5pF
 RFXX_WRT_CMD(0x82D9);//!er,!ebb,ET,ES,EX,!eb,!ew,DC
 RFXX_WRT_CMD(0xA640);//A140=430.8MHz
 RFXX_WRT_CMD(0xC647);//4.8kbps
 RFXX_WRT_CMD(0x94A0);//VDI,FAST,134kHz,0dBm,-103dBm
 RFXX_WRT_CMD(0xC2AC);//AL,!ml,DIG,DQD4
 RFXX_WRT_CMD(0xCA81);//FIFO8,SYNC,!ff,DR
 RFXX_WRT_CMD(0xCED4);//SYNC=2DD4；
 RFXX_WRT_CMD(0xC483);//@PWR,NO RSTRIC,!st,!fi,OE,EN
 RFXX_WRT_CMD(0x9850);//!mp,9810=30kHz,MAX OUT
 RFXX_WRT_CMD(0xCC77);//OB1，OB0,！lpx,！ddy，DDIT，BW0
 RFXX_WRT_CMD(0xE000);//NOT USE
 RFXX_WRT_CMD(0xC800);//NOT USE
 RFXX_WRT_CMD(0xC040);//1.66MHz,2.2V 
*/
};

//------------------------------------------------------------------------------
uint16_t rfm12b_cmd(rfm12b *self, uint16_t code)
{
    io_clear(self->pin_select);
    spi_write(self->spi_port, code);
    io_set(self->pin_select);

    return 0;
}

//------------------------------------------------------------------------------
void rfm12b_init(rfm12b *self, int spi, int select, int irq)
{
    uint8_t i;

    spi_init(spi);
    
    self->spi_port = spi;
    self->pin_select = select;
    self->pin_irq = irq;
    
    rfm12b_cmd(self, 0x0000);

    for (i=0; rfm12b_config[i] != 0; i++) {
        rfm12b_cmd(self, rfm12b_config[i]);
    }
}

//------------------------------------------------------------------------------
void rfm12b_tx(rfm12b *self, uint8_t on)
{
    if (on) {
	rfm12b_cmd(self, 0x8239);
    }
    else {
	rfm12b_cmd(self, 0x8201);
    }
}

//------------------------------------------------------------------------------
void rfm12b_send(rfm12b *self, uint8_t* buffer, uint8_t size)
{
    uint8_t i;

    rfm12b_tx(self, 1);
    
    rfm12b_cmd(self, RFM12B_CMD_SEND | 0xAA); // preamble
    rfm12b_cmd(self, RFM12B_CMD_SEND | 0xAA);
    rfm12b_cmd(self, RFM12B_CMD_SEND | 0xAA);
    rfm12b_cmd(self, RFM12B_CMD_SEND | 0x2D); // sync
    rfm12b_cmd(self, RFM12B_CMD_SEND | 0xD4);

    for(i=0; i<size; i++) {
	rfm12b_cmd(self, RFM12B_CMD_SEND | buffer[i]);
    }
    
    rfm12b_cmd(self, RFM12B_CMD_SEND | 0xAA); // dummy bytes
    rfm12b_cmd(self, RFM12B_CMD_SEND | 0xAA);
    rfm12b_cmd(self, RFM12B_CMD_SEND | 0xAA);

    rfm12b_tx(self, 0);
}

//------------------------------------------------------------------------------
uint8_t rfm12b_receive(rfm12b *self)
{
    return 0;
}

//------------------------------------------------------------------------------
void rfm12b_test(rfm12b *self)
{
    rfm12b_cmd(self, 0x5555);
}
