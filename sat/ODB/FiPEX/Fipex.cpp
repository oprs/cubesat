
#include "Config.h"
#include "Fipex.h"

#include <safe_stm32f4xx.h>
#include <cstring>


using namespace qb50;


Fipex qb50::FPX( "FPX", UART2, PB14 );

static FormatException ScriptFormatException;


static uint8_t cmd_rsp[ 4 ] = { 0x7e, 0x10, 0x00, 0x10 };


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Fipex::Fipex( const char *name, STM32_UART& uart, STM32_GPIO::Pin& enPin )
   : Device( name ), _uart( uart ), _enPin( enPin )
{
   _st = (uint8_t*)BKPSRAM_BASE + 2048; // XXX avoid magic numbers
   _sc = _st;
   _sn = 0;
}


Fipex::~Fipex()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

Fipex& Fipex::init()
{
   Config::pval_t sn;

   _enPin.out().on();

   kprintf( "%s: FIPEX Probe on %s, enPin: %s\r\n", _name, _uart.name(), _enPin.name() );

   sn = CONF.getParam( Config::PARAM_FIPEX_SCRIPT_N );
   (void)activeScript( sn );

   return *this;
}


Fipex& Fipex::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   _enPin.on();

   // Req: FPX-SW-0240 - "The OBC shall wait 500ms before initializing the UART interface [...]"

   delay( 500 );
   _uart.enable( silent );

   if( !silent ) {
      kprintf( "%s: enabled\r\n", _name );
   }

   return *this;
}


Fipex& Fipex::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   _uart.disable( silent );
   _enPin.off();

   if( !silent ) {
      kprintf( "%s: disabled\r\n", _name );
   }

   return *this;
}


Fipex& Fipex::activeScript( unsigned sn )
{
   kprintf( "%s: script #%lu active\r\n", _name, sn );

   _sn = sn;
   _sc = _st + _sn * 256;

   return *this;
}


Fipex& Fipex::storeScript( unsigned sn, Fipex::Script::ScriptHeader *sh )
{
   Fipex::Script sc;

   if( sn > 7 ) {

      kprintf( RED( "%s: invalid script number #%lu" ) "\r\n", _name, sn );

   } else {

      hexdump( sh, sh->len + 1 );

      try {
         sc.load( sh );
         uint8_t *base = _st + sn * 256;
         (void)memcpy( base, sh, sh->len + 1 );
         kprintf( GREEN( "%s: storing script #%lu" ) "\r\n", _name, sn );
      } catch( FipexException& e ) {
         kprintf( RED( "%s: %s" ) "\r\n", _name, e.what() );
      }

   }

   return *this;
}


Fipex& Fipex::runCommand( Script::CmdHeader *ch, Script::RspHeader *rh )
{
   switch( ch->id ) {

      case Script::OBC_SU_ON:
         enable();
         // XXX set state
         break;

      case Script::OBC_SU_OFF:
         disable();
         // XXX set state
         break;

      case Script::OBC_SU_END:
         disable();
         // XXX set state
         break;

      case Script::SU_PING:
      case Script::SU_INIT:
      case Script::SU_ID:
      case Script::SU_STDBY:
      case Script::SU_SC:
      case Script::SU_SM:
      case Script::SU_RSP:
      case Script::SU_SP:
      case Script::SU_HK:
      case Script::SU_DP:
      case Script::SU_CAL:

         if( !_send( ch, rh, 500 )) {
            kprintf( RED( "%s: _send() failed, retrying with SU_RSP" ) "\r\n", _name );
            if( !_send( (Script::CmdHeader*)cmd_rsp, rh, 500 )) {
               kprintf( RED( "%s: _send() failed again, aborting" ) "\r\n", _name );
               // XXX switch to ERROR state
               break;
            }
         }

         // XXX set state
         break;
   }

   return *this;
}


Fipex& Fipex::abort( void )
{
   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

bool Fipex::_send( Script::CmdHeader *ch, Script::RspHeader *rh, int toms )
{
   size_t n = _uart.write( (const uint8_t*)ch, ch->len + 4U, toms );

hexdump( (const uint8_t*)ch, ch->len + 4U );

   if( n != ( ch->len + 4U )) {
      kprintf( RED( "%s: timeout in _send()" ) "\r\n", _name );
      return false;
   }

   return
      _recv( rh, toms );
}


bool Fipex::_recv( Script::RspHeader *rh, int toms )
{
   (void)memset( rh, 0, 205 );

   size_t n = _uart.read( (uint8_t*)rh, 205, toms );

   if( n != 205 ) {
      kprintf( RED( "%s: timeout in _recv()" ) "\r\n", _name );
      return false;
   }

   if( rh->sb != 0x7e ) {
      kprintf( RED( "%s: start byte not found in SU response" ) "\r\n", _name );
      return false;
   }

   uint8_t sum = rh->id ^ rh->len ^ rh->seq;
   for( size_t i = 0 ; i < rh->len ; ++i )
      sum ^= rh->x[i];

   const uint8_t *x = (const uint8_t *)rh;
   if( sum != x[ rh->len + 4U ] ) {
      kprintf( RED( "%s: checksum mismatch in SU response" ) "\r\n", _name );
      return false;
   }

   return true;
}


/*EoF*/
