#ifndef _LCD5110_H_
#define _LCD5110_H_

/***********************************************************************************
* INCLUDE
*/
#include "user_stm32f1xx_spi.h"
#include "user_stm32f1xx_SysTick.h"
/******************************************************************************
 * DEFINE
 */
#define LCD5110_PORT    GPIOA
#define RST_PIN         GPIO_Pin_2
#define CE_PIN          SPIy_PIN_NSS
#define DC_PIN          GPIO_Pin_3
#define DIN_PIN         SPIy_PIN_MOSI
#define CLK_PIN         SPIy_PIN_SCK

#define LCD5110_CMD     0       /* DC = 0 bits nhan duoc la command*/
#define LCD5110_DATA    1      /* DC =1 bits nhan duoc la data */

#define LCD_X     84
#define LCD_Y     48

#define EnableLCD		GPIO_ResetBits(LCD5110_PORT, CE_PIN)
#define DisableLCD		GPIO_SetBits(LCD5110_PORT, CE_PIN)
/******************************************************************************
 * GLOBAL FUNCTIONS
 */
void LCD5110_ShiftOut(uint8_t TxData);
void LCD5110_Write(uint8_t DC, uint8_t Data_Transfer);
void LCD5110_GotoXY(uint8_t x,uint8_t y);  //x:0->5  y:0->83
void LCD5110_Clr(void);
void LCD5110_write_char(uint8_t c);
void LCD5110_write_sring(uint8_t *str);
void LCD5110_Bitmap(unsigned char arr[]);
void LCD5110_Init(void);
//void error_program(void);

#endif
