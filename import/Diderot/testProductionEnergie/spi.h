#ifndef _SPI_H
#define  _SPI_H
#include <stm32f4xx_spi.h>

enum CS
{
	cs0=0,cs1,cs2,cs3,cs4,cs5,cs6
};

/* All six spis work the same principle by default.
 *	- Master
 *	- 8data bits
 *	- data sampled at first edge
 *	- prescaler 32
 *	- firstbit MSB
 *	- software SS pin configure
 *	- direction is full duplex 2 wire
 *
 *	Pinout
 *				|PINS PACK 1			|PINS PACK 2			|PINS PACK 3
 *		SPIX	|MOSI	MISO	SCK		|MOSI	MISO	SCK		|MOSI	MISO	SCK
 *				|
 *		SPI1	|PA7	PA6		PA5		|PB5	PB4		PB3		|
 *		SPI2	|PC3	PC2		PB10	|PB15	PB14	PB13	|PI3	PI2		PI0
 *		SPI3	|PB5	PB4		PB3		|PC12	PC11	PC10	|
 *		SPI4	|PE6	PE5		PE2		|PE14	PE13	PE12	|
 *		SPI5	|PF9	PF8		PF7		|PF11	PH7		PH6		|
 *		SPI6	|PG14	PG12	PG13	|
 *
 *	Possible changes to each SPI. Set this defines in your defines.h file.
 *
 *	Change x with 1-6, to match your SPI
 *
 *	//Default prescaler
 *	#define TM_SPIx_PRESCALER	SPI_BaudRatePrescaler_32
 *	//Specify datasize
 *	#define TM_SPIx_DATASIZE 	SPI_DataSize_8b
 *	//Specify which bit is first
 *	#define TM_SPIx_FIRSTBIT 	SPI_FirstBit_MSB
 *	//Mode, master or slave
 *	#define TM_SPIx_MASTERSLAVE	SPI_Mode_Master
 *	//Specify mode of operation, clock polarity and clock phase
 *	#define TM_SPIx_MODE		TM_SPI_Mode_0
 *
 */

/**
 * Library dependencies
 * - STM32F4xx
 * - STM32F4xx RCC
 * - STM32F4xx GPIO
 * - STM32F4xx SPI
 * - defines.h
 */
/**
 * Includes
 */
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"

/**
 * Every SPIx has 3 pins for MISO, MOSI and SCK
 */
typedef enum {
	pack1,
	pack2,
	pack3
} pinsPack;

typedef enum
{
	spi1,
	spi2,
	spi3
}SPIx;



/**
 * Every SPIx can work in 4 different modes
 */
typedef enum {
	mode0,	//Clock polarity low, clock phase 1st edge
	mode1,	//Clock polarity low, clock phase 2nd edge
	mode2,	//Clock polarity high, clock phase 1st edge
	mode3	//Clock polarity high, clock phase 2nd edge
} SPIMode;

/*enum SPIx
{
	spi1,spi2,spi3,spi4,spi5,spi6
};*/



struct selectSlave
{
	GPIO_TypeDef port;
	GPIO_Pin numPin;

};

struct configSPI
{
	SPIx numSPI;
	pinsPack numPinPack;
	selectSlave numCS;

};
 class CSpi
 {
 public:
	SPI_TypeDef* m_numSPI;
	GPIO_InitTypeDef m_GPIOInitStruct;
	SPI_InitTypeDef m_SPIInitStruct;
	configSPI m_config;

	CSpi(configSPI config);
	~CSpi();
	void init();
	void initSPI1(pinsPack pinspack);
	void initSPI2(pinsPack pinspack);
	void initSPI3(pinsPack pinspack);
	void activerChipSelect(CS numCS);
	void desactiverChipSelect(CS numCS);
	/**
	 * Initialize SPIx
	 *
	 * Parameters:
	 * 	- SPIx:
	 * 		SPI 1 - 6
	 * 	- pinsPack pinspack: select pins pack to use
	 * 		- pack_1
	 * 		- pack_2
	 *		- pinsPack_3
	 */
	void init(SPI_TypeDef* numSPI, pinsPack pack);

	/**
	 * Send and receive data over SPI
	 *
	 * Parameters:
	 * 	- SPI_TypeDef* SPIx: Select SPI which will operate with data
	 * 	- uint8_t data: data to be sent
	 *
	 * Returns: Data returned from slave
	 */
	uint8_t send(uint8_t data);

	/**
	 * Send and receive multiple data bytes over SPI
	 *
	 * Parameters:
	 * 	- SPI_TypeDef* SPIx: Select SPI which will operate with data
	 * 	- uint8_t dataOut: pointer to data to be sent out
	 *	- uint8_t dataIn: pointer to received data
	 *	- uint16_t count: number of bytes to send
	 *
	 * No returns
	 */
	void send(uint8_t* dataOut, uint8_t* dataIn, uint16_t count);

	/**
	 * Write multiple data via SPI
	 *
	 * Parameters:
	 * 	- SPI_TypeDef* SPIx: Select SPI which will operate with data
	 * 	- uint8_t dataOut: pointer to data to be sent out
	 *	- uint16_t count: number of bytes to send
	 *
	 * No returns
	 */
	void write( uint8_t* dataOut, uint16_t count);

	/**
	 * Send and receive multiple data bytes over SPI
	 *
	 * Parameters:
	 * 	- SPI_TypeDef* SPIx: Select SPI which will operate with data
	 *	- uint8_t dataIn: pointer to received data
	 *	- uint8_t dummy: dummy byte to be sent to SPI
	 *	- uint16_t count: number of bytes to receive
	 *
	 * No returns
	 */
	void read( uint8_t *dataIn, uint8_t dummy, uint16_t count);

	/**
	 * Send and receive data over SPI in 16-bit SPI mode
	 * Selected SPI must be set in 16-bit mode
	 *
	 * Parameters:
	 * 	- SPI_TypeDef* SPIx: Select SPI which will operate with data
	 * 	- uint16_t data: data to be sent
	 *
	 * Returns: Data returned from slave
	 */
	uint16_t send( uint16_t data);

	/**
	 * Send and receive multiple data bytes over SPI in 16-bit SPI mode
	 * Selected SPI must be set in 16-bit mode
	 *
	 * Parameters:
	 * 	- SPI_TypeDef* SPIx: Select SPI which will operate with data
	 * 	- uint16_t dataOut: pointer to data to be sent out
	 *	- uint16_t dataIn: pointer to received data
	 *	- uint16_t count: number of bytes to send
	 *
	 * No returns
	 */
	void send( uint16_t* dataOut, uint16_t* dataIn, uint16_t count);

	/**
	 * Write multiple data via SPI in 16-bit SPI mode
	 * Selected SPI must be set in 16-bit mode
	 *
	 * Parameters:
	 * 	- SPI_TypeDef* SPIx: Select SPI which will operate with data
	 * 	- uint16_t dataOut: pointer to data to be sent out
	 *	- uint16_t count: number of bytes to send
	 *
	 * No returns
	 */
	void write( uint16_t* dataOut, uint16_t count);

	/**
	 * Send and receive multiple data bytes over SPI in 16-bit SPI mode
	 * Selected SPI must be set in 16-bit mode
	 *
	 * Parameters:
	 * 	- SPI_TypeDef* SPIx: Select SPI which will operate with data
	 *	- uint16_t dataIn: pointer to received data
	 *	- uint16_t dummy: dummy 16bit to be sent to SPI
	 *	- uint16_t count: number of bytes to receive
	 *
	 * No returns
	 */
	void read( uint16_t* dataIn, uint16_t dummy, uint16_t count);


 };
#endif
