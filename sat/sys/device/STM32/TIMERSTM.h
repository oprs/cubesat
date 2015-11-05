
#ifndef _QB50_SYS_DEVICE_STM32_TIMER_H
#define _QB50_SYS_DEVICE_STM32_TIMER_H

#include "Device.h"
#include "BusSlave.h"
#include "STM32/STM32_GPIO.h"
#include "STM32/STM32_NVIC.h"

#undef TIM


namespace qb50 {

   class TIMER : public Device, public BusSlave
   {
      public:

         TIMER( Bus&              bus,
                const uint32_t    iobase,
                const uint32_t    periph,
                const char       *name,
                STM32_GPIO::Pin&  pin,
                STM32_GPIO::Alt   mode
         );

         ~TIMER();

         TIMER& init    ( void );
         TIMER& enable  ( bool silent = false );
         TIMER& disable ( bool silent = false );


      private:

         STM32_GPIO::Pin& _pin;
         STM32_GPIO::Alt  _alt;

    };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_STM32_TIMER_H*/

/*EoF*/
