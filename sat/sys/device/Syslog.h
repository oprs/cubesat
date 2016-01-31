
#ifndef _QB50_SYS_SYSLOG_H
#define _QB50_SYS_SYSLOG_H

#include "device/UART.h"

#include <iostream>
#include <sstream>
#include <task.h>


#define LOG Syslog::LogLine( SYSLOG ).get()

#define RED( MSG ) "\033[31;1m" MSG "\033[0m"
#define WHITE( MSG ) "\033[1m" MSG "\033[0m"


namespace qb50 {

   class Syslog;

   class Syslog : public Device
   {

      public:

         class LogLine
         {

            public:

               LogLine( Syslog& log );
               virtual ~LogLine();

               std::ostringstream& get( void );

            protected:

               std::ostringstream _os;
               Syslog& _log;

         };

         Syslog( const char *name, UART& uart );
         virtual ~Syslog();

         Syslog& init    ( void );
         Syslog& enable  ( bool silent = false );
         Syslog& disable ( bool silent = false );

         Syslog& write   ( std::string *sp );

         void run( void );

      protected:

         UART&        _uart;
         xQueueHandle _ioQueue;
         TaskHandle_t _ioTask;

   };

   extern qb50::Syslog SYSLOG;

} /*qb50*/


#endif /*_QB50_SYS_SYSLOG_H*/

/*EoF*/
