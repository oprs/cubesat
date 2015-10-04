
#ifndef _QB50_SYS_DEVICE_SPI_H
#define _QB50_SYS_DEVICE_SPI_H

#include <FreeRTOS.h>
#include <semphr.h>

#include "BusDevice.h"
#include "GPIOPin.h"
#include "SPIStream.h"


namespace qb50 {

   class SPI : public BusDevice
   {
      public:

         SPI( Bus&           bus,
              const uint32_t iobase,
              const uint32_t periph,
              const char*    name,
              SPIStream&     stMISO,
              SPIStream&     stMOSI,
              GPIOPin&       clkPin,
              GPIOPin::Alt   alt
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

         SPIStream&      _stMISO;
         SPIStream&      _stMOSI;
         GPIOPin&        _clkPin;
         GPIOPin::Alt    _alt;
   };

 //extern qb50::SPI SPI1;
 //extern qb50::SPI SPI2;
   extern qb50::SPI SPI3;

} /* qb50 */


extern "C" {
   void SPI1_IRQHandler ( void );
   void SPI2_IRQHandler ( void );
   void SPI3_IRQHandler ( void );
}


#endif /*_QB50_SYS_DEVICE_SPI_H*/

/*EoF*/
