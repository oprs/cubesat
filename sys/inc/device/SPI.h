
#ifndef _QB50_SYS_DEVICE_SPI_H
#define _QB50_SYS_DEVICE_SPI_H

#include "FreeRTOS.h"
#include "semphr.h"

#include "stm32f4xx_spi.h"
#include "CoreDevice.h"
#include "DMAChannel.h"


namespace qb50 {

   class SPI : public CoreDevice
   {
      public:

         SPI( Bus& bus, const uint32_t periph, const uint32_t iobase, DMAChannel& ch1, DMAChannel& ch2 );
         ~SPI();

         void reset   ( void );
         void enable  ( void );
         void disable ( void );

         void isr( void );

         /* synchronous read */
         size_t read  (                  void *dst, size_t len, bool useDMA = false );
         /* synchronous write */
         size_t write ( const void *src,            size_t len, bool useDMA = false );
         /* synchronous transfer */
         size_t xfer  ( const void *src, void *dst, size_t len, bool useDMA = false );

         DMAChannel& ch1;
         DMAChannel& ch2;

      private:

         void setupGPIO ( void );
         void setupNVIC ( void );

         xSemaphoreHandle lock;    /**< global lock on the device */
         xSemaphoreHandle isrRXNE; /**< ISR semaphore bound to RXNE  */
         xSemaphoreHandle isrTXE;  /**< ISR semaphore bound to TXE   */

         GPIO_InitTypeDef GPIOis;
         NVIC_InitTypeDef NVICis;
         SPI_InitTypeDef  SPIis;
   };

   /* CMSIS keeps polluting the whole namespace with
      hundreds of macros, we need to clear those off. */

   #undef SPI1
   #undef SPI2
   #undef SPI3

   extern qb50::SPI SPI1;
   extern qb50::SPI SPI2;
   extern qb50::SPI SPI3;

} /* qb50 */


extern "C" {
   void SPI1_IRQHandler ( void );
   void SPI2_IRQHandler ( void );
   void SPI3_IRQHandler ( void );
}


#endif /*_QB50_SYS_DEVICE_SPI_H*/

/*EoF*/
