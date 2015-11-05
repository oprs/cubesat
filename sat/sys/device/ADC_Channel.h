
#ifndef _QB50_SYS_DEVICE_ADC_CHANNEL_H
#define _QB50_SYS_DEVICE_ADC_CHANNEL_H

#ifndef _QB50_SYS_DEVICE_ADC_H
 #error "can't include ADC_Channel.h, try ADC.h instead"
#endif


class Channel : public Device
{

   public:

      ADC& _adc;

      Channel( ADC& adc, const char *name )
      : Device( name ), _adc( adc )
      { ; }

      virtual ~Channel()
      { ; }

      virtual Channel& init    ( void )                = 0;
      virtual Channel& enable  ( bool silent = false ) = 0;
      virtual Channel& disable ( bool silent = false ) = 0;

      inline adcval_t read( void ) __attribute__(( always_inline ))
      { return _adc.read( *this ); }

};


#endif /*_QB50_SYS_DEVICE_ADC_CHANNEL_H*/

/*EoF*/
