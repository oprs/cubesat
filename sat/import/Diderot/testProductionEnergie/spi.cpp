#include "spi.h"
#include <stm32f4xx_spi.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <string.h>


void CSpi::init(void){

	GPIO_InitTypeDef  GPIO_InitStruct_spi_1;
	SPI_InitTypeDef SPI_InitStruct_spi_1;

	// enable clock for used IO pins
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);


	// enable peripheral clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);


	/* configure pins used by SPI1
		* PB3 = SCK
		* PB5 = MISO
		* PB4 = MOSI
		*/


	GPIO_InitStruct_spi_1.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3;
	GPIO_InitStruct_spi_1.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct_spi_1.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct_spi_1.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStruct_spi_1.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStruct_spi_1);
	// connect SPI1 pins to SPI alternate function
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);





	/* configure SPI1 in Mode 0
		* CPOL = 0 --> clock is low when idle
		* CPHA = 0 --> data is sampled at the first edge
		*/
	SPI_InitStruct_spi_1.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // set to full duplex mode, seperate MOSI and MISO lines
	SPI_InitStruct_spi_1.SPI_Mode = SPI_Mode_Master;     // transmit in master mode, NSS pin has to be always high
	SPI_InitStruct_spi_1.SPI_DataSize = SPI_DataSize_8b; // one packet of data is 8 bits wide
	SPI_InitStruct_spi_1.SPI_CPOL = SPI_CPOL_Low;        // clock is low when idle
	SPI_InitStruct_spi_1.SPI_CPHA = SPI_CPHA_1Edge;      // data sampled at first edge
	SPI_InitStruct_spi_1.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set; // set the NSS management to internal and pull internal NSS high
	SPI_InitStruct_spi_1.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; // SPI frequency is APB2 frequency / 4
	SPI_InitStruct_spi_1.SPI_FirstBit = SPI_FirstBit_MSB;// data is transmitted MSB first

	SPI_Init(SPI1, &SPI_InitStruct_spi_1);

	SPI_Cmd(SPI1, ENABLE); // enable SPI1
}


void CSpi::activerChipSelect(CS numCS){

	GPIO_InitTypeDef  GPIO_InitStruct_cs;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStruct_cs.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_0 |GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4;
	GPIO_InitStruct_cs.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct_cs.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct_cs.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStruct_cs.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct_cs);

	GPIO_InitStruct_cs.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct_cs.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct_cs.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct_cs.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStruct_cs.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStruct_cs);

	switch(numCS)
		{
			case cs1:
				GPIO_SetBits(GPIOA,GPIO_Pin_4);
				GPIO_SetBits(GPIOA,GPIO_Pin_7);
				GPIO_SetBits(GPIOA,GPIO_Pin_0);
				GPIO_SetBits(GPIOA,GPIO_Pin_6);
				GPIO_SetBits(GPIOA,GPIO_Pin_5);
				GPIO_SetBits(GPIOC,GPIO_Pin_4);
				GPIO_ResetBits(GPIOA,GPIO_Pin_4);
				break;
			case cs2:
				GPIO_SetBits(GPIOA,GPIO_Pin_5);
				GPIO_SetBits(GPIOA,GPIO_Pin_7);
				GPIO_SetBits(GPIOA,GPIO_Pin_0);
				GPIO_SetBits(GPIOA,GPIO_Pin_6);
				GPIO_SetBits(GPIOA,GPIO_Pin_4);
				GPIO_SetBits(GPIOC,GPIO_Pin_4);
				GPIO_ResetBits(GPIOA,GPIO_Pin_5);
				break;
			case cs3:
				GPIO_SetBits(GPIOA,GPIO_Pin_6);
				GPIO_SetBits(GPIOA,GPIO_Pin_7);
				GPIO_SetBits(GPIOA,GPIO_Pin_0);
				GPIO_SetBits(GPIOA,GPIO_Pin_5);
				GPIO_SetBits(GPIOA,GPIO_Pin_4);
				GPIO_SetBits(GPIOC,GPIO_Pin_4);
				GPIO_ResetBits(GPIOA,GPIO_Pin_6);
				break;
			case cs4:
				GPIO_SetBits(GPIOA,GPIO_Pin_7);
				GPIO_SetBits(GPIOA,GPIO_Pin_0);
				GPIO_SetBits(GPIOA,GPIO_Pin_6);
				GPIO_SetBits(GPIOA,GPIO_Pin_5);
				GPIO_SetBits(GPIOA,GPIO_Pin_4);
				GPIO_SetBits(GPIOC,GPIO_Pin_4);
				GPIO_ResetBits(GPIOA,GPIO_Pin_7);
				break;
			case cs5:
				GPIO_SetBits(GPIOC,GPIO_Pin_4);
				GPIO_SetBits(GPIOA,GPIO_Pin_7);
				GPIO_SetBits(GPIOA,GPIO_Pin_6);
				GPIO_SetBits(GPIOA,GPIO_Pin_5);
				GPIO_SetBits(GPIOA,GPIO_Pin_4);
				GPIO_SetBits(GPIOA,GPIO_Pin_0);
				GPIO_ResetBits(GPIOC,GPIO_Pin_4);
				break;
			case cs6:
				GPIO_SetBits(GPIOA,GPIO_Pin_0);
				GPIO_SetBits(GPIOA,GPIO_Pin_7);
				GPIO_SetBits(GPIOA,GPIO_Pin_6);
				GPIO_SetBits(GPIOA,GPIO_Pin_5);
				GPIO_SetBits(GPIOA,GPIO_Pin_4);
				GPIO_SetBits(GPIOC,GPIO_Pin_4);
				GPIO_ResetBits(GPIOA,GPIO_Pin_0);
				break;

	}


}

