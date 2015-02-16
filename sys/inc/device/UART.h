
#ifndef _QB50_SYS_DEVICE_UART_H
#define _QB50_SYS_DEVICE_UART_H

#include "FreeRTOS.h"
#include "semphr.h"

#include "stm32f4xx_usart.h"
#include "CoreDevice.h"


namespace qb50 {

   class UART : public CoreDevice
   {
      public:

         UART( Bus& bus, const uint32_t periph, const uint32_t iobase );
         ~UART();

         void isr     ( void );

         void reset   ( void );
         void enable  ( void );
         void disable ( void );

         /* synchronous read */
         size_t read  (       void *x, size_t len, TickType_t timeout = portMAX_DELAY );
         /* synchronous write */
         size_t write ( const void *x, size_t len, TickType_t timeout = portMAX_DELAY );

      private:

         size_t _readIRQ  (       void *x, size_t len, TickType_t timeout );
         size_t _readDMA  (       void *x, size_t len, TickType_t timeout );

         size_t _writeIRQ ( const void *x, size_t len, TickType_t timeout );
         size_t _writeDMA ( const void *x, size_t len, TickType_t timeout );

         xSemaphoreHandle rdLock;  /**< global lock on the read end  */
         xSemaphoreHandle wrLock;  /**< global lock on the write end */
         xSemaphoreHandle isrRXNE; /**< ISR semaphore bound to RXNE  */
         xSemaphoreHandle isrTXE;  /**< ISR semaphore bound to TXE   */
   };

   /* CMSIS keeps polluting the whole namespace with
      hundreds of macros, we need to clear those off. */

   #undef UART1
   #undef UART2
   #undef UART3
   #undef UART4
   #undef UART5
   #undef UART6

   extern qb50::UART UART1;
   extern qb50::UART UART2;
   extern qb50::UART UART3;
   extern qb50::UART UART4;
 //extern qb50::UART UART5;
   extern qb50::UART UART6;

} /* qb50 */


extern "C" {
   void USART1_IRQHandler ( void );
   void USART2_IRQHandler ( void );
   void USART3_IRQHandler ( void );
   void UART4_IRQHandler  ( void );
 //void UART5_IRQHandler  ( void );
   void USART6_IRQHandler ( void );
}


#endif /*_QB50_SYS_DEVICE_UART_H*/

/*EoF*/
