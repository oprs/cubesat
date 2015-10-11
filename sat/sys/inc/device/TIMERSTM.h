#ifndef _QB50_SYS_DEVICE_TIMER_H
#define _QB50_SYS_DEVICE_TIMER_H

#include "BusDevice.h"
#include "GPIOPin.h"
#include "NVIC.h"

#undef TIM

namespace qb50{

   class TIMER : public BusDevice
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

   extern qb50::TIMER TIMER1;
   extern qb50::TIMER TIMER2;
   extern qb50::TIMER TIMER8;
}

#endif
/* TIMER_H_INCLUDED */

