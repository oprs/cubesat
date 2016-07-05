
#include "Config.h"
#include "Fipex.h"

#include <safe_stm32f4xx.h>
#include <cstring>


using namespace qb50;


Fipex qb50::FPX( "FPX", UART2, PB14 );

static FormatException ScriptFormatException;


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


Fipex& Fipex::storeScript( unsigned sn, const uint8_t *x, unsigned len )
{
   Fipex::Script sc;

   hexdump( x, len );

   try {
      sc.load( x, len );
      uint8_t *base = _st + sn * 256;
      (void)memcpy( base, x, len );
      kprintf( GREEN( "%s: storing script #%lu" ) "\r\n", _name, sn );
   } catch( FipexException& e ) {
      kprintf( RED( "%s: %s" ) "\r\n", _name, e.what() );
   }

   return *this;
}


Fipex& Fipex::op_SU_ON( void )
{
   enable();
   return *this;
}


Fipex& Fipex::op_SU_OFF( void )
{
   disable();
   return *this;
}


Fipex& Fipex::op_SU_END( void )
{
   disable();
   return *this;
}


Fipex& Fipex::op_CMD( void )
{
   return *this;
}


/*EoF*/
