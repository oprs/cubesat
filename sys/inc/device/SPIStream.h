
#ifndef _QB50_SYS_DEVICE_SPI_STREAM_H
#define _QB50_SYS_DEVICE_SPI_STREAM_H

#include "GPIOPin.h"
#include "DMAStream.h"


namespace qb50 {

   class SPIStream : Device
   {
      friend class SPI;

      public:

         SPIStream( GPIOPin& pin, DMAStream& ds, uint32_t dc );
         ~SPIStream();

         SPIStream& reset   ( void );
         SPIStream& enable  ( void );
         SPIStream& disable ( void );

         GPIOPin&   pin;  /* GPIO pin    */
         DMAStream& ds;   /* DMA stream  */
         uint32_t   dc;   /* DMA channel */
   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_SPI_STREAM_H*/

/*EoF*/
