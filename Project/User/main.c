/*-----------------------------------------------------
Description: Dieu khien xe tay PS2
Author: 		 Tuyen BK
MCU:				 STM32f103c8t6
- Dong co 1:
+ Quay thuan			: 	PB6 PWM TIM4 ch1
+ Quay nguoc			: 	PB7 PWM TIM4 ch2
+ Enable bridge		: 	PB1 output push pull
- Dong co 2:
+ Quay thuan			: 	PB8 PWM TIM4 ch3
+ Quay nguoc			: 	PB9 PWM TIM4 ch4
+ Enable bridge		: 	PB2 output push pull
- Giao tiep PS2 gampad
+ MOSI (Command)	: 	PB15 output push pull
+ MISO (Data)			: 	PB14 input pull up (must be!!!)
+ SS   (Attention):   PB13 output push pull
+ CLK  (SCK)      :   PB12 output push pull
-----------------------------------------------------*/
#include "main.h"
    
#define PRESSED 			0
#define ON						1
#define OFF						!ON	
#define STOP          0
#define FORWARD				1
#define REVERSE       2
#define TURN_LEFT			3
#define TURN_RIGHT		4
#define LOW_SPEED     20
#define MEDIUM_SPEED	60
#define HIGH_SPEED		90

static uint8_t speed = MEDIUM_SPEED;

void General_Configuration(void);
void Init_Motor(void);
void Go_Forward(void);
void Stop_Forward(void);
void Go_Reverse(void);
void Stop_Reverse(void);
void Turn_Left(void);
void Turn_Right(void);
void Stop_Turn_Left(void);
void Stop_Turn_Right(void);

int main(void)
{
	static uint8_t state = STOP;
	
	General_Configuration(); 
	Timer_Enable();
  Init_Motor();
	ps2_init();
	
	while (1)
	{
		update_ps2_button();
		
		if (TRIANGLE == PRESSED)
		{
			speed = HIGH_SPEED; 
		}
		if (X == PRESSED)
		{
			speed = MEDIUM_SPEED; 
		}	
		
		if (UP == PRESSED)
		{
			if (state != FORWARD)
			{
				Update_Duty_Channel1(speed); Update_Duty_Channel3(speed);
				Go_Forward(); 
				state = FORWARD; 
			}
		}
		else
			if (state == FORWARD)
			{
				Update_Duty_Channel1(LOW_SPEED); Update_Duty_Channel3(LOW_SPEED);
				SystemTick_Delay_ms(1);
				Stop_Forward();
				SystemTick_Delay_Us(20);
				state = STOP;
			}
			
		if (DOWN == PRESSED)
		{
			if (state != REVERSE)
			{
				Update_Duty_Channel2(speed); Update_Duty_Channel4(speed);
				Go_Reverse(); 
				state = REVERSE; 
			}
		}
		else
			if (state == REVERSE)
			{
				Update_Duty_Channel2(LOW_SPEED); Update_Duty_Channel4(LOW_SPEED);
				SystemTick_Delay_ms(1);
				Stop_Reverse();
				SystemTick_Delay_Us(20);
				state = STOP;
			}
			
		if (LEFT == PRESSED)
		{
			if (state != TURN_LEFT)
			{
				Turn_Left();
				state = TURN_LEFT;
			}
		}	
		else
			if (state == TURN_LEFT)
			{
				Update_Duty_Channel2(LOW_SPEED); Update_Duty_Channel3(LOW_SPEED);
				SystemTick_Delay_ms(1);
				Stop_Turn_Left();
				SystemTick_Delay_Us(20);
				state = STOP;
			}
		
		if (RIGHT == PRESSED)
		{
			if (state != TURN_RIGHT)
			{
				Turn_Right();
				state = TURN_RIGHT;
			}
		}
		else
			if (state == TURN_RIGHT)
			{
				Update_Duty_Channel1(LOW_SPEED); Update_Duty_Channel4(LOW_SPEED);
				SystemTick_Delay_ms(1);
				Stop_Turn_Right();
				SystemTick_Delay_Us(20);
				state = STOP;
			}	
	}	
}

void General_Configuration(void)
{
	Clock_Configuration();
	GPIO_Configuration();
	SystemTick_Timer_Init(); 
	Timer_Configuration_PWM();
}	
void Enable_Bridge(void)
{
	GPIO_SetBits(GPIO_PORT_B, GPIO_Pin_1);
	GPIO_SetBits(GPIO_PORT_B, GPIO_Pin_2);
}
void Disable_Bridge(void)
{
	GPIO_ResetBits(GPIO_PORT_B, GPIO_Pin_1);
	GPIO_ResetBits(GPIO_PORT_B, GPIO_Pin_2);
}
void Init_Motor(void)
{
	Channel1_Force_To_Low();
	Channel2_Force_To_Low();
	Channel3_Force_To_Low();
	Channel4_Force_To_Low();
	Disable_Bridge();
	SystemTick_Delay_Us(20);
}
void Go_Forward(void)
{
	Channel1_Pulsing();
	Channel3_Pulsing();
	Enable_Bridge(); 	
}
void Stop_Forward(void)
{
	Channel1_Force_To_Low();
	Channel3_Force_To_Low();
	Disable_Bridge(); 
}
void Go_Reverse(void)
{
	Channel2_Pulsing();
	Channel4_Pulsing();
	Enable_Bridge();
}
void Stop_Reverse(void)
{
	Channel2_Force_To_Low();
	Channel4_Force_To_Low();
	Disable_Bridge(); 
}
void Turn_Left(void)
{
	Update_Duty_Channel2(speed);
	Update_Duty_Channel3(speed);
	Channel2_Pulsing();
	Channel3_Pulsing();
	Enable_Bridge(); 
}
void Stop_Turn_Left(void)
{
	Channel2_Force_To_Low();
	Channel3_Force_To_Low();
	Disable_Bridge();
}
void Stop_Turn_Right(void)
{
	Channel1_Force_To_Low();
	Channel4_Force_To_Low();
	Disable_Bridge();
}
void Turn_Right(void)
{
	Update_Duty_Channel1(speed);
	Update_Duty_Channel4(speed);
	Channel1_Pulsing();
	Channel4_Pulsing();
	Enable_Bridge();
}
