
#ifndef _QB50_SYS_DEVICE_STM32_SPI_STREAM_H
#define _QB50_SYS_DEVICE_STM32_SPI_STREAM_H

#ifndef _QB50_SYS_DEVICE_SPI_H
 #error "can't include _SPI_Stream.h, try SPI.h instead"
#endif


class Stream : public SPI::Stream
{

   public:

      Stream( DMA::Stream&       dmaStream,
              DMA::Channel       dmaChannel,
              const char        *name,
              STM32_GPIO::Pin&   pin,
              STM32_GPIO::Alt    alt );

      ~Stream();

      Stream& init    ( void );
      Stream& enable  ( bool silent = false );
      Stream& disable ( bool silent = false );

      DMA::Stream&      dmaStream;
      DMA::Channel      dmaChannel;
      STM32_GPIO::Pin& _pin;
      STM32_GPIO::Alt  _alt;

};


#endif /*_QB50_SYS_DEVICE_STM32_SPI_STREAM_H*/

/*EoF*/
