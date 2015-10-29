
#ifndef _QB50_SYS_DEVICE_UART_H
#define _QB50_SYS_DEVICE_UART_H

#include "Device.h"
#include "BusSlave.h"
#include "GPIO.h"
#include "NVIC.h"
#include "FIFO.hpp"

#include <task.h>


namespace qb50 {

   class UART : public Device, public BusSlave
   {

      private:

         struct IOReq;

      public:

         UART( Bus& bus,
               const uint32_t iobase,
               const uint32_t periph,
               const char    *name,
               GPIO::Pin&     rxPin,
               GPIO::Pin&     txPin,
               const uint32_t IRQn,
               GPIO::Alt      alt
         );

         ~UART();

         UART& init     ( void );
         UART& enable   ( bool silent = false );
         UART& disable  ( bool silent = false );

         /* synchronous read */
         size_t read    (       void *x, size_t len );
         size_t readLine(       void *x, size_t len );
         /* synchronous write */
         size_t write   ( const void *x, size_t len );
         /* set baud rate */
         UART&  baudRate( unsigned rate );

         void isr( void );
         void run( void );

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


#endif /*_QB50_SYS_DEVICE_UART_H*/

/*EoF*/
