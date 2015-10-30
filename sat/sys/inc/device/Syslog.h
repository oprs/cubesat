
#ifndef _QB50_SYS_SYSLOG_H
#define _QB50_SYS_SYSLOG_H

#include "device/UART.h"

#include <iostream>
#include <sstream>
#include <task.h>


#define LOG Syslog::LogLine( SYSLOG ).get()


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
