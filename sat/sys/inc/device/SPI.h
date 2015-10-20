
#ifndef _QB50_SYS_DEVICE_SPI_H
#define _QB50_SYS_DEVICE_SPI_H

#include "Device.h"
#include "BusSlave.h"
#include "GPIO.h"
#include "DMA.h"


namespace qb50 {

   class SPI : public Device, public BusSlave
   {

      public:

         #include "_SPI_Stream.h"

         SPI( Bus&           bus,
              const uint32_t iobase,
              const uint32_t periph,
              const char*    name,
              Stream&        stMISO,
              Stream&        stMOSI,
              GPIO::Pin&     clkPin,
              GPIO::Pin::Alt alt
         );

         ~SPI();

         SPI& init    ( void );
         SPI& enable  ( bool silent = false );
         SPI& disable ( bool silent = false );

         SPI& grab    ( void );
         SPI& release ( void );

         SPI& master  ( void );
         SPI& slave   ( void );

         /* synchronous transfer */

         SPI& xfer    ( const void *src, void *dst, size_t len );
         SPI& write   ( const void *src, size_t len );
         SPI& read    ( void *dst, size_t len );

         SPI& pollXfer( const void *src, void *dst, size_t len );

         void isr     ( void );


      private:

         SPI& _xfer   ( void );

         Stream&        _stMISO;
         Stream&        _stMOSI;
         GPIO::Pin&     _clkPin;
         GPIO::Pin::Alt _alt;

   };

} /* qb50 */


extern "C" {
   void SPI1_IRQHandler ( void );
   void SPI2_IRQHandler ( void );
   void SPI3_IRQHandler ( void );
}


#endif /*_QB50_SYS_DEVICE_SPI_H*/

/*EoF*/
