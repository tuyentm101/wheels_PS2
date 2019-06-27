#ifndef _USER_STM32F1XX_EXTI_H_
#define _USER_STM32F1XX_EXTI_H_
/*----------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "misc.h"
#include "user_stm32f1xx_gpio.h"

void EXTI3_Configuration(void);
void NVIC_Configuration(void);
void NVIC_EXTI3_Enable(void);
void NVIC_EXTI3_Disable(void);
#endif
