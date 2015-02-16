#include "adc.h"


CAdc::CAdc(CSpi *spi, CS numCS)
{
	m_spi=spi;
	m_cs=numCS;
}



byte CAdc:: read(channel canal)
{

	uint8_t Recevie[3];
	uint8_t valeur;
	uint8_t b7b2 = 0, b1b0 = 0;


	m_GPIO_InitStruct_adc.GPIO_Mode = GPIO_Mode_OUT;
	m_GPIO_InitStruct_adc.GPIO_OType = GPIO_OType_PP;
	m_GPIO_InitStruct_adc.GPIO_Speed = GPIO_Speed_50MHz;
	m_GPIO_InitStruct_adc.GPIO_PuPd = GPIO_PuPd_UP;
	/* Configure the chip select pin
		in this case we will use PA6 */
	switch (m_cs)
	{
		case cs1:
			m_GPIO_InitStruct_adc.GPIO_Pin = GPIO_Pin_4;
			GPIO_Init(GPIOA, &m_GPIO_InitStruct_adc);
			break;
		case cs2:
			m_GPIO_InitStruct_adc.GPIO_Pin = GPIO_Pin_5;
			GPIO_Init(GPIOA, &m_GPIO_InitStruct_adc);
			break;
		case cs3:
			m_GPIO_InitStruct_adc.GPIO_Pin = GPIO_Pin_6;
			GPIO_Init(GPIOA, &m_GPIO_InitStruct_adc);
			break;
		case cs5:
			m_GPIO_InitStruct_adc.GPIO_Pin = GPIO_Pin_4;
			GPIO_Init(GPIOC, &m_GPIO_InitStruct_adc);
			break;

	}


	SPI_Cmd(SPI1, ENABLE);
	m_spi->activerChipSelect(m_cs);


	SPI_I2S_SendData(SPI1, canal);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	SPI_I2S_SendData(SPI1, 0x0);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);

	Recevie[0] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);

	SPI_I2S_SendData(SPI1, 0x0);
	Recevie[1] = SPI_I2S_ReceiveData(SPI1);
	while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	Recevie[2] = SPI_I2S_ReceiveData(SPI1);


	m_spi->desactiverChipSelect(m_cs);


	b7b2 = ((Recevie[1] & 0x3F) << 2);
	b1b0 = ((Recevie[2] & 0xC0))>>6;


	valeur = (b7b2 | b1b0);

	return valeur;
}

CAdc::~CAdc()
{

}

