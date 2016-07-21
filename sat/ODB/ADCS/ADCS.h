
#ifndef _QB50_ADCS_H
#define _QB50_ADCS_H

#include "devices.h"


namespace qb50 {

   class ADCS : public Device
   {

      public:

         ADCS( const char *name, STM32_UART& uart, STM32_GPIO::Pin& enPin );
         virtual ~ADCS();

         ADCS& init    ( void );
         ADCS& enable  ( bool silent = false );
         ADCS& disable ( bool silent = false );

         unsigned read  (       uint8_t *x, unsigned len, int toms = 0 );
         unsigned write ( const uint8_t *x, unsigned len, int toms = 0 );

      private:

         STM32_UART&      _uart;
         STM32_GPIO::Pin& _enPin;

   };

   extern qb50::ADCS ADCS0;

} /* qb50 */


#endif /*_QB50_ADCS_H*/

/*EoF*/
