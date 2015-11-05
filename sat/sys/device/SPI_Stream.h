
#ifndef _QB50_SYS_DEVICE_SPI_STREAM_H
#define _QB50_SYS_DEVICE_SPI_STREAM_H

#ifndef _QB50_SYS_DEVICE_SPI_H
 #error "can't include SPI_Stream.h, try SPI.h instead"
#endif


class Stream : public Device
{

   public:

      Stream( const char *name )
         : Device( name )
      { ; }

      virtual ~Stream()
      { ; }

      virtual Stream& init    ( void                ) = 0;
      virtual Stream& enable  ( bool silent = false ) = 0;
      virtual Stream& disable ( bool silent = false ) = 0;

};


#endif /*_QB50_SYS_DEVICE_SPI_STREAM_H*/

/*EoF*/
