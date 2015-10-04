
#ifndef _QB50_SYS_DEVICE_UART_H
#define _QB50_SYS_DEVICE_UART_H

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include "BusDevice.h"
#include "GPIOPin.h"
#include "NVIC.h"
#include "FIFO.hpp"


namespace qb50 {

   class UART : public BusDevice
   {

      private:

         struct IOReq;

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

         UART& init     ( void );
         UART& enable   ( bool silent = false );
         UART& disable  ( bool silent = false );

         UART& ioctl    ( IOReq *req, TickType_t maxWait = portMAX_DELAY );

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

         xQueueHandle     _ioQueue;
         TaskHandle_t     _ioTask;

         FIFO<uint8_t>    _rxFIFO;  /**< receiver FIFO (input)        */
         FIFO<uint8_t>    _txFIFO;  /**< transmitter FIFO (output)    */

         GPIOPin&         _rxPin;
         GPIOPin&         _txPin;
         const uint32_t   _IRQn;
         GPIOPin::Alt     _alt;

         bool _enabled;

         /* IOCTLs */

         enum IOCTL {
            ENABLE   = 0,
            DISABLE  = 1,
            READ     = 2,
            READLINE = 3,
            WRITE    = 4,
            BAUDRATE = 5
         };

         struct IOReq
         {
            IOCTL        _op;
            TaskHandle_t _handle;

            IOReq( IOCTL op ) : _op( op )
            { _handle = xTaskGetCurrentTaskHandle(); }

            ~IOReq()
            { ; }
         };

         struct IOReq_read : public IOReq
         {
            void  *_x;
            size_t _len;

            IOReq_read( void *x, size_t len )
            : IOReq( READ ), _x( x ), _len( len )
            { ; }
         };

         struct IOReq_readLine : public IOReq
         {
            void  *_x;
            size_t _len;

            IOReq_readLine( void *x, size_t len )
            : IOReq( READLINE ), _x( x ), _len( len )
            { ; }
         };

         struct IOReq_write : public IOReq
         {
            const void *_x;
            size_t    _len;

            IOReq_write( const void *x, size_t len )
            : IOReq( WRITE ), _x( x ), _len( len )
            { ; }
         };

         struct IOReq_baudRate : public IOReq
         {
            unsigned _rate;

            IOReq_baudRate( unsigned rate )
            : IOReq( BAUDRATE ), _rate( rate )
            { ; }
         };

         /* operations */

         void _enable   ( IOReq          *req );
         void _disable  ( IOReq          *req );
         void _read     ( IOReq_read     *req );
         void _readLine ( IOReq_readLine *req );
         void _write    ( IOReq_write    *req );
         void _baudRate ( IOReq_baudRate *req );

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
