
#ifndef _QB50_SYS_BUS_AHB_H
#define _QB50_SYS_BUS_AHB_H

#include "Bus.h"
#include "BusDevice.h"


namespace qb50 {

   class AHB : public Bus
   {
      public:

         AHB( uint32_t AHBn );
         ~AHB();

         void enable  ( BusDevice *dev );
         void disable ( BusDevice *dev );

      private:

         uint32_t _AHBn;
   };

   extern qb50::AHB AHB1;
   extern qb50::AHB AHB2;
   extern qb50::AHB AHB3;

} /* qb50 */


#endif /*_QB50_SYS_BUS_AHB_H*/

/*EoF*/
