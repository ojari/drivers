#ifndef __OUTSENS_H
#define __OUTSENS_H


extern void outsens_init();
extern char *outsens_set(uint8_t  index,
			 uint16_t values[],
			 uint8_t  count);

#endif
