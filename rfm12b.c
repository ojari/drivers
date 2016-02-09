#include "hw.h"
#include <stdio.h> 
#include "rfm12b.h"

const uint16_t rfm12b_config[] = {
    0x80ED, // 868MHz
    0xA640, // set frequency
    0x8209, // ex+dc
    0x94A0, //VDI,FAST,BW:134kHz,LNA:0dBm,DRSSI:-103dBm
    0xC2AC, //Data Filter,DQD
    0xCA80, //
    0xCED4, //
    0xCA83, //FIFO8,SYNC,2DD4
    0xC49B, //enable AFC
    0xCC77, //
    0xE69C, //waker up timer 10000ms
    0xC80e, //NOT USE
    0xC691, //BR = 2400bps
    0x9810, //434M,Max=8dbm ; 868M/915M,Max=6dbm
    0xC060, //CLK 2.0MHz,LBD 2.2V
    NULL
};

//------------------------------------------------------------------------------
void rfm12b_cmd(uint16_t code)
{
}

//------------------------------------------------------------------------------
void rfm12b_init(uint8_t group, uint8_t node)
{
    uint8_t i;
    
    rfm12b_cmd(0x0000);

    for (i=0; rfm12b_config[i] != NULL; i++) {
        rfm12b_cmd(rfm12b_config[i]);
    }
}

//------------------------------------------------------------------------------
void rfm12b_send(void* data, uint8_t size)
{
}

//------------------------------------------------------------------------------
uint8_t rfm12b_receive()
{
	return 0;
}
