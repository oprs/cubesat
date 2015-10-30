#ifndef _QB50_SYS_DEVICE_TIMER_H
#define _QB50_SYS_DEVICE_TIMER_H

#include "Device.h"
#include "BusSlave.h"
#include "GPIO.h"
#include "STM32_NVIC.h"

#undef TIM

namespace qb50 {

   class TIMER : public Device, public BusSlave
   {
   public:

      //Constructor
      TIMER(Bus& bus,
         const uint32_t iobase,
         const uint32_t periph,
         const char *name,
         GPIO::Pin& pin,
         GPIO::Alt  mode
      );

      //Destructor
      ~TIMER();

      TIMER& init    ( void );
      TIMER& enable  ( bool silent = false );
      TIMER& disable ( bool silent = false );

   private:

      GPIO::Pin& _pin;
      GPIO::Alt  _alt;
    };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_TIMER_H*/

/*EoF*/
