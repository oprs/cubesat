
#ifndef _QB50_SYS_DEVICE_STM32_TIMER_H
#define _QB50_SYS_DEVICE_STM32_TIMER_H

#include "Device.h"
#include "BusSlave.h"
#include "STM32/STM32_GPIO.h"
#include "STM32/STM32_NVIC.h"

#undef TIM


namespace qb50 {

   class STM32_TIMER : public Device, public BusSlave
   {
      public:

         STM32_TIMER( Bus&              bus,
                      const uint32_t    iobase,
                      const uint32_t    periph,
                      const char       *name,
                      STM32_GPIO::Pin&  pin,
                      STM32_GPIO::Alt   mode
         );

         ~STM32_TIMER();

         STM32_TIMER& init    ( void );
         STM32_TIMER& enable  ( bool silent = false );
         STM32_TIMER& disable ( bool silent = false );


      private:

         STM32_GPIO::Pin& _pin;
         STM32_GPIO::Alt  _alt;

    };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_STM32_TIMER_H*/

/*EoF*/
