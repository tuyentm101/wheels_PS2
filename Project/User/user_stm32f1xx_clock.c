#include "user_stm32f1xx_clock.h"

void Clock_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_GPIO_PORT_ACTIVE, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_TIMER_ACTIVE, ENABLE);
}
