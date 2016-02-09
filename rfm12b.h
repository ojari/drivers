#ifndef __RFM12B_H
#define __RFM12B_H

// http://www.hoperf.com/upload/rf/rfm12b.pdf

#include <stdint.h>


extern void rfm12b_init(uint8_t group, uint8_t node);
extern void rfm12b_send(void* data, uint8_t size);
extern uint8_t rfm12b_receive();

#endif
