#ifndef _USER_STM32F1XX_GPIO_H_
#define _USER_STM32F1XX_GPIO_H_
#include "stm32f10x.h"          
#include "stm32f10x_gpio.h"     // Pins Interface
/*******************************************/
#define GPIO_PORT_A									GPIOA								// GPIO port = A													
#define GPIO_PORT_C 								GPIOC								// GPIO port = C
#define GPIO_PORT_B	 								GPIOB								// GPIO port = B
#define GPIO_PIN_PA 								GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
#define GPIO_PIN_PB_PWM 					  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9
#define GPIO_PIN_PB_ENABLE_BRIDGE		GPIO_Pin_1 | GPIO_Pin_2
#define GPIO_PIN_PB_SPI_OUTPUT			GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_15
#define GPIO_PIN_PB_SPI_INPUT				GPIO_Pin_14
#define GPIO_MODE_ALTERNATE_FUNCTION_PUSH_PULL										  GPIO_Mode_AF_PP				
#define GPIO_MODE_OUTPUT_PUSH_PULL												          GPIO_Mode_Out_PP
#define GPIO_MODE_INPUT_FLOATING																	  GPIO_Mode_IN_FLOATING
#define GPIO_MODE_INPUT_PULL_UP																			GPIO_Mode_IPU
#define GPIO_SPEED																		GPIO_Speed_50MHz			
/******************************************/
void GPIO_Configuration(void);
#endif
