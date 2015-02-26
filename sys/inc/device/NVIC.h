
#ifndef _QB50_SYS_DEVICE_NVIC_H
#define _QB50_SYS_DEVICE_NVIC_H

#include <stdint.h>


namespace qb50 {

   class NVIC
   {
      public:

         NVIC();
         ~NVIC();

         enum Priority {
            IPR0 = 0, IPR1,  IPR2,  IPR3,
            IPR4,     IPR5,  IPR6,  IPR7,
            IPR8,     IPR9,  IPR10, IPR11,
            IPR12,    IPR13, IPR14, IPR15,
         };

         void enable  ( uint32_t IRQn, Priority sel = IPR15 );
         void disable ( uint32_t IRQn );
   };

   extern qb50::NVIC IRQ;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_NVIC_H*/

/*EoF*/
