#ifndef _USER_STM32F1XX_CLOCK_H_
#define _USER_STM32F1XX_CLOCK_H_
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
/***********************************/
#define RCC_GPIO_PORT_ACTIVE				RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO
#define RCC_TIMER_ACTIVE						RCC_APB1Periph_TIM4
/***************************************/
void Clock_Configuration(void);
#endif
