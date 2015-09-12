
#ifndef _QB50_SYS_DEVICE_UART_H
#define _QB50_SYS_DEVICE_UART_H

#include <FreeRTOS.h>
#include <semphr.h>

#include "BusDevice.h"
#include "GPIOPin.h"
#include "NVIC.h"
#include "FIFO.hpp"


namespace qb50 {

	class UART : public BusDevice
	{
		public:

			UART( Bus& bus,
			      const uint32_t iobase,
			      const uint32_t periph,
					const char    *name,
			      GPIOPin&       rxPin,
			      GPIOPin&       txPin,
			      const uint32_t IRQn,
			      GPIOPin::Alt   alt
			);

			~UART();

			UART& enable   ( void );
			UART& disable  ( void );

			UART& baudRate ( unsigned rate );

			/* synchronous read */
			size_t read    (       void *x, size_t len );
			size_t readLine(       void *x, size_t len );
			/* synchronous write */
			size_t write   ( const void *x, size_t len );

			void isr( void );

		private:

			xSemaphoreHandle _rdLock;  /**< global lock on the read end  */
			xSemaphoreHandle _isrRXNE; /**< ISR semaphore bound to RXNE  */

			FIFO<uint8_t>  _fo;

			GPIOPin&       _rxPin;
			GPIOPin&       _txPin;
			const uint32_t _IRQn;
			GPIOPin::Alt   _alt;
	};

	extern qb50::UART UART1;
	extern qb50::UART UART2;
	extern qb50::UART UART3;
	extern qb50::UART UART4;
	extern qb50::UART UART5;
	extern qb50::UART UART6;

} /* qb50 */


extern "C" {
	void USART1_IRQHandler ( void );
	void USART2_IRQHandler ( void );
	void USART3_IRQHandler ( void );
	void UART4_IRQHandler  ( void );
	void UART5_IRQHandler  ( void );
	void USART6_IRQHandler ( void );
}


#endif /*_QB50_SYS_DEVICE_UART_H*/

/*EoF*/
