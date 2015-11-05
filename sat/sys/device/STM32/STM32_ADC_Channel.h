
#ifndef _QB50_SYS_DEVICE_STM32_ADC_CHANNEL_H
#define _QB50_SYS_DEVICE_STM32_ADC_CHANNEL_H

#ifndef _QB50_SYS_DEVICE_STM32_ADC_H
 #error "can't include STM32_ADC_Channel.h, try STM32_ADC.h instead"
#endif


class Channel : public ADC::Channel
{

   public:

      ChId             _id;
      STM32_GPIO::Pin &_pin;

      Channel( STM32_ADC& adc, const char *name, ChId id, STM32_GPIO::Pin& pin );
      virtual ~Channel();

      Channel& init    ( void );
      Channel& enable  ( bool silent = false );
      Channel& disable ( bool silent = false );

};


#endif /*_QB50_SYS_DEVICE_STM32_ADC_CHANNEL_H*/

/*EoF*/
