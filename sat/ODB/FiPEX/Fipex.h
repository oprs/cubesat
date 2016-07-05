
#ifndef _QB50_FIPEX_H
#define _QB50_FIPEX_H

#include "devices.h"
#include "Exception.h"


namespace qb50 {

   class Fipex : public Device
   {

      public:

         enum ScriptCmd
         {
            SU_PING    = 0x00,
            SU_INIT    = 0x01,
            SU_ID      = 0x04,
            SU_STDBY   = 0x0a,
            SU_SC      = 0x0b,
            SU_SM      = 0x0c,
            OBC_SU_ON  = 0x0f,
            SU_RSP     = 0x10,
            SU_SP      = 0x11,
            SU_HK      = 0x20,
            SU_DP      = 0x21,
            SU_CAL     = 0x33,
            OBC_SU_OFF = 0xf0,
            OBC_SU_END = 0xff
         };

#if 0
         struct CmdHeader
         {
            uint8_t  sb;    // start byte
            uint8_t  id;    // command ID
            uint8_t  len;   // len
            uint8_t  x[];   // data
         } __attribute__(( packed ));

         struct ScriptHeader
         {
            uint8_t  len;   // script length
            uint32_t stime; // start time
            uint16_t rtime; // repeat time
            uint8_t  cnt;   // command count
         } __attribute__(( packed ));
#endif

         #include "Script.h"

         Fipex( const char *name, STM32_UART& uart, STM32_GPIO::Pin& enPin );
         virtual ~Fipex();

         Fipex& init    ( void );
         Fipex& enable  ( bool silent = false );
         Fipex& disable ( bool silent = false );

         Fipex& activeScript ( unsigned sn );
         Fipex& storeScript  ( unsigned sn, const uint8_t *x, unsigned len );

         Fipex& op_SU_ON  ( void );
         Fipex& op_SU_OFF ( void );
         Fipex& op_SU_END ( void );
         Fipex& op_CMD    ( void );

         unsigned activeScript ( void ) const
         { return _sn; }


      private:

         STM32_UART&      _uart;
         STM32_GPIO::Pin& _enPin;

         uint8_t *_st;  // scripts table
         uint8_t *_sc;  // active script data
         unsigned _sn;  // acrive script number

   };

   extern qb50::Fipex FPX;

} /* qb50 */


#endif /*_QB50_FIPEX_H*/

/*EoF*/
