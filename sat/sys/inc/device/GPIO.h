
#ifndef _QB50_SYS_GPIO_H
#define _QB50_SYS_GPIO_H

#include "BusDevice.h"
#include "GPIOPin.h"
#include "Bus.h"


namespace qb50 {

   class GPIO : public BusDevice
   {
      public:

         GPIO( Bus& bus, const uint32_t iobase, const uint32_t periph, GPIOPin *pin );
         ~GPIO();

         GPIO& enable  ( void );
         GPIO& disable ( void );

         GPIOPin *pin;
   };

   extern qb50::GPIO GPIOA;
   extern qb50::GPIO GPIOB;
   extern qb50::GPIO GPIOC;
   extern qb50::GPIO GPIOD;
   extern qb50::GPIO GPIOE;

} /* qb50 */


#endif /*_QB50_SYS_GPIO_H*/

/*EoF*/
