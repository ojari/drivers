#include "hw.h"
#include "logging.h"

static uint8_t gUart = 0;


void log_init(uint8_t uart)
{
    gUart = uart;
}


void log_msg(uint8_t module, char message)
{
    uart_send(gUart, module);
    uart_send(gUart, (uint8_t)message);
}
