
#ifndef _QB50_SYS_DEVICE_MAX111x_CHANNEL_H
#define _QB50_SYS_DEVICE_MAX111x_CHANNEL_H

#ifndef _QB50_SYS_DEVICE_MAX111x_H
 #error "can't include MAX111x_Channel.h, try MAX111x.h instead"
#endif


class Channel : public Device, public ADC::Channel
{

   public:

      ChId _id;

      Channel( MAX111x& adc, const char *name, ChId id );
      virtual ~Channel();

      Channel& init    ( void );
      Channel& enable  ( bool silent = false );
      Channel& disable ( bool silent = false );

};


#endif /*_QB50_SYS_DEVICE_MAX111x_CHANNEL_H*/

/*EoF*/

