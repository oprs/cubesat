
#include "devices.h"
#include "Modem1200.h"
#include "Baseband.h"
#include "Config.h"

#include <ctime>


using namespace qb50;


Modem1200 qb50::M1K2( "M1K2", PC3, UART3 ); // global Modem1200 object


static const uint8_t _istr[ 4 ] = { 0x0d, 0x0a, 0x0d, 0x0a };

static const uint8_t _hexv[ 16 ] = {
   '0', '1', '2', '3', '4', '5', '6', '7',
   '8' ,'9', 'a', 'b', 'c', 'd', 'e', 'f'
};


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Modem1200::Modem1200( const char *name, GPIO::Pin& enPin, STM32_UART& uart )
   : Modem( name ), _enPin( enPin ), _uart( uart )
{
   _rxBuf = new uint8_t[ 16 ];
}


Modem1200::~Modem1200()
{
   delete[] _rxBuf;
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

Modem1200& Modem1200::init( void )
{
   kprintf( "%s: AMSAT-F Modem1200 Interface, enPin: %s\r\n",
            _name, _enPin.name() );

   _enPin.out().off();

   return *this;
}


Modem1200& Modem1200::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   BB.enable( Baseband::P0, silent );
   delay( 6500 );
   Baseband::Power p = (Baseband::Power)CONF.getParam( Config::PARAM_WODEX_POWER );
   BB.power( p );
   delay( 500 );
   _uart.enable();
   _enPin.on();

   delay( 100 );

/*
   _uart.write( _istr, sizeof( _istr ));
   n = _uart.read( _rxBuf, 16, 100 );

   kprintf( "%s: read %d bytes\r\n", _name, n );
   hexdump( _rxBuf, 16 );
*/

   if( !silent ) {
      kprintf( "%s: enabled\r\n", _name );
   }

   return *this;
}


Modem1200& Modem1200::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

delay( 2000 );
   _enPin.off();
   _uart.disable();
   BB.disable( silent );

   if( !silent ) {
      kprintf( "%s: disabled\r\n", _name );
   }

   return *this;
}


#define MAXERR 3
#define MAXTRY 3

size_t Modem1200::send( WodStore::WEH *hdr, const uint8_t *x, int toms )
{
   int n;

   (void)toms;

   for( n = 0 ; n < MAXTRY ; ++n ) {
      if( _send( hdr, x ))
         break;

      _wrb( 0x0d );
   }

   if( n == MAXTRY ) {
      kprintf( RED( "%s: giving up after %d tries" ) "\r\n", _name, n );
   }

   return 0;
}


size_t Modem1200::send( const uint8_t *x, size_t len, int toms )
{
   int n;

   (void)toms;

   for( n = 0 ; n < MAXTRY ; ++n ) {
      if( _send( x, len ))
         break;

      _wrb( 0x0d );
   }

   return 0;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

bool Modem1200::_send( WodStore::WEH *hdr, const uint8_t *x )
{
   char stime[ 32 ];
   struct tm stm;

   unsigned len, err, i, n;

   (void)gmtime_r( (const time_t*)&hdr->time, &stm );
   n = strftime( stime, 32, "!%Y%m%d@%H%M%S;", &stm );

   err = 0;

   for( i = 0 ; i < n ; ++i ) {
      if( !_wrb( stime[ i ] )) {
         ++err;
         if( err == MAXERR ) break;
      }
   }

   if( err < MAXERR ) {
      len = hdr->len - sizeof( WodStore::WEH );
      for( i = 0 ; i < len ; ++i ) {
         if( !_wrb( _hexv[ x[ i ] >> 4 ] )) {
            ++err;
            if( err == MAXERR ) break;
         }

         if( !_wrb( _hexv[ x[ i ]  & 0x0f ] )) {
            ++err;
            if( err == MAXERR ) break;
         }
      }
   }

   _wrb( 0x0d );
   _wrb( 0x0d );
   _wrb( 0x0d );
   _wrb( 0x0a );

   return( err < MAXERR );
}


bool Modem1200::_send( const uint8_t *x, size_t len )
{
   unsigned err = 0;

   for( size_t i = 0 ; i < len ; ++i ) {
      if( !_wrb( x[ i ] )) {
         ++err;
         if( err == MAXERR ) break;
      }
   }

   return( err < MAXERR );
}


bool Modem1200::_wrb( const uint8_t tx )
{
   uint8_t rx;
   int i;

   for( i = 0 ; i < 5 ; ++i ) {
      if( tx == 0x0a ) {
         /* 0x0a is not echoed back by the PIC, disable read-back */
         if( _uart.write( tx, 25 ) > 0 ) {
            break;
         }
      } else {
         if( _uart.write( tx, rx, 25 ) > 0 ) {
            break;
         }
      }
   }

   if( i == 5 ) {
      kprintf( RED( "%s: byte lost: 0x%02x" ) "\r\n", _name, tx );
      return false;
   }

   return true;
}


/*EoF*/
