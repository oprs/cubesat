
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
   _rxBuf = new uint8_t[ 64 ];
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
   size_t n;

   if( _incRef() > 0 )
      return *this;

   BB.enable( Baseband::P0, silent );
   delay( 6500 );
   Baseband::Power p = (Baseband::Power)CONF.getParam( Config::PARAM_WODEX_POWER );
   BB.power( p );
   delay( 500 );
   _uart.enable();
   _enPin.on();

   n = _uart.readLine( _rxBuf, 63, 500 );
   while( n > 0 ) {
      _rxBuf[ n ] = 0;
      kprintf( RED( "%s: [modem] %s" ) "\r\n", _name, (const char*)_rxBuf );
      n = _uart.readLine( _rxBuf, 63, 500 );
   }

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

   _enPin.off();
   _uart.disable();
   BB.disable( silent );

   if( !silent ) {
      kprintf( "%s: disabled\r\n", _name );
   }

   return *this;
}


struct DataTrackCmd {
   const char *name;
   const char *cmd;
   size_t      len;
};

Modem1200& Modem1200::configure( void )
{
   size_t n;
   int i;

   struct DataTrackCmd cv[ 5 ] = {
      { "TOCALL",  "TLM\r",    4 },
      { "MYCALL",  "XXXXXX\r", 7 },
      { "1st VIA", "\r",       1 },
      { "TXDELAY", "1000\r",   5 },
      { "ECHO",    "Y\r",      2 }
   };

   cv[1].cmd = ( SAT.id() == ODB::FR01 ) ? "ON0FR1\r\n" : "ON0FR5\r\n";

   kprintf( YELLOW( "%s: reconfiguring PIC " ) "\r\n", _name );

   _enPin.off();
   delay( 100 );

   _uart.enable();
   _enPin.on();
   delay( 1000 );

   for( i = 0 ; i < 5 ; ++i ) {
      n = _uart.readLine( _rxBuf, 63, 500 );
      while( n > 0 ) {
         _rxBuf[ n ] = 0;
         kprintf( "%s: [modem] %s\r\n", _name, (const char*)_rxBuf );
         n = _uart.readLine( _rxBuf, 63, 500 );
      }

      if( _uart.write( (const uint8_t*)cv[i].cmd, cv[i].len, 250  ) != cv[i].len ) {
         kprintf( RED( "%s: can't write to %s" ) "\r\n", _name, _uart.name() );
         break;
      }

      delay( 250 );
   }

   n = _uart.readLine( _rxBuf, 63, 1000 );
   while( n > 0 ) {
      _rxBuf[ n ] = 0;
      kprintf( "%s: [modem] %s\r\n", _name, (const char*)_rxBuf );
      n = _uart.readLine( _rxBuf, 63, 500 );
   }

   kprintf( "%s: configuration set, hoping for the best...\r\n", _name );

   _enPin.off();
   _uart.disable();

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

   unsigned len = 0;
   unsigned err, ms, i, n;

   (void)gmtime_r( (const time_t*)&hdr->time, &stm );
   n  = snprintf ( stime,     32,     "!%02x", CONF.nrst() & 0xff );
   n += strftime ( stime + n, 32 - n, "%y%m%d@%H%M%S;", &stm );

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
/*
   _wrb( 0x0a );
*/

   ms = ( 1000 * ( n + len )) / 75;
 //ms = 500;
   kprintf( YELLOW( "%s: delay: %ums" ) "\r\n", _name, ms );
   delay( ms );

   return( err < MAXERR );
}


bool Modem1200::_send( const uint8_t *x, size_t len )
{
   unsigned err = 0;
   unsigned ms;

   for( size_t i = 0 ; i < len ; ++i ) {
      if( !_wrb( x[ i ] )) {
         ++err;
         if( err == MAXERR ) break;
      }
   }

   _wrb( 0x0d );
//   _wrb( 0x0a );

   ms = ( 1000 * len ) / 100;
 //ms = 500;
   kprintf( YELLOW( "%s: delay: %ums" ) "\r\n", _name, ms );
   delay( ms );

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