void CSpi::desactiverChipSelect(CS numCS){

	GPIO_InitTypeDef  GPIO_InitStruct_cs;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStruct_cs.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_0 |GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4;
	GPIO_InitStruct_cs.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct_cs.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct_cs.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStruct_cs.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStruct_cs);

	GPIO_InitStruct_cs.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct_cs.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct_cs.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct_cs.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_InitStruct_cs.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStruct_cs);

	switch(numCS)
	{
		case cs1:
			GPIO_SetBits(GPIOA,GPIO_Pin_4);
			break;
		case cs2:
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			break;
		case cs3:
			GPIO_SetBits(GPIOA,GPIO_Pin_6);
			break;
		case cs4:
			GPIO_SetBits(GPIOA,GPIO_Pin_7);
			break;
		case cs5:
			GPIO_SetBits(GPIOC,GPIO_Pin_4);
			break;
		case cs6:
			GPIO_SetBits(GPIOA,GPIO_Pin_0);
			break;

	}
}

CSpi::CSpi(configSPI config)
{
	m_config=config;

	init();
}

CSpi::~CSpi()
{

}


void initSPI1(pinsPack pinspack);
void initSPI2(pinsPack pinspack);
void initSPI3(pinsPack pinspack);
void initSPI4(pinsPack pinspack);
void initSPI5(pinsPack pinspack);
void initSPI6();



void CSpi::init()
{

	SPI_StructInit(&m_SPIInitStruct);
	m_SPIInitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	m_SPIInitStruct.SPI_DataSize =SPI_DataSize_8b;
	m_SPIInitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	m_SPIInitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	m_SPIInitStruct.SPI_Mode = SPI_Mode_Master;
	m_SPIInitStruct.SPI_CPOL = SPI_CPOL_Low;
	m_SPIInitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	m_SPIInitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_Cmd(numSPI, DISABLE);
	SPI_DeInit(numSPI);
	SPI_Init(numSPI, &m_SPIInitStruct);


		//Common settings for all pins
	m_GPIOInitStruct.GPIO_OType = GPIO_OType_PP;
	m_GPIOInitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	m_GPIOInitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	m_GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF;


	if(numSPI==SPI1) initSPI1(pack);
	else if (numSPI==SPI2) 	initSPI2(pack);
		else if(numSPI==SPI3) 	initSPI3(pack);

	SPI_Cmd(numSPI, ENABLE);

}

