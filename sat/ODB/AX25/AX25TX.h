
#ifndef _QB50_ODB_AX25_TX_H
#define _QB50_ODB_AX25_TX_H

#include "Device.h"
#include "NRZI.h"
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

         AX25TX&  send    ( const uint8_t *x, unsigned len, int toms = -1 );
         uint16_t crc16   ( const uint8_t *x, unsigned len );

         void handle( STM32_EXTI::EXTIn );

         void test( const bool *v, unsigned len );

      private:

         xSemaphoreHandle    _semTX;
         FIFO<uint16_t,1024> _fifo;

         NRZI _nrzi;

   };

   extern qb50::AX25TX AX25;

} /* qb50 */


#endif /*_QB50_ODB_AX25_TX_H*/

/*EoF*/
