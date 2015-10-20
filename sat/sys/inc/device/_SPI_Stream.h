
#ifndef _QB50_SYS_DEVICE_SPI_STREAM_H
#define _QB50_SYS_DEVICE_SPI_STREAM_H


class Stream : public Device
{

   public:

      Stream( DMA::Stream&         dmaStream,
              DMA::Stream::Channel dmaChannel,
              const char          *name,
              GPIO::Pin&           pin,
              GPIO::Pin::Alt       alt );

      ~Stream();

      Stream& init    ( void );
      Stream& enable  ( bool silent = false );
      Stream& disable ( bool silent = false );

      DMA::Stream&         dmaStream;
      DMA::Stream::Channel dmaChannel;
      GPIO::Pin&           _pin;
      GPIO::Pin::Alt       _alt;

};


#endif /*_QB50_SYS_DEVICE_SPI_STREAM_H*/

/*EoF*/
