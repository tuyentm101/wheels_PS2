#include "PS2.h"
/*----------------------------------
----------------------------------*/

uint8_t byte[6];

void ps2_init (void)
{
	uint8_t i;
	
	SPI_CLK_1;
	SPI_MOSI_1;
	SPI_SS_1;
	for (i = 0; i < 6; i++)
		byte[i] = 0xFF;
}

uint8_t SPI_Tx(uint8_t tByte)
{
	uint8_t i;
	uint8_t rByte = 0x00;
	
	SPI_CLK_1;
	SPI_MOSI_1;
	
	for (i = 0x01; i > 0 ; i <<= 1)
	{
		if (tByte & i)
			SPI_MOSI_1;
		else
			SPI_MOSI_0;
		
		SPI_CLK_0;
		SystemTick_Delay_Us(50);
		SPI_CLK_1;
		SystemTick_Delay_Us(50);
		
		if (SPI_READ_MISO)
			rByte |= i;
	}	 
	return rByte;
}
uint8_t SPI_Rx(void)
{
	uint8_t rByte = 0;
	uint8_t i;
	
	SPI_CLK_1;
	
	for (i = 0x01; i > 0; i<<=1)
	{
		SPI_CLK_0;
		SystemTick_Delay_Us(50);
		SPI_CLK_1;
		SystemTick_Delay_Us(50);
		
		if (SPI_READ_MISO)
			rByte |= i;
	}
	return rByte;
}	
uint8_t ps2_get_mode (void)
{
	SPI_Tx(0x01);					     //start command
	return SPI_Tx(0x42);      //request command and get back type of mode
}  
void update_ps2_button (void)
{
	SPI_SS_0;
	SystemTick_Delay_Us(10);
	
//	if (PS2_MODE_NONE == ps2_get_mode())
//	{
//	  SPI_SS_1;
//		return 1;
//	}
	if (PS2_MODE_DIGITAL == ps2_get_mode())
	{
		SPI_Tx(0x00); 	        //get 0x5A
		byte[0] = SPI_Rx(); 		//digital button group 1
		byte[1] = SPI_Rx();			//digital button group 2
	}
	if (PS2_MODE_ANALOG_RED_LED == ps2_get_mode())
	{
		SPI_Tx(0x00); 	        //get 0x5A
		byte[0] = SPI_Rx(); 		//Bit 0 -> 7: SELECT JOYR JOYL START UP RIGHT DOWN LEFT
		byte[1] = SPI_Rx(); 		//Bit 0 -> 7: L2   R2   L1   R1   /\   O    X    []
		byte[2] = SPI_Rx(); 		//Right Joystick X axis value: 				0x00 = Left		0xFF = Right
		byte[3] = SPI_Rx(); 		//Right Joystick Y axis value: 				0x00 = Up		  0xFF = Down
		byte[4] = SPI_Rx(); 		// Left Joystick X axis value: 				0x00 = Left		0xFF = Right
		byte[5] = SPI_Rx(); 	  // Left Joystick Y axis value:				0x00 = Up		  0xFF = Down
	}
	SystemTick_Delay_Us(5);
	SPI_SS_1;
 }
