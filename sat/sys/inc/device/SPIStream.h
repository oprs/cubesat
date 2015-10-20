
#ifndef _QB50_SYS_DEVICE_SPI_STREAM_H
#define _QB50_SYS_DEVICE_SPI_STREAM_H

#include "GPIO.h"
#include "DMAStream.h"


namespace qb50 {

   class SPIStream : public Device
   {
      friend class SPI;

      public:

         SPIStream( DMAStream&         dmaStream,
                    DMAStream::Channel dmaChannel,
                    const char        *name,
                    GPIO::Pin&         pin,
                    GPIO::Pin::Alt     alt );

         ~SPIStream();

         SPIStream& init    ( void );
         SPIStream& enable  ( bool silent = false );
         SPIStream& disable ( bool silent = false );

         DMAStream&           dmaStream;
         DMAStream::Channel   dmaChannel;
         GPIO::Pin&           _pin;
         GPIO::Pin::Alt       _alt;
   };

   void DMA1_Stream0_IRQHandler( void );
   void DMA1_Stream1_IRQHandler( void );
   void DMA1_Stream2_IRQHandler( void );
   void DMA1_Stream3_IRQHandler( void );
   void DMA1_Stream4_IRQHandler( void );
   void DMA1_Stream5_IRQHandler( void );
   void DMA1_Stream6_IRQHandler( void );
   void DMA1_Stream7_IRQHandler( void );

   void DMA2_Stream0_IRQHandler( void );
   void DMA2_Stream1_IRQHandler( void );
   void DMA2_Stream2_IRQHandler( void );
   void DMA2_Stream3_IRQHandler( void );
   void DMA2_Stream4_IRQHandler( void );
   void DMA2_Stream5_IRQHandler( void );
   void DMA2_Stream6_IRQHandler( void );
   void DMA2_Stream7_IRQHandler( void );

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_SPI_STREAM_H*/

/*EoF*/
