
#include "device/Syslog.h"
#include "system/Application.h"

using namespace qb50;


static void _trampoline( void *x );


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Syslog::Syslog( const char *name, UART& uart )
   : Device( name ), _uart( uart )
{
   _ioQueue = xQueueCreate( 64, sizeof( LogLine* ));
}


Syslog::~Syslog()
{
   vQueueDelete( _ioQueue );
}


Syslog::LogLine::LogLine()
{
   _x   = new char[ 128 ];
   _len = 0;
}


Syslog::LogLine::~LogLine()
{
   delete[] _x;
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

Syslog& Syslog::init( void )
{
   (void)xTaskCreate( _trampoline, _name, /*128*/ 512, this, 1, &_ioTask );
   return *this;
}


Syslog& Syslog::printf( const char *fmt, ... )
{
   unsigned ts = ticks();

   va_list ap;
   va_start( ap, fmt );

   do {
      LogLine *line = new LogLine();
      int n;

      n = snprintf( line->_x, 13, "[% 9.3f] ", (float)ts / configTICK_RATE_HZ );
      if( n <= 0 ) { delete line; break; }

      line->_len += n;

      n = vsnprintf( line->_x + n, 128 - n - 1, fmt, ap );
      if( n <= 0 ) { delete line; break; }

      line->_len += n;
      (void)xQueueSend( _ioQueue, &line, 0 );

   } while( 0 );

   va_end( ap );

   return *this;
}


Syslog& Syslog::enable( bool silent )
{
   //_uart.enable( silent ).baudRate( 115200 );
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
   LogLine *line;

   for( ;; ) {
      if( xQueueReceive( _ioQueue, &line, portMAX_DELAY ) != pdPASS ) {
         continue;
      }

      (void)_uart.write( line->_x, line->_len );
      delete line;
   }
}

/*EoF*/