uint8_t CSpi::send(uint8_t data) {
	/* Fill output buffer with data */
	m_numSPI->DR = data;
	/* Wait for transmission to complete */
	while (!SPI_I2S_GetFlagStatus(m_numSPI, SPI_I2S_FLAG_TXE));
	/* Wait for received data to complete */
	while (!SPI_I2S_GetFlagStatus(m_numSPI, SPI_I2S_FLAG_RXNE));
	/* Wait for SPI to be ready */
	while (SPI_I2S_GetFlagStatus(m_numSPI, SPI_I2S_FLAG_BSY));
	/* Return data from buffer */
	return m_numSPI->DR;
}

void CSpi::send( uint8_t* dataOut, uint8_t* dataIn, uint16_t count) {
	uint16_t i;
	for (i = 0; i < count; i++) {
		dataIn[i] = send(dataOut[i]);
	}
}

void CSpi::write( uint8_t* dataOut, uint16_t count) {
	uint16_t i;
	for (i = 0; i < count; i++) {
		send( dataOut[i]);
	}
}

void CSpi::read(uint8_t* dataIn, uint8_t dummy, uint16_t count) {
	uint16_t i;
	for (i = 0; i < count; i++) {
		dataIn[i] = send( dummy);
	}
}

uint16_t CSpi::send(uint16_t data) {
	/* Fill output buffer with data */
	m_numSPI->DR = data;
	/* Wait for transmission to complete */
	while (!SPI_I2S_GetFlagStatus(m_numSPI, SPI_I2S_FLAG_TXE));
	/* Wait for received data to complete */
	while (!SPI_I2S_GetFlagStatus(m_numSPI, SPI_I2S_FLAG_RXNE));
	/* Wait for SPI to be ready */
	while (SPI_I2S_GetFlagStatus(m_numSPI, SPI_I2S_FLAG_BSY));
	/* Return data from buffer */
	return m_numSPI->DR;
}

void CSpi::send( uint16_t* dataOut, uint16_t* dataIn, uint16_t count) {
	uint16_t i;
	for (i = 0; i < count; i++) {
		dataIn[i] = send(dataOut[i]);
	}
}

void CSpi:: write( uint16_t* dataOut, uint16_t count) {
	uint16_t i;
	for (i = 0; i < count; i++) {
		send( dataOut[i]);
	}
}

void CSpi::read( uint16_t* dataIn, uint16_t dummy, uint16_t count) {
	uint16_t i;
	for (i = 0; i < count; i++) {
		dataIn[i] = send( dummy);
	}
}

void CSpi::initSPI1(pinsPack pinspack)
{

	if (pinspack == pack1) {
		//Enable clock for GPIOA
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		//Pinspack nr. 1        SCK          MISO         MOSI
		m_GPIOInitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_Init(GPIOA, &m_GPIOInitStruct);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
	} else if (pinspack == pack2) {
		//Enable clock for GPIOB
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		//Pinspack nr. 2        SCK          MISO         MOSI
		m_GPIOInitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
		GPIO_Init(GPIOB, &m_GPIOInitStruct);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);
	}
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
}

