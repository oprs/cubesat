
#ifndef _QB50_ODB_AX25_TX_H
#define _QB50_ODB_AX25_TX_H

#include "Device.h"
#include "device/STM32/STM32_EXTI.h"


namespace qb50 {

   class AX25TX : public Device, public STM32_EXTIHandler
   {

      public:

         AX25TX( const char *name );
         ~AX25TX();

         AX25TX&  init    ( void );
         AX25TX&  enable  ( bool silent = false );
         AX25TX&  disable ( bool silent = false );

         AX25TX&  mycall  ( const char *x, int ssid );
         AX25TX&  unproto ( const char *x, int ssid );

         AX25TX&  sendUI  ( const uint8_t *x, unsigned len, int toms = -1 );
         AX25TX&  sendUIH ( const uint8_t *x, unsigned len, int toms = -1 );
         uint16_t crc16   ( const uint8_t *x, unsigned len, uint16_t crc = 0xffff );

         void handle( STM32_EXTI::EXTIn );


      private:

         void _push( const uint16_t w, int toms );

         xSemaphoreHandle    _semTX;
         FIFO<uint16_t,1024> _fifo;

         uint8_t _ohdr[ 16 ];

         bool    _flag;
         uint8_t _byte;
         uint8_t _mask;
         uint8_t _ones;
   };

   extern qb50::AX25TX AX25;

} /* qb50 */


#endif /*_QB50_ODB_AX25_TX_H*/

/*EoF*/
