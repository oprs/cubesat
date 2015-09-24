
#include "device/UART.h"
#include "system/Logger.h"
#include "system/Application.h"

#include <cstdio>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Logger::Logger()
{ ; }


Logger::~Logger()
{
   _os << "\r\n" << std::flush;

   std::string s = _os.str();
   UART6.write( s.data(), s.size() );
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

std::ostringstream& Logger::get( void )
{
   unsigned ts = ticks();
   char x[16];

   /*
    * I considered using stream manipulators here (std::setw(), etc...)
    * but the resulting code turned out to be clumsy and slow.
    * Let's just stick with snprintf() and stdio.
    */
   (void)snprintf( x, sizeof( x ), "[% 9.3f] ", (float)ts / 1000 );
   _os << x;

   return _os;
}


/*EoF*/
