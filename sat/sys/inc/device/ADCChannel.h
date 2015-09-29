
#ifndef _QB50_SYS_DEVICE_ADC_CHANNEL_H
#define _QB50_SYS_DEVICE_ADC_CHANNEL_H

#include "device/MAX111x.h"


namespace qb50 {

   class ADCChannel : public Device
   {

      public:

         ADCChannel( MAX111x& adc, MAX111x::Channel, const char *name, float mul );
         ~ADCChannel();

         ADCChannel& init    ( void );
         ADCChannel& enable  ( bool silent = false );
         ADCChannel& disable ( bool silent = false );

         float       read    ( void );

      private:

         MAX111x&         _adc;
         MAX111x::Channel _chan;
         float            _mul;

   };

   extern qb50::ADCChannel& ADC1CH0;
   extern qb50::ADCChannel& ADC1CH1;
   extern qb50::ADCChannel& ADC1CH2;
   extern qb50::ADCChannel& ADC1CH3;
   extern qb50::ADCChannel& ADC1CH4;
   extern qb50::ADCChannel& ADC1CH5;
   extern qb50::ADCChannel& ADC1CH6;
   extern qb50::ADCChannel& ADC1CH7;

   extern qb50::ADCChannel& ADC2CH0;
   extern qb50::ADCChannel& ADC2CH1;
   extern qb50::ADCChannel& ADC2CH2;
   extern qb50::ADCChannel& ADC2CH3;
   extern qb50::ADCChannel& ADC2CH4;
   extern qb50::ADCChannel& ADC2CH5;
   extern qb50::ADCChannel& ADC2CH6;
   extern qb50::ADCChannel& ADC2CH7;

   extern qb50::ADCChannel& ADC3CH0;
   extern qb50::ADCChannel& ADC3CH1;
   extern qb50::ADCChannel& ADC3CH2;
   extern qb50::ADCChannel& ADC3CH3;
   extern qb50::ADCChannel& ADC3CH4;
   extern qb50::ADCChannel& ADC3CH5;
   extern qb50::ADCChannel& ADC3CH6;
   extern qb50::ADCChannel& ADC3CH7;

   extern qb50::ADCChannel& ADC4CH0;
   extern qb50::ADCChannel& ADC4CH1;
   extern qb50::ADCChannel& ADC4CH2;
   extern qb50::ADCChannel& ADC4CH3;
   extern qb50::ADCChannel& ADC4CH4;
   extern qb50::ADCChannel& ADC4CH5;
   extern qb50::ADCChannel& ADC4CH6;
   extern qb50::ADCChannel& ADC4CH7;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_ADC_CHANNEL_H*/

/*EoF*/
