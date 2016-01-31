
#ifndef _QB50_SYS_DEVICE_ADC_CHANNEL_H
#define _QB50_SYS_DEVICE_ADC_CHANNEL_H

#ifndef _QB50_SYS_DEVICE_ADC_H
 #error "can't include ADC_Channel.h, try ADC.h instead"
#endif


class Channel
{

   public:

      ADC& _adc;

      Channel( ADC& adc ) : _adc( adc )
      { ; }

      virtual ~Channel()
      { ; }

      inline adcval_t read( void ) __attribute__(( always_inline ))
      { return _adc.read( *this ); }

};


#endif /*_QB50_SYS_DEVICE_ADC_CHANNEL_H*/

/*EoF*/
