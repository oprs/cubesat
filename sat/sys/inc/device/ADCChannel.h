
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

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_ADC_CHANNEL_H*/

/*EoF*/
