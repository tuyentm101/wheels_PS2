#ifndef _USER_STM32F1XX_SPI_H_
#define _USER_STM32F1XX_SPI_H_
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "user_stm32f1xx_gpio.h"
/*-----------------------------------------*/
#define SPIy                   SPI1   
#define SPIy_CLK               RCC_APB2Periph_SPI1
#define SPIy_GPIO              GPIOA
#define SPIy_GPIO_CLK          RCC_APB2Periph_GPIOA  
#define SPIy_PIN_NSS					 GPIO_Pin_4	
#define SPIy_PIN_SCK           GPIO_Pin_5
#define SPIy_PIN_MISO          GPIO_Pin_6
#define SPIy_PIN_MOSI          GPIO_Pin_7 
/*----------------------------------------------*/
void SPI_Configuration(uint16_t SPI_mode);
void SPI_LCD5110_Configuration(void);
void SPI_Slave_Select(uint8_t action);
void SPI_Send_8bit(uint8_t data);
uint16_t SPI_Receive_8bit(void);
void SPI_Send_16bit(uint16_t data);
#endif
