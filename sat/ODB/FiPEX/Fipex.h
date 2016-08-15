
#ifndef _QB50_FIPEX_H
#define _QB50_FIPEX_H

#include "devices.h"
#include "Exception.h"


namespace qb50 {

   class Fipex : public Device
   {

      public:

         #include "Script.h"

         Fipex( const char *name, STM32_UART& uart, STM32_GPIO::Pin& enPin );
         virtual ~Fipex();

         Fipex& init    ( void );
         Fipex& enable  ( bool silent = false );
         Fipex& disable ( bool silent = false );

         Fipex& activeScript ( unsigned sn );
         Fipex& storeScript  ( unsigned sn, Script::ScriptHeader *sh );

         Script::ScriptHeader *loadScript( unsigned sn );

         Fipex& runCommand   ( Script::CmdHeader *ch, Script::RspHeader *rh );
         Fipex& abort        ( void );

         unsigned activeScript ( void ) const
         { return _sn; }


      private:

         STM32_UART&      _uart;
         STM32_GPIO::Pin& _enPin;

         uint8_t *_st;  // scripts table
         uint8_t *_sc;  // active script data
         unsigned _sn;  // acrive script number

         bool _send( Script::CmdHeader *ch, Script::RspHeader *rh, int toms );
         bool _recv(                        Script::RspHeader *rh, int toms );

   };

   extern qb50::Fipex FPX;

} /* qb50 */


#endif /*_QB50_FIPEX_H*/

/*EoF*/
