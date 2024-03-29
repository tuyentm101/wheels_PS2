#ifndef _USER_STM32F1XX_TIM_H_
#define _USER_STM32F1XX_TIM_H_
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
/*------------------------------------*/
#define TIM_COUNTER_FREQ  7200  //72000
/* if create small pwm freq, must be 7200 because can make a hundred thousands value, exceeding the 16 bit int*/
#define PWM_FREQ           1000
#define TIMER_ACTIVE			 TIM4
/*-------------Macros-----------------------*/

void Timer_Configuration_PWM(void);
void Timer_Enable(void);
void Timer_Disable(void);
void Channel1_Pulsing(void);
void Channel2_Pulsing(void);
void Channel3_Pulsing(void);
void Channel4_Pulsing(void);
void Channel1_Force_To_High(void);
void Channel2_Force_To_High(void);
void Channel3_Force_To_High(void);
void Channel4_Force_To_High(void);
void Channel1_Force_To_Low(void);
void Channel2_Force_To_Low(void);
void Channel3_Force_To_Low(void);
void Channel4_Force_To_Low(void);
void Update_Duty_Channel1(uint16_t new_duty);
void Update_Duty_Channel2(uint16_t new_duty);
void Update_Duty_Channel3(uint16_t new_duty);
void Update_Duty_Channel4(uint16_t new_duty);
#endif
