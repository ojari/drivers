#include "hw.h"
#include "hal.h"
#include "event.h"

#ifdef stm32f4
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_tim.h"
#endif

#ifdef stm32f7
#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx_ll_tim.h"
#endif

#ifdef stm32f1
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_tim.h"
#endif

#ifdef stm32f0
#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_tim.h"
#endif


//------------------------------------------------------------------------------
void TIM2_IRQHandler(void)
{
    if(LL_TIM_IsActiveFlag_UPDATE(TIM2) == 1) {
	LL_TIM_ClearFlag_UPDATE(TIM2);
    }

    //LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_14);
    EVENT_SET(EV_TIMER2, 0);
}

//------------------------------------------------------------------------------
void timer2_init()
{
    uint32_t clock, reload;
    
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

    LL_TIM_SetPrescaler(TIM2, __LL_TIM_CALC_PSC(SystemCoreClock, 10000));

    clock = SystemCoreClock/1;

    reload = __LL_TIM_CALC_ARR(clock, LL_TIM_GetPrescaler(TIM2), 1);
    LL_TIM_SetAutoReload(TIM2, reload);

    LL_TIM_EnableIT_UPDATE(TIM2);
    
    NVIC_SetPriority(TIM2_IRQn, 0);
    NVIC_EnableIRQ(TIM2_IRQn);

    LL_TIM_EnableCounter(TIM2);
    LL_TIM_GenerateEvent_UPDATE(TIM2);
}
