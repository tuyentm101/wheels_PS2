#include "user_stm32f1xx_spi.h"


void SPI_Configuration(uint16_t SPI_mode)
{
	SPI_InitTypeDef SPI_InitStructure;
	if (SPI_Mode_Master == SPI_mode)
	{
		 SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
		 GPIO_SPI_Configuration(SPI_Mode_Master);
	}
	else 
	{
		SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
		GPIO_SPI_Configuration(SPI_Mode_Slave);
	}
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   //only 8 LSB of DR used in transmission/reception
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;  //Baudrate = 70.312 KBits/s
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPIy, &SPI_InitStructure);

	SPI_NSSInternalSoftwareConfig(SPIy, SPI_NSSInternalSoft_Set); // set bit SSI = 1 in CR1
}

void SPI_LCD5110_Configuration(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	
	GPIO_SPI_Configuration(SPI_Mode_Master);
	
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//bit SPE in CR1
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;   //only 8 LSB of DR used in transmission/reception
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;			//bit SSM = 1 in CR1
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4; //PLK2 / BaudratePrescaler
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
	
	SPI_Init(SPIy, &SPI_InitStructure);
	
	SPI_NSSInternalSoftwareConfig(SPIy, SPI_NSSInternalSoft_Set); // set bit SSI = 1 in CR1
//	SPI_SSOutputCmd(SPIy, ENABLE); 		// Enables or disables the SS output for the selected SPI, bit SSOE = 1 CR2
	
	/*
	Co 2 kieu SPI chay duoc khi NSS pin la output
	1. SSM = 1 (soft), SSI = 0, SSOE = 0. NSS la GPIO output
	2. SSM = 0 (Hard), SSI = 0, SSOE = 1. NSS la GPIO output
	*/
	SPI_Cmd(SPIy, ENABLE);
}

void SPI_Slave_Select(uint8_t action)
{
	GPIO_WriteBit(SPIy_GPIO, SPIy_PIN_NSS, (action) ? Bit_SET : Bit_RESET);
}	

void SPI_Send_8bit(uint8_t data)
{
	SPI_I2S_SendData(SPIy,(uint16_t)data);
	while (RESET == SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE));		//waiting for TxBuffer is empty, means data is sent
}
uint16_t SPI_Receive_8bit(void)
{
	while (RESET == SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_RXNE));
	return SPI_I2S_ReceiveData(SPIy);
}

void SPI_Send_16bit(uint16_t data)
{
	/*--------Send MSByte----------*/
	while (RESET == SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE));	
	SPI_I2S_SendData(SPIy, (data & 0xFF00) >> 8);;
	while (RESET == SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE));
	/*--------Send LSByte----------*/
	SPI_I2S_SendData(SPIy, data & 0x00FF);
	while (RESET == SPI_I2S_GetFlagStatus(SPIy, SPI_I2S_FLAG_TXE));
}
