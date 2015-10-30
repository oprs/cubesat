
#ifndef _QB50_SYS_DEVICE_STM32_UART_H
#define _QB50_SYS_DEVICE_STM32_UART_H

#include "device/UART.h"
#include "device/BusSlave.h"
#include "device/GPIO.h"
#include "device/FIFO.hpp"

#include <task.h>


namespace qb50{

   class STM32_UART : public UART, public BusSlave
   {

      public:

         STM32_UART( Bus& bus,
                     const uint32_t iobase,
                     const uint32_t periph,
                     const char    *name,
                     GPIO::Pin&     rxPin,
                     GPIO::Pin&     txPin,
                     const uint32_t IRQn,
                     GPIO::Alt      alt
         );

         ~STM32_UART();

         STM32_UART& init     ( void );
         STM32_UART& enable   ( bool silent = false );
         STM32_UART& disable  ( bool silent = false );
         size_t      read     (       void *x, size_t len );
         size_t      readLine (       void *x, size_t len );
         size_t      write    ( const void *x, size_t len );
         STM32_UART& baudRate ( unsigned rate );

         void isr( void );

      private:

         xSemaphoreHandle _isrRXNE; /**< ISR semaphore bound to RXNE  */
         xSemaphoreHandle _isrTXE;  /**< ISR semaphore bound to TXE   */

         FIFO<uint8_t>    _rxFIFO;  /**< receiver FIFO (input)        */
         FIFO<uint8_t>    _txFIFO;  /**< transmitter FIFO (output)    */

         GPIO::Pin&       _rxPin;
         GPIO::Pin&       _txPin;
         const uint32_t   _IRQn;
         GPIO::Alt        _alt;

   };

} /* qb50 */


extern "C" {
   void USART1_IRQHandler ( void );
   void USART2_IRQHandler ( void );
   void USART3_IRQHandler ( void );
   void UART4_IRQHandler  ( void );
   void UART5_IRQHandler  ( void );
   void USART6_IRQHandler ( void );
}


#endif /*_QB50_SYS_DEVICE_STM32_UART_H*/

/*EoF*/
