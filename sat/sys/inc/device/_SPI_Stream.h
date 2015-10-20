
#ifndef _QB50_SYS_DEVICE_SPI_STREAM_H
#define _QB50_SYS_DEVICE_SPI_STREAM_H

#ifndef _QB50_SYS_DEVICE_SPI_H
 #error "can't include _SPI_Stream.h, try SPI.h instead"
#endif


class Stream : public Device
{

   public:

      Stream( DMA::Stream& dmaStream,
              DMA::Channel dmaChannel,
              const char   *name,
              GPIO::Pin&   pin,
              GPIO::Alt    alt );

      ~Stream();

      Stream& init    ( void );
      Stream& enable  ( bool silent = false );
      Stream& disable ( bool silent = false );

      DMA::Stream& dmaStream;
      DMA::Channel dmaChannel;
      GPIO::Pin&   _pin;
      GPIO::Alt    _alt;

};


#endif /*_QB50_SYS_DEVICE_SPI_STREAM_H*/

/*EoF*/
