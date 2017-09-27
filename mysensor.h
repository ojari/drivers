#ifndef __MYSENSOR_H
#define __MYSENSOR_H

#define 

extern char *mysensor_present(uint8_t nodeId,
			      uint8_t childId,
			      uint8_t type);

extern char *mysensor_set(uint8_t nodeId,
			  uint8_t childId,
			  uint8_t type,
			  int value);


#endif
