#include "hw.h"
#include "sump.h"

#define SUMP_META_NAME         0x01
#define SUMP_META_FPGA_VERSION 0x02
#define SUMP_META_SW_VERSION   0x03
#define SUMP_META_SAMPLE_MEM   0x21
#define SUMP_META_DYN_MEM      0x22
#define SUMP_META_SAMPLE_RATE  0x23
#define SUMP_META_NO_PROPES    0x40
#define SUMP_META_PROTOCOL_VER 0x41

#define BUFFER_SIZE 1024

uint8_t buffer[BUFFER_SIZE];

void sump_meta_int32(uint8_t key, uint32_t value)
{
    uart_send(key);
    uart_send( (value >> 24) & 0xFF);
    uart_send( (value >> 16) & 0xFF);
    uart_send( (value >>  8) & 0xFF);
    uart_send( value & 0xFF);
}

void sump_meta()
{
    uart_send(SUMP_META_NAME);
    uart_sends("StmSump");
    uart_send(0x00);

    sump_meta_int32(SUMP_META_SAMPLE_MEM, BUFFER_SIZE);
    sump_meta_int32(SUMP_META_DYN_MEM,    0);
    sump_meta_int32(SUMP_META_SAMPLE_RATE,1000000);

    uart_send(SUMP_META_NO_PROPES);
    uart_send(8);

    uart_send(SUMP_META_PROTOCOL_VER);
    uart_send(2);

    uart_send(0x00); // end mark
}

void sump_run()
{
    uint16_t i;
    uint8_t val;
    //uart_sends("RUN\n");

    val = 1;
    for (i=0; i<BUFFER_SIZE; i++) {
	uart_send(val);

	val++;
	if (val > 20)
	    val = 1;
    }
}

void sump_read()
{
    //uart_sends("READ\n");
}


void sump_undef(uint8_t cmd)
{
    if (cmd & 0x01) {
	clr_LED1;
    }
    if (cmd & 0x02) {
	clr_LED2;
    }
    if (cmd & 0x04) {
	clr_LED3;
    }
    LL_mDelay(2000);

    set_LED1;
    set_LED2;
    set_LED3;
    
    LL_mDelay(1000);
}

void sump_handle(uint8_t cmd)
{
    switch (cmd) {
    case SUMP_RESET:
	// do nothing
	break;
    case SUMP_ID:
	uart_sends("1ALS");
	break;
    case SUMP_METADATA:
	sump_meta();
	break;
    case SUMP_RUN:
	sump_run();
	break;
    case SUMP_XON:
	sump_undef(1);
	break;
    case SUMP_XOFF:
	sump_undef(2);
	break;
    case SUMP_TRG_MASK:
	sump_undef(3);
	break;
    case SUMP_TRG_VAL:
	sump_undef(4);
	break;
    case SUMP_TRG_CFG:
	sump_undef(5);
	break;
    case SUMP_DIVIDER:
	sump_undef(6);
	break;
    case SUMP_READ:
	sump_read();
	break;
    case SUMP_FLAGS:
	sump_undef(7);
	break;
    default:
	break;
    }
}
