
#ifndef _QB50_ODB_MODEM_1200_H
#define _QB50_ODB_MODEM_1200_H

#include "Modem.h"
#include "GPIO.h"


namespace qb50 {

   class Modem1200 : public Modem
   {

      public:

         Modem1200( const char *name, GPIO::Pin& enPin, STM32_UART& _uart );
         ~Modem1200();

         Modem1200& init    ( void );
         Modem1200& enable  ( bool silent = false );
         Modem1200& disable ( bool silent = false );

         size_t     send    ( WodStore::WEH *hdr, const uint8_t *x, int toms = -1 );
         size_t     send    ( const uint8_t *x,   unsigned len,     int toms = -1 );


      private:

         GPIO::Pin&  _enPin;
         STM32_UART& _uart;

         uint8_t    *_rxBuf;

         bool        _wrb  ( const uint8_t tx );
         bool        _send ( WodStore::WEH *hdr, const uint8_t *x );
         bool        _send ( const uint8_t *x, size_t len );

   };

   extern qb50::Modem1200 M1K2;

} /* qb50 */


#endif /*_QB50_ODB_MODEM_1200_H*/

/*EoF*/
