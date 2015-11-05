
#include "device/Syslog.h"
#include "system/Application.h"

#include <cstdio>
#include <cstring>

using namespace qb50;


static void _trampoline( void *x );


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Syslog::Syslog( const char *name, UART& uart )
   : Device( name ), _uart( uart )
{
   _ioQueue = xQueueCreate( 64, sizeof( std::string* ));
}


Syslog::~Syslog()
{
   vQueueDelete( _ioQueue );
}


Syslog::LogLine::LogLine( Syslog& log ) : _log( log )
{ ; }


Syslog::LogLine::~LogLine()
{
   _os << "\r\n" << std::flush;
   (void)_log.write( new std::string( _os.str() ));
}

//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

Syslog& Syslog::init( void )
{
   (void)xTaskCreate( _trampoline, _name, 128, this, 1, &_ioTask );
   return *this;
}


std::ostringstream& Syslog::LogLine::get( void )
{
   unsigned ts = ticks();
   char x[16];

   /*
    * I considered using stream manipulators here (std::setw(), etc...)
    * but the resulting code turned out to be clumsy and slow.
    * Let's just stick with snprintf() and stdio.
    */

   (void)snprintf( x, sizeof( x ), "[% 9.3f] ", (float)ts / configTICK_RATE_HZ );
   _os << x;

   return _os;
}


Syslog& Syslog::write( std::string *sp )
{
   (void)xQueueSend( _ioQueue, &sp, 0 );
   return *this;
}


Syslog& Syslog::enable( bool silent )
{
   _uart.enable( silent );
   return *this;
}


Syslog& Syslog::disable( bool silent )
{
   (void)silent;
   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

static void _trampoline( void *x )
{
   Syslog *self = (Syslog*)x;
   self->run();
   vTaskDelete( NULL );
}


void Syslog::run( void )
{
   std::string *sp;

   for( ;; ) {
    if( xQueueReceive( _ioQueue, &sp, portMAX_DELAY ) != pdPASS )
         continue;

    //_lock();
      (void)_uart.write( sp->data(), sp->size() );
      delete sp;
    //_unlock();
   }

}

/*EoF*/
