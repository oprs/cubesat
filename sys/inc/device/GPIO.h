
#ifndef _QB50_SYS_GPIO_H
#define _QB50_SYS_GPIO_H

#include "stm32f4xx_gpio.h"
#include "CoreDevice.h"
#include "GPIOPin.h"


namespace qb50 {

   class GPIO : public CoreDevice
   {
      public:

         GPIO( Bus& bus, const uint32_t periph, const uint32_t iobase, GPIOPin *pin );
         ~GPIO();

         void reset    ( void );
         void enable   ( void );
         void disable  ( void );

         GPIOPin *pin;
   };

   /* CMSIS keeps polluting the whole namespace with
      hundreds of macros, we need to clear those off. */

   #undef GPIOA
   #undef GPIOB
   #undef GPIOC
   #undef GPIOD
   #undef GPIOE

   extern qb50::GPIO GPIOA;
   extern qb50::GPIO GPIOB;
   extern qb50::GPIO GPIOC;
   extern qb50::GPIO GPIOD;
   extern qb50::GPIO GPIOE;

} /* qb50 */


#endif /*_QB50_SYS_GPIO_H*/

/*EoF*/
