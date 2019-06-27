#include "user_stm32f1xx_TIM.h"

uint16_t ARR_Val = 0;

void Timer_Configuration_PWM (void)
{
	/*-------------------------------------------------------------------
		- declare a Timer Base struct including parameters: 
			period, prescaler, clock division,counter mode, repetition counter
		- declare a Output Compare struct including parameters: 
			output state, output N state, pulse, OC Polarity, OC N polarity, OC idle state, OC N idle state
	--------------------------------------------------------------------*/
	TIM_TimeBaseInitTypeDef 	TIM_TimeBaseStructure;
	TIM_OCInitTypeDef					TIM_OCInitStructure;
	uint16_t CCR1_Val, CCR2_Val, CCR3_Val, CCR4_Val;
	uint32_t TIM_counter_clock_freq = 0, TIM_clock_freq = 0;
	uint16_t duty_ch1, duty_ch2, duty_ch3, duty_ch4;
	/* -----------------------------------------------------------------------
    TIM2 Configuration: generate 4 PWM signals with 4 different duty cycles:
    The TIM2CLK frequency is set to SystemCoreClock (Hz)
     - Prescaler = (TIM2CLK / TIM2 counter clock) - 1 
    SystemCoreClock is set to 72 MHz
	  The TIM2 counter clock is  TIM_COUNTER_FREQ:
		- PWM Frequency = TIM2 counter clock/(ARR + 1)
		- ARR = TIM2 counter clock / PWM Freq - 1;
																									
  ----------------------------------------------------------------------- */
	TIM_counter_clock_freq = TIM_COUNTER_FREQ;       	
	TIM_clock_freq = SystemCoreClock;
	ARR_Val = (uint16_t)((TIM_counter_clock_freq / PWM_FREQ)  - 1);   //PWM frequency = PWM_FREQ
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t)((TIM_clock_freq / TIM_counter_clock_freq) - 1);
	TIM_TimeBaseStructure.TIM_Period = ARR_Val; 				
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIMER_ACTIVE, &TIM_TimeBaseStructure);
	/*-------------------------------------------------------------------------------------
		TIM2 Channel1 duty cycle = (TIM2_CCR1/ (TIM2_ARR + 1))* 100 = 50%
    TIM2 Channel1 duty cycle = (TIM2_CCR2/ (TIM2_ARR + 1))* 100 = 12.5%
		Edge - aligned, not single pulse mode
	---------------------------------------------------------------------------------------*/
	duty_ch1 = 25;
	duty_ch2 = 25;
	duty_ch3 = 25;
	duty_ch4 = 25;
	CCR1_Val = ( duty_ch1 * (ARR_Val + 1) ) / 100;
	CCR2_Val = ( duty_ch2 * (ARR_Val + 1) ) / 100;
	CCR3_Val = ( duty_ch3 * (ARR_Val + 1) ) / 100;
	CCR4_Val = ( duty_ch4 * (ARR_Val + 1) ) / 100;
	
	TIM_OCStructInit(&TIM_OCInitStructure);			//Fills with default values
	/* PWM1 Mode configuration: Channel_1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;				//Low true
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	
  TIM_OC1Init(TIMER_ACTIVE, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIMER_ACTIVE, TIM_OCPreload_Disable); //Disable the TIM2 Preload register on CCR1
	/* PWM1 Mode configuration: Channel_2 */
  TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	
  TIM_OC2Init(TIMER_ACTIVE, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIMER_ACTIVE, TIM_OCPreload_Disable); //Disable the TIM2 Preload register on CCR2
	/* PWM1 Mode configuration: Channel_3 */
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
	
  TIM_OC3Init(TIMER_ACTIVE, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIMER_ACTIVE, TIM_OCPreload_Disable); //Disable the TIM2 Preload register on CCR3
	/* PWM1 Mode configuration: Channel_4 */
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
	
	TIM_OC4Init(TIMER_ACTIVE, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIMER_ACTIVE, TIM_OCPreload_Disable); //Disable the TIM2 Preload register on CCR4
	
	TIM_ARRPreloadConfig(TIMER_ACTIVE, ENABLE);	//Enable the TIM peripheral Preload register on ARR
}
void Channel1_Pulsing(void)
{
	TIM_SelectOCxM(TIMER_ACTIVE, TIM_Channel_1, TIM_OCMode_PWM1);
	TIM_CCxCmd(TIMER_ACTIVE, TIM_Channel_1, TIM_CCx_Enable);
}	
void Channel2_Pulsing(void)
{
	TIM_SelectOCxM(TIMER_ACTIVE, TIM_Channel_2, TIM_OCMode_PWM1);
	TIM_CCxCmd(TIMER_ACTIVE, TIM_Channel_2, TIM_CCx_Enable);
}	
void Channel3_Pulsing(void)
{
	TIM_SelectOCxM(TIMER_ACTIVE, TIM_Channel_3, TIM_OCMode_PWM1);
	TIM_CCxCmd(TIMER_ACTIVE, TIM_Channel_3, TIM_CCx_Enable);
}	
void Channel4_Pulsing(void)
{
	TIM_SelectOCxM(TIMER_ACTIVE, TIM_Channel_4, TIM_OCMode_PWM1);
	TIM_CCxCmd(TIMER_ACTIVE, TIM_Channel_4, TIM_CCx_Enable);
}	
void Channel1_Force_To_High(void)
{
	TIM_ForcedOC1Config(TIMER_ACTIVE, TIM_ForcedAction_Active);  //Force output to low level
}	
void Channel2_Force_To_High(void)
{
	TIM_ForcedOC2Config(TIMER_ACTIVE, TIM_ForcedAction_Active);  //Force output to low level
}	
void Channel3_Force_To_High(void)
{
	TIM_ForcedOC3Config(TIMER_ACTIVE, TIM_ForcedAction_Active);  //Force output to low level
}	
void Channel4_Force_To_High(void)
{
	TIM_ForcedOC4Config(TIMER_ACTIVE, TIM_ForcedAction_Active);  //Force output to low level
}	
void Channel1_Force_To_Low(void)
{
	TIM_ForcedOC1Config(TIMER_ACTIVE, TIM_ForcedAction_InActive);  //Force output to low level
}	
void Channel2_Force_To_Low(void)
{
	TIM_ForcedOC2Config(TIMER_ACTIVE, TIM_ForcedAction_InActive);  //Force output to low level
}	
void Channel3_Force_To_Low(void)
{
	TIM_ForcedOC3Config(TIMER_ACTIVE, TIM_ForcedAction_InActive);  //Force output to low level
}	
void Channel4_Force_To_Low(void)
{
	TIM_ForcedOC4Config(TIMER_ACTIVE, TIM_ForcedAction_InActive);  //Force output to low level
}	
void Timer_Enable(void)
{
	TIM_Cmd(TIMER_ACTIVE, ENABLE);
}
void Timer_Disable(void)
{
	TIM_Cmd(TIMER_ACTIVE, DISABLE);
}
void Update_Duty_Channel1(uint16_t new_duty)
{
	uint16_t new_CCR1_val;
	if (new_duty < 100)
		new_CCR1_val = ( new_duty * (ARR_Val + 1) ) / 100;
	else
		new_CCR1_val = ( new_duty * (ARR_Val + 1) ) / 1000;
	TIM_SetCompare1(TIMER_ACTIVE, new_CCR1_val); 
}
void Update_Duty_Channel2(uint16_t new_duty)
{
	uint16_t new_CCR2_val;
	if (new_duty < 100)
		new_CCR2_val = ( new_duty * (ARR_Val + 1) ) / 100;
	else
		new_CCR2_val = ( new_duty * (ARR_Val + 1) ) / 1000;
	TIM_SetCompare2(TIMER_ACTIVE, new_CCR2_val); 
}
void Update_Duty_Channel3(uint16_t new_duty)
{
	uint16_t new_CCR3_val;
	if (new_duty < 100)
		new_CCR3_val = ( new_duty * (ARR_Val + 1) ) / 100;
	else
		new_CCR3_val = ( new_duty * (ARR_Val + 1) ) / 1000;
	TIM_SetCompare3(TIMER_ACTIVE, new_CCR3_val); 
}
void Update_Duty_Channel4(uint16_t new_duty)
{
	uint16_t new_CCR4_val;
	if (new_duty < 100)
		new_CCR4_val = ( new_duty * (ARR_Val + 1) ) / 100;
	else
		new_CCR4_val = ( new_duty * (ARR_Val + 1) ) / 1000;
	TIM_SetCompare4(TIMER_ACTIVE, new_CCR4_val); 
}
