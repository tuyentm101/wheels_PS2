#include "user_stm32f1xx_exti.h"

EXTI_InitTypeDef   EXTI_InitStructure;
NVIC_InitTypeDef   NVIC_InitStructure;

void EXTI3_Configuration(void)
{
	GPIO_EXTI3_Configuration();
	
	/* Clears the EXTI line 3 interrupt pending bit */
	EXTI_ClearITPendingBit(EXTI_Line3);
	
  /* Configure EXTI3 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
}
void NVIC_Configuration(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	/* Enable and set EXTI0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;					//Interrupt vector
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
  NVIC_Init(&NVIC_InitStructure);
}	
void NVIC_EXTI3_Enable(void)
{
	NVIC_EnableIRQ(EXTI3_IRQn);
}
void NVIC_EXTI3_Disable(void)
{
	NVIC_DisableIRQ(EXTI3_IRQn);
}
