#ifndef __MYSENSOR_H
#define __MYSENSOR_H

// types for presentation command
//
#define S_TEMP  6
#define S_HUM   7

// types for set command
//
#define V_TEMP 1
#define V_HUM  2


extern char *mysensor_present(uint8_t nodeId,
			      uint8_t childId,
			      uint8_t type);

extern char *mysensor_set(uint8_t nodeId,
			  uint8_t childId,
			  uint8_t type,
			  int value);


#endif
