#include "hw.h"
#include "sump.h"

void sump_handle(uint8_t cmd)
{
    switch (cmd) {
    case SUMP_RESET:
	break;
    case SUMP_RUN:
	break;
    case SUMP_ID:
	break;
    case SUMP_XON:
	break;
    case SUMP_XOFF:
	break;
    case SUMP_TRG_MASK:
	break;
    case SUMP_TRG_VAL:
	break;
    case SUMP_TRG_CFG:
	break;
    case SUMP_DIVIDER:
	break;
    case SUMP_READ:
	break;
    case SUMP_FLAGS:
	break;
    default:
	break;
    }
}


void sump_run()
{
}
