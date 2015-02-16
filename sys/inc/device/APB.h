
#ifndef _QB50_SYS_BUS_APB_H
#define _QB50_SYS_BUS_APB_H

#include "peripherals/stm32f4xx_rcc.h"
#include "Bus.h"


namespace qb50 {

   class APB : public Bus
   {
      public:

         APB( unsigned APBn );
         ~APB();

         void enable  ( CoreDevice *dev );
         void disable ( CoreDevice *dev );

         unsigned APBn;
   };

   extern qb50::APB APB1;
   extern qb50::APB APB2;

} /* qb50 */


#endif /*_QB50_SYS_BUS_APB_H*/

/*EoF*/
