

#include "SerialPort.h"


CSerialPort::~CSerialPort(void)
{

}



CSerialPort::CSerialPort(int numPort,uint32_t baudrate, uint16_t parity, uint16_t wordLength,uint16_t stopBit)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStr;

	uint32_t GPIO_Pin_rx,GPIO_Pin_tx;
	GPIO_TypeDef* GPIOx;

	switch(numPort)
	{
	case 1:
		m_USARTx=USART1;
		GPIOx=GPIOA;
		GPIO_Pin_tx=GPIO_Pin_9;
		GPIO_Pin_rx=GPIO_Pin_10;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
		m_status=true;
		break;
	case 2:
		m_USARTx=USART2;
		GPIOx=GPIOA;
		GPIO_Pin_tx=GPIO_Pin_2;
		GPIO_Pin_rx=GPIO_Pin_3;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
		m_status=true;
		break;
	case 3:
		m_USARTx=USART3;
		GPIOx=GPIOB;
		GPIO_Pin_tx=GPIO_Pin_10;
		GPIO_Pin_rx=GPIO_Pin_11;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
		m_status=true;
		break;
	case 6:
		m_USARTx=USART6;
		GPIOx=GPIOC;
		GPIO_Pin_tx=GPIO_Pin_6;
		GPIO_Pin_rx=GPIO_Pin_7;
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
		GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);
		m_status=true;
		break;
	default:
		m_status=false;
		break;
	}
	if(m_status)
	{
		//Configure tx
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_tx|GPIO_Pin_rx;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOx, &GPIO_InitStructure);




		USART_InitStr.USART_BaudRate= baudrate;
		USART_InitStr.USART_WordLength= wordLength;
		USART_InitStr.USART_StopBits= stopBit;
		USART_InitStr.USART_Parity = parity;
		USART_InitStr.USART_Mode= USART_Mode_Tx | USART_Mode_Rx;
		USART_InitStr.USART_HardwareFlowControl	= USART_HardwareFlowControl_None;
		USART_Init(m_USARTx, &USART_InitStr);
		USART_Cmd(m_USARTx, ENABLE);
	}

}

bool CSerialPort::read(byte data[], uint32_t offset, uint32_t taille)
{
	bool retour=false;
	if(m_status)
	{
		for(int i=offset;i<taille;i++)
		{
			while(USART_GetFlagStatus(m_USARTx, USART_FLAG_RXNE) == RESET);
			data[i]=USART_ReceiveData(m_USARTx);

		}
		retour=true;
	}
	return retour;
}

bool CSerialPort::read(byte &data)
{
	bool retour=false;
	byte i=0;
	if(m_status)
	{
	//	data=USART_ReceiveData(m_USARTx);
		while(USART_GetFlagStatus(m_USARTx, USART_FLAG_RXNE) == RESET);
		data = USART_ReceiveData(m_USARTx);
		if (data <= 0xFF) {
			data = (uint8_t) (data & 0xFF);
		}



	}
	return retour;
}

bool CSerialPort::write(byte data[],uint32_t offset,uint32_t count)
{
	bool retour=false;
	if(m_status)
	{
		for(int i=offset;i<count;i++)
		{
			while (USART_GetFlagStatus(m_USARTx,USART_FLAG_TXE)==RESET);
			USART_SendData(m_USARTx,data[i]);
			while(USART_GetFlagStatus(m_USARTx, USART_FLAG_TC) == RESET);
		}
		retour=true;
	}
	return retour;
}

bool CSerialPort::write(byte data)
{
	bool retour=false;
	if(m_status)
	{
		while (USART_GetFlagStatus(m_USARTx,USART_FLAG_TXE)==RESET);
		USART_SendData(m_USARTx,data);
		while(USART_GetFlagStatus(m_USARTx, USART_FLAG_TC) == RESET);
		retour=true;
	}
	return retour;
}


/*
void envoyerDataDecimalUSART1(uint8_t data){

	char buf[3];
	sprintf(buf, "%u", data);
	for(int i=0;i<3;i++ )
		envoyerDataUSART1(buf[i]);
}



void envoyerDataHexaUSART1(uint8_t data){

	char buf[2];
	sprintf(buf, "%x", data);
	for(int i=0;i<2;i++ )
		envoyerDataUSART1(buf[i]);
}

*/
