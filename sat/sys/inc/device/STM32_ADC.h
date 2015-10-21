
#ifndef _QB50_SYS_DEVICE_STM32_ADC_H
#define _QB50_SYS_DEVICE_STM32_ADC_H

#include "device/ADC.h"
#include "device/BusSlave.h"
#include "device/GPIO.h"

//Over-ride macros defined by CMSIS
#undef ADC

namespace qb50{

   class STM32_ADC : public ADC, public BusSlave
   {

      public:

      /* Channel Definitions for ADC */

         enum ChId {
            CH0  = 0x00, CH1  = 0x01,
            CH2  = 0x02, CH3  = 0x03,
            CH4  = 0x04, CH5  = 0x05,
            CH6  = 0x06, CH7  = 0x07,
            CH8  = 0x08, CH9  = 0x09,
            CH10 = 0x0A, CH11 = 0x0B,
            CH12 = 0x0C, CH13 = 0x0D,
            CH14 = 0x0E, CH15 = 0x0F,
            CH16 = 0x10, CH17 = 0x11,
            CH18 = 0x12,
         };

         #include "_STM32_ADC_Channel.h"

         STM32_ADC( Bus& bus,
                    const uint32_t iobase,
                    const uint32_t periph,
                    const char    *name
         );

         ~STM32_ADC();

         STM32_ADC& init( void );


      protected:

         GPIO::Alt _alt;
         uint8_t   _numConv;

         void _enable  ( IOReq_enable  *req );
         void _disable ( IOReq_disable *req );
       //void _reset   ( IOReq_reset   *req );
         void _read    ( IOReq_read    *req );

   };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_STM32_ADC_H*/

/*EoF*/
