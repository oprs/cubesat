
#include "Config.h"
#include "ADCS.h"


using namespace qb50;


ADCS qb50::ADCS0( "ADCS0", UART1, PC13 );


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

ADCS::ADCS( const char *name, STM32_UART& uart, STM32_GPIO::Pin& enPin )
   : Device( name ), _uart( uart ), _enPin( enPin )
{ ; }


ADCS::~ADCS()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

ADCS& ADCS::init()
{
   _enPin.out().off();

   kprintf( "%s: Attitude Determination & Control System on %s, enPin: %s\r\n", _name, _uart.name(), _enPin.name() );

   return *this;
}


ADCS& ADCS::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   _uart.enable( silent );
   _enPin.on();

   if( !silent ) {
      kprintf( "%s: enabled\r\n", _name );
   }

   return *this;
}


ADCS& ADCS::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   _enPin.off();
   _uart.disable( silent );

   if( !silent ) {
      kprintf( "%s: disabled\r\n", _name );
   }

   return *this;
}


unsigned ADCS::read( uint8_t *x, unsigned len, int toms )
{
   return
      _uart.read( x, len, toms );
}


unsigned ADCS::write( const uint8_t *x, unsigned len, int toms )
{
   return
      _uart.write( x, len, toms );
}

/*EoF*/
