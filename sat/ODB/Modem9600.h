
#ifndef _QB50_ODB_MODEM_9600_H
#define _QB50_ODB_MODEM_9600_H

#include "Modem.h"
#include "device/STM32/STM32_EXTI.h"


namespace qb50 {

   class Modem9600 : public Modem, public STM32_EXTIHandler
   {

      public:

         Modem9600( const char *name );
         ~Modem9600();

         Modem9600&  init    ( void );
         Modem9600&  enable  ( bool silent = false );
         Modem9600&  disable ( bool silent = false );

         size_t      send    ( WodStore::WEH *hdr, const uint8_t *x, int toms = -1 );
         size_t      send    ( const uint8_t *x,   unsigned len,     int toms = -1 );

         Modem9600&  mycall  ( const char *x, int ssid );
         Modem9600&  unproto ( const char *x, int ssid );

/* - */
// XXX privates
         Modem9600&  sendUI  ( const uint8_t *x, unsigned len, int toms = -1 );
         Modem9600&  sendUIH ( const uint8_t *x, unsigned len, int toms = -1 );
/* - */

         void handle( STM32_EXTI::EXTIn );


      private:

         uint16_t _crc16 ( const uint8_t *x, unsigned len, uint16_t crc = 0xffff );
         void     _push  ( const uint16_t w, int toms );

         xSemaphoreHandle    _semTX;
         FIFO<uint16_t,1024> _fifo;

         uint8_t  _ohdr[ 16 ];
         uint8_t *_obuf;

         bool     _flag;
         uint8_t  _byte;
         uint8_t  _mask;
         uint8_t  _ones;
   };

   extern qb50::Modem9600 M9K6;

} /* qb50 */


#endif /*_QB50_ODB_MODEM_9600_H*/

/*EoF*/
