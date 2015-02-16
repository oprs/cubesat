
#ifndef _QB50_SYS_BUS_AHB_H
#define _QB50_SYS_BUS_AHB_H

#include "peripherals/stm32f4xx_rcc.h"
#include "Bus.h"


namespace qb50 {

   class AHB : public Bus
   {
      public:

         AHB( unsigned AHBn );
         ~AHB();

         void enable  ( CoreDevice *dev );
         void disable ( CoreDevice *dev );

         unsigned AHBn;
   };

   extern qb50::AHB AHB1;
   extern qb50::AHB AHB2;
   extern qb50::AHB AHB3;

} /* qb50 */


#endif /*_QB50_SYS_BUS_AHB_H*/

/*EoF*/
