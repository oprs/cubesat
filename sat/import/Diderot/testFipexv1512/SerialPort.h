#ifndef CSERIALPORT_H
#define CSERIALPORT_H
//#include <stm32f4xx_spi.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_usart.h>
#include <stm32f4xx_rcc.h>
#include <stdio.h>
typedef	uint8_t	byte ;


class CSerialPort
{

private:
	USART_TypeDef* m_USARTx;

public:
	bool m_status;
	CSerialPort(int numPort);
	~CSerialPort(void);

	CSerialPort(char*numCom, int baudRate, byte parite, byte dataBits, byte StopBits);

	bool read(byte data[], uint32_t offset, uint32_t taille);
	bool read(byte &data);
	bool write(byte data[],uint32_t offset,uint32_t count);
	bool write(byte data);
	void close();

};

#endif
