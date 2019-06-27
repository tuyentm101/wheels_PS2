#include "user_stm32f1xx_lcd_text.h"
/********************************************/
void LCD_Send_4bit(uint8_t data)
{
	GPIO_WriteBit(DATA_PORT, LCD_D7, (data & 0x08) ? Bit_SET : Bit_RESET);
	GPIO_WriteBit(DATA_PORT, LCD_D6, (data & 0x04) ? Bit_SET : Bit_RESET);
	GPIO_WriteBit(DATA_PORT, LCD_D5, (data & 0x02) ? Bit_SET : Bit_RESET);
	GPIO_WriteBit(DATA_PORT, LCD_D4, (data & 0x01) ? Bit_SET : Bit_RESET);
}
void LCD_Send(uint8_t type, uint8_t data_8bit)
{
	if (LCD_TYPE_DATA == type)
	{
		GPIO_SetBits(CTRL_PORT, LCD_RS);
		LCD_Send_4bit(data_8bit >> 4);
		GPIO_SetBits(CTRL_PORT, LCD_EN);
		GPIO_ResetBits(CTRL_PORT, LCD_EN);
		LCD_Send_4bit(data_8bit);
		GPIO_SetBits(CTRL_PORT, LCD_EN);
		GPIO_ResetBits(CTRL_PORT, LCD_EN);
	}
	else
	{
		GPIO_ResetBits(CTRL_PORT, LCD_RS);
		LCD_Send_4bit(data_8bit >> 4);
		GPIO_SetBits(CTRL_PORT, LCD_EN);
		GPIO_ResetBits(CTRL_PORT, LCD_EN);
		LCD_Send_4bit(data_8bit);
		GPIO_SetBits(CTRL_PORT, LCD_EN);
		GPIO_ResetBits(CTRL_PORT, LCD_EN);
		if (data_8bit <= 0x02)
			SystemTick_Delay_ms(2);
	}
}
void LCD_Init(void)
{
	/*
	default mode: 8 bit interface, display 1 line,
								auto - incrementing cursor, off display
	*/
	LCD_Send(LCD_TYPE_CMD, 0x30);
	SystemTick_Delay_ms(5);
	LCD_Send(LCD_TYPE_CMD, 0x30);
	SystemTick_Delay_ms(1);
	LCD_Send(LCD_TYPE_CMD, 0x30);
	LCD_Send(LCD_TYPE_CMD, LCD_CMD_RETURN_HOME);
	LCD_Send(LCD_TYPE_CMD, LCD_CMD_4BIT_FONT5X8_2LINE);
	LCD_Send(LCD_TYPE_CMD, LCD_CMD_DISPLAY_ON_CTRL_NO_BLINK);
	LCD_Send(LCD_TYPE_CMD, LCD_CMD_ENTRY_MODE_SET);	
	LCD_Send(LCD_TYPE_CMD, LCD_CMD_CLR);
}
void LCD_Clear(void)
{
	LCD_Send(LCD_TYPE_CMD, LCD_CMD_CLR);
}
#ifdef USE_LCD_16X2
void LCD_GotoXY(unsigned char x, unsigned char y)
{
	unsigned char addr;
	if (0 == y)
		addr = 0x80 + x;
	else 
		addr = 0xC0 + x;
	LCD_Send(LCD_TYPE_CMD, addr);
}
#else
#ifdef USE_LCD_16X4
void LCD_GotoXY(unsigned char x, unsigned char y)
{
	unsigned char addr;
	if (0 == y)
		addr = 0x80 + x;
	if (1 == y)
		addr = 0xC0 + x;
	if (2 == y)
		addr = 0x90 + x;
	if (3 == y)
		addr = 0xD0 + x;
	LCD_Send(LCD_TYPE_CMD, addr);
}
#else
#ifdef USE_LCD_20X4
void LCD_GotoXY(unsigned char x, unsigned char y)
{
	unsigned char addr;
	if (0 == y)
		addr = 0x80 + x;
	if (1 == y)
		addr = 0xC0 + x;
	if (2 == y)
		addr = 0x94 + x;
	if (3 == y)
		addr = 0xD4 + x;
	LCD_Send(LCD_TYPE_CMD, addr);
}
#endif
#endif
#endif
void LCD_Write_Char(uint8_t ch)
{
	LCD_Send(LCD_TYPE_DATA, ch); 
}
void LCD_Write_String(uint8_t* text)
{
	while (*text)
		LCD_Write_Char(*text ++);
}
