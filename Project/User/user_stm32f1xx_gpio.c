#include "user_stm32f1xx_gpio.h"

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef 				GPIO_InitStruct ;
	GPIO_StructInit(&GPIO_InitStruct);								 //Fills GPIO_InitStruct members with its default value
	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_PB_PWM;
	GPIO_InitStruct.GPIO_Mode = GPIO_MODE_ALTERNATE_FUNCTION_PUSH_PULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_SPEED;
	GPIO_Init(GPIO_PORT_B, &GPIO_InitStruct);  

	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_PB_SPI_INPUT;
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_INPUT_PULL_UP;
	GPIO_Init(GPIO_PORT_B, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_PIN_PB_SPI_OUTPUT | GPIO_PIN_PB_ENABLE_BRIDGE;
  GPIO_InitStruct.GPIO_Mode = GPIO_MODE_OUTPUT_PUSH_PULL;
	GPIO_Init(GPIO_PORT_B, &GPIO_InitStruct);
}
