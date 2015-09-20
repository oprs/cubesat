
#include "system/Logger.h"
#include "system/Application.h"

#include <iostream>
#include <cstdio>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Logger::Logger()
	: std::ostream( new LogBuf( std::cout ))
{ ; }


Logger::~Logger()
{ ; }


Logger::LogBuf::LogBuf( std::ostream& os )
   : _os( os )
{ ; }


Logger::LogBuf::~LogBuf()
{ pubsync(); }

//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

int Logger::LogBuf::sync( void )
{
   char x[16];
   unsigned ts = ticks();

   _lock.P();

   (void)snprintf( x, sizeof( x ), "% 9.3f", (float)ts / 1000 );
   _os << '[' << x << "] " << str() << "\r\n";
   str( "" );

   _lock.V();

   return 0;
}

/*EoF*/
