#ifndef _PS2_H_
#define _PS2_H_
#include "stm32f10x.h"          
#include "stm32f10x_gpio.h"
#include "user_stm32f1xx_gpio.h"
#include "user_stm32f1xx_SysTick.h"
/*--------------------------------
	MOSI: GPIO PB15 output
	MISO: GPIO PB14 input
	SS	: GPIO PB13 output
	CLK : GPIO PB12 output

	Co 6 loai byte du lieu gui tu tay PS2 ve VDK, moi byte la 1 nhom 8 bit cho 8 nut khac nhau: byte[6]
	- 1st byte: digital button group 1
		+ bit 7 (MSB): left button      <
		+ bit 6 		 : down button	    v
		+ bit 5 		 : right button	    >
		+ bit 4 		 : up button	      /\
		+ bit 3 		 : start button	    STR
		+ bit 2 		 : Right Joystick Center button	
		+ bit 1 		 : Left Joystick Center button	
		+ bit 0 (LSB): Select button SEL
	- 2nd byte: digital button group 2
		+ bit 7 (MSB): square button    []
		+ bit 6 		 : cross button		  +
		+ bit 5 		 : circle button	  o
		+ bit 4 		 : triangle button  \/
		+ bit 3 		 : R1 button				R1
		+ bit 2 		 : L1 button				L1	
		+ bit 1 		 : R2 button				R2	
		+ bit 0 (LSB): L2 button				L2
		Note:
					bit = 0 if the button is pressed
					bit = 1 if the button is not pressed
	- 3rd byte: Right Joystick X axis
	- 4th byte: Right Joystick Y axis
	- 5th byte: Left Joystick Y axis
	- 6th byte: Left Joystick Y axis
--------------------------------*/
#define SPI_MOSI	GPIO_Pin_15
#define SPI_MISO	GPIO_Pin_14
#define SPI_SS		GPIO_Pin_13
#define SPI_CLK		GPIO_Pin_12

#define SPI_CLK_1		    GPIO_SetBits(GPIO_PORT_B, SPI_CLK)
#define SPI_CLK_0		    GPIO_ResetBits(GPIO_PORT_B, SPI_CLK)

#define SPI_MOSI_1		  GPIO_SetBits(GPIO_PORT_B, SPI_MOSI)
#define SPI_MOSI_0		  GPIO_ResetBits(GPIO_PORT_B, SPI_MOSI)

#define SPI_READ_MISO		GPIO_ReadInputDataBit(GPIO_PORT_B, SPI_MISO)

#define SPI_SS_1			  GPIO_SetBits(GPIO_PORT_B, SPI_SS)
#define SPI_SS_0			  GPIO_ResetBits(GPIO_PORT_B, SPI_SS)
/*-------------MASK GROUP 1------------------------------*/
#define MASK_SELECT 							0x01
#define MASK_START								0x08
#define MASK_UP									  0xEF//0x10 
#define MASK_RIGHT								0xDF//0x20
#define MASK_DOWN								  0xBF//0x40
#define MASK_LEFT								  0x7F//0x80 
#define MASK_UP_LEFT							0x90
#define MASK_UP_RIGHT  					  0x30
#define MASK_DOWN_LEFT  					0xC0
#define MASK_DOWN_RIGHT  				  0x60
#define MASK_RIGHT_JOY_CENTER   	0x02
#define MASK_LEFT_JOY_CENTER    	0x04
#define MASK_NO_BUTTON						0xFF
/*-------------MASK GROUP 2------------------------------*/
#define MASK_L2									  0x01
#define MASK_R2									  0x02
#define MASK_L1									  0x04
#define MASK_R1									  0x08
#define MASK_TRIANGLE    				  0xEF//0x10
#define MASK_O           				  0xDF//0x20
#define MASK_X           				  0xBF//0x40
#define MASK_SQUARE      				  0x7F//0x80 

#define SELECT        							(byte[0] & MASK_SELECT)
#define START        								(byte[0] & MASK_START)
#define LEFT_JOY_CENTER      				(byte[0] & MASK_RIGHT_JOY_CENTER)
#define RIGHT_JOY_CENTER     				(byte[0] & MASK_LEFT_JOY_CENTER)

#define UP            							(byte[0] ^ MASK_UP)
#define RIGHT        								(byte[0] ^ MASK_RIGHT)
#define DOWN        								(byte[0] ^ MASK_DOWN)
#define LEFT        								(byte[0] ^ MASK_LEFT)

#define UP_LEFT       							(byte[0] & MASK_UP_LEFT)
#define UP_RIGHT      							(byte[0] & MASK_UP_RIGHT)
#define DOWN_LEFT     							(byte[0] & MASK_DOWN_LEFT)
#define DOWN_RIGHT    							(byte[0] & MASK_DOWN_RIGHT)

#define PS2_MODE_DIGITAL             0x41
#define PS2_MODE_NEGCON              0x23
#define PS2_MODE_ANALOG_RED_LED      0x73
#define PS2_MODE_ANALOG_GREEN_LED    0x53
#define PS2_MODE_NONE                0xFF

#define L2            (byte[1] & MASK_L2)
#define R2            (byte[1] & MASK_R2)
#define L1            (byte[1] & MASK_L1)
#define R1            (byte[1] & MASK_R1)

#define TRIANGLE    	(byte[1] ^ MASK_TRIANGLE)
#define O            	(byte[1] ^ MASK_O)
#define X            	(byte[1] ^ MASK_X)
#define SQUARE        (byte[1] ^ MASK_SQUARE)

#define RIGHT_JOY_LEFT_RIGHT  (byte[2])
#define RIGHT_JOY_UP_DOWN     (byte[3])
#define LEFT_JOY_LEFT       	(byte[4])
#define LEFT_JOY_UP_DOWN      (byte[5])
/*------------------------------------------------------------*/
extern unsigned char byte[6];

void ps2_init (void);
void update_ps2_button (void);
#endif
