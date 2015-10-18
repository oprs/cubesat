#ifndef _QB50_SYS_DEVICE_TIMER_H
#define _QB50_SYS_DEVICE_TIMER_H

#include "Device.h"
#include "BusSlave.h"
#include "GPIOPin.h"
#include "NVIC.h"

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
         GPIOPin& pin,
         GPIOPin::Alt mode
      );

      //Destructor
      ~TIMER();

      TIMER& init    ( void );
      TIMER& enable  ( bool silent = false );
      TIMER& disable ( bool silent = false );

   private:

      GPIOPin&     _pin;
      GPIOPin::Alt _alt;
    };

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_TIMER_H*/

/*EoF*/
