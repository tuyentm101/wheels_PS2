#ifndef _USER_STM32F1XX_LCD_TEXT_H_
#define _USER_STM32F1XX_LCD_TEXT_H_
#include "stm32f10x.h"
#include "user_stm32f1xx_gpio.h"
#include "user_stm32f1xx_SysTick.h"
/**********************************************/
#define DATA_PORT			GPIOB
#define CTRL_PORT		  GPIOA
#define LCD_RS				GPIO_Pin_0		//RS Pin: PA0
#define LCD_EN				GPIO_Pin_1		//EN Pin: PA1
//#define LCD_D0				GPIO_Pin_0		// D0 Pin: PB0
//#define LCD_D1				GPIO_Pin_1		// D1 Pin: PB1
//#define LCD_D2				GPIO_Pin_2		// D2 Pin: PB2
//#define LCD_D3				GPIO_Pin_3		// D3 Pin: PB3
#define LCD_D4				GPIO_Pin_4		// D4 Pin: PB4
#define LCD_D5				GPIO_Pin_5		// D5 Pin: PB5
#define LCD_D6				GPIO_Pin_6		// D6 Pin: PB6
#define LCD_D7				GPIO_Pin_7    // D7 Pin: PB7
/********************************************/
/*
	List LCD command, refer to D:\Hoc tap\Do an Bai tap\LCD\HD44780.pdf, page 28/60
*/
#define LCD_CMD_CLR					        						 0x01
#define LCD_CMD_RETURN_HOME			    						 0x02
#define LCD_CMD_ENTRY_MODE_SET		  						 0x06		/* I/D = 1 : Increment, S = 0: no shift display*/
#define LCD_CMD_DISPLAY_OFF_CTRL_NO_BLINK   	   0x0C   /* on display, off cursor, no blink */
#define LCD_CMD_DISPLAY_ON_CTRL_NO_BLINK 				 0x0E		/* on display, on cursor, no blink */
#define LCD_CMD_DISPLAY_OFF_CTRL_BLINK   	   		 0x0D 	/* on display, off cursor, blink */
#define LCD_CMD_DISPLAY_ON_CTRL_BLINK 				   0x0F		/* on display, on cursor, blink */
#define LCD_CMD_CURSOR_SHIFT_LEFT								 0x10
#define LCD_CMD_CURSOR_SHIFT_RIGHT							 0x14
#define LCD_CMD_DISPLAY_SHIFT_LEFT							 0x18
#define LCD_CMD_DISPLAY_SHIFT_RIGHT							 0x1C
#define LCD_CMD_ADD_L1_HOME				 						   0x80
#define LCD_CMD_ADD_L2_HOME				 							 0xC0
#define LCD_CMD_8BIT_FONT5X8_2LINE	 						 0x38
#define LCD_CMD_4BIT_FONT5X8_2LINE	 						 0x28
/**********************************************/
#define LCD_TYPE_CMD						 		 0
#define LCD_TYPE_DATA						     1
/**********************************************/
void LCD_Init(void);
void LCD_Write_Char(uint8_t ch);
void LCD_Write_String(uint8_t* text);
void LCD_Clear(void);
void LCD_GotoXY(uint8_t x, uint8_t y);
#endif