void CSpi::initSPI2(pinsPack pinspack)
{

	if (pinspack == pack1) {
		//Enable clock
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		//Pinspack nr. 1        	MISO         MOSI
		m_GPIOInitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
		GPIO_Init(GPIOC, &m_GPIOInitStruct);
		//                      	SCK
		m_GPIOInitStruct.GPIO_Pin = GPIO_Pin_10;
		GPIO_Init(GPIOB, &m_GPIOInitStruct);

		GPIO_PinAFConfig(GPIOC, GPIO_PinSource2, GPIO_AF_SPI2);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource3, GPIO_AF_SPI2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_SPI2);
	} else if (pinspack == pack2) {
		//Enable clock
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		//Pinspack nr. 2        	SCK           MISO          MOSI
		m_GPIOInitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_Init(GPIOB, &m_GPIOInitStruct);

		GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
	} else if (pinspack == pack3) {
		//Enable clock
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
		//Pinspack nr. 2        	SCK         MISO         MOSI
		m_GPIOInitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3;
		GPIO_Init(GPIOB, &m_GPIOInitStruct);

		GPIO_PinAFConfig(GPIOI, GPIO_PinSource0, GPIO_AF_SPI2);
		GPIO_PinAFConfig(GPIOI, GPIO_PinSource2, GPIO_AF_SPI2);
		GPIO_PinAFConfig(GPIOI, GPIO_PinSource3, GPIO_AF_SPI2);
	}
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

}

void CSpi::initSPI3(pinsPack pinspack)
{
		if (pinspack == pack1) {
		//Enable clock
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		//Pinspack nr. 1        SCK          MISO         MOSI
		m_GPIOInitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
		GPIO_Init(GPIOB, &m_GPIOInitStruct);

		GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI3);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI3);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI3);
	} else if (pinspack == pack2) {
		//Enable clock
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		//Pinspack nr. 2        SCK           MISO          MOSI
		m_GPIOInitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
		GPIO_Init(GPIOC, &m_GPIOInitStruct);

		GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_SPI3);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_SPI3);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_SPI3);
	}
	RCC_APB1PeriphClockCmd(pack3, ENABLE);
}
/*
void initSPI4(pinsPack pinspack)
{
	if (pinspack == TM_SPI_PinsPack_1) {
		//Enable clock
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		//Pinspack nr. 1        SCK          MISO         MOSI
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_5 | GPIO_Pin_6;
		GPIO_Init(GPIOE, &GPIO_InitStruct);

		GPIO_PinAFConfig(GPIOE, GPIO_PinSource2, GPIO_AF_SPI4);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_SPI4);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_SPI4);
	} else if (pinspack == TM_SPI_PinsPack_2) {
		//Enable clock
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		//Pinspack nr. 2        SCK           MISO          MOSI
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
		GPIO_Init(GPIOE, &GPIO_InitStruct);

		GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_SPI4);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_SPI4);
		GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_SPI4);
	}
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4, ENABLE);
}

void initSPI5(pinsPack pinspack)
{
	if (pinspack == TM_SPI_PinsPack_1) {
		//Enable clock
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		//Pinspack nr. 1        SCK          MISO         MOSI
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_Init(GPIOF, &GPIO_InitStruct);

		GPIO_PinAFConfig(GPIOF, GPIO_PinSource7, GPIO_AF_SPI5);
		GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_SPI5);
		GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_SPI5);
	} else if (pinspack == TM_SPI_PinsPack_2) {
		//Enable clock
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
		//Pinspack nr. 1        SCK          MISO
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_Init(GPIOF, &GPIO_InitStruct);
		//                      MOSI
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
		GPIO_Init(GPIOF, &GPIO_InitStruct);

		GPIO_PinAFConfig(GPIOF, GPIO_PinSource11, GPIO_AF_SPI5);
		GPIO_PinAFConfig(GPIOH, GPIO_PinSource6, GPIO_AF_SPI5);
		GPIO_PinAFConfig(GPIOH, GPIO_PinSource7, GPIO_AF_SPI5);
	}
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI5, ENABLE);
}

void initSPI6()
{
	//Enable clock
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

	//Pinspack nr. 1        SCK           MISO          MOSI
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_12 | GPIO_Pin_14;
	GPIO_Init(GPIOG, &GPIO_InitStruct);

	GPIO_PinAFConfig(GPIOG, GPIO_PinSource13, GPIO_AF_SPI6);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource12, GPIO_AF_SPI6);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_SPI6);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI6, ENABLE);
}*/


