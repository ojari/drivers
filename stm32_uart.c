#include "hw.h"
#include "hal.h"

#ifdef stm32f4
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_usart.h"
#endif

#ifdef stm32f7
#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx_ll_usart.h"
#endif

#ifdef stm32f0
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_usart.h"
#endif


uint8_t gUart1Rx;
uint8_t gUart2Rx;


#ifdef stm32f0
#define UART_PORT USART1
#endif
#ifdef stm32f4
#define UART_PORT USART2
#endif
#ifdef stm32f7
#define UART_PORT ((USART_TypeDef *) USART3_BASE)
#endif

//------------------------------------------------------------------------------
USART_TypeDef *uart_get(uint8_t port)
{
    USART_TypeDef *ret = NULL;
    
    switch (port) {
    case 1:
	ret = USART1;
	break;
    case 2:
	ret = USART2;
	break;
#ifdef stm32f7
    case 3:
	ret = USART3;
	break;
    case 4:
	ret = UART4;
	break;
#endif
    default:
	error(ERR_UART_PORT);
	break;
    }
    return ret;
}

//------------------------------------------------------------------------------
void USART1_IRQHandler()
{
  if (LL_USART_IsActiveFlag_RXNE(USART1) && LL_USART_IsEnabledIT_RXNE(USART1)) {
    /* RXNE flag will be cleared by reading of RDR register (done in call) */
    /* Call function in charge of handling Character reception */
    //USART_CharReception_Callback();
      gUart1Rx = LL_USART_ReceiveData8(USART1);

      //uart_send(ch);
      
      gEvents |= EV_UART1_RX;
  }
}

void USART2_IRQHandler()
{
  if (LL_USART_IsActiveFlag_RXNE(USART2) && LL_USART_IsEnabledIT_RXNE(USART2)) {
    /* RXNE flag will be cleared by reading of RDR register (done in call) */
    /* Call function in charge of handling Character reception */
    //USART_CharReception_Callback();
      gUart2Rx = LL_USART_ReceiveData8(USART2);

      //uart_send(ch);
      
      gEvents |= EV_UART2_RX;
  }
}


//------------------------------------------------------------------------------
void uart_init(uint8_t port)
{
    //uint32_t pclk;
    USART_TypeDef *uart = uart_get(port);
    
#ifdef stm32f0
    switch (port) {
    case 1:	
 	LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_USART1);
	//NVIC_SetPriority(USARTx_IRQn, 0);  
	//NVIC_EnableIRQ(USARTx_IRQn);
	NVIC_SetPriority(USART1_IRQn, 0);  
	NVIC_EnableIRQ(USART1_IRQn);
	break;
    case 2:
 	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
	//NVIC_SetPriority(USARTx_IRQn, 0);  
	//NVIC_EnableIRQ(USARTx_IRQn);
	NVIC_SetPriority(USART2_IRQn, 0);  
	NVIC_EnableIRQ(USART2_IRQn);
	break;
#ifdef stm32f7
    case 3:
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
	NVIC_SetPriority(USART3_IRQn, 0);
	NVIC_EnableIRQ(USART3_IRQn);
	break;
#endif
    }
#endif

    LL_USART_SetTransferDirection(uart,
				  LL_USART_DIRECTION_TX_RX);

    LL_USART_ConfigCharacter(uart,
			     LL_USART_DATAWIDTH_8B,
			     LL_USART_PARITY_NONE,
			     LL_USART_STOPBITS_1);

    //pclk = LL_RCC_GetUSARTClockFreq(LL_RCC_USART1_CLKSOURCE);

    LL_USART_SetBaudRate(uart,
			 SystemCoreClock/1,       // for stm32f0 1 others 2
			 LL_USART_OVERSAMPLING_16,
			 9600);
//			 115200); 

    LL_USART_Enable(uart);

    LL_USART_ConfigAsyncMode(USART1); // for stm32f0
    
    LL_USART_EnableIT_RXNE(uart);
    LL_USART_EnableIT_ERROR(uart);
}

//------------------------------------------------------------------------------
void uart_send(uint8_t port, char ch)
{
    USART_TypeDef *uart = uart_get(port);
    
    while (!LL_USART_IsActiveFlag_TXE(uart));

    LL_USART_TransmitData8(uart, ch);
}

//------------------------------------------------------------------------------
void uart_sends(uint8_t port, char *buf)
{
    USART_TypeDef *uart = uart_get(port);

    for (uint8_t i = 0; buf[i] != 0; i++) {
	while (!LL_USART_IsActiveFlag_TXE(uart));
	
	LL_USART_TransmitData8(uart, buf[i]);	
    }
}
