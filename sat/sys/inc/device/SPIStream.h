
#ifndef _QB50_SYS_DEVICE_SPI_STREAM_H
#define _QB50_SYS_DEVICE_SPI_STREAM_H

#include "GPIOPin.h"
#include "DMAStream.h"


namespace qb50 {

   class SPIStream : Device
   {
      friend class SPI;

      public:

         SPIStream( DMAStream&         dmaStream,
                    DMAStream::Channel dmaChannel,
                    GPIOPin&           pin,
                    GPIOPin::Alt       alt );

         ~SPIStream();

         SPIStream& enable  ( void );
         SPIStream& disable ( void );

         DMAStream&           dmaStream;
         DMAStream::Channel   dmaChannel;
         GPIOPin&             _pin;
         GPIOPin::Alt         _alt;
   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_SPI_STREAM_H*/

/*EoF*/
