
#ifndef _QB50_SYS_SYSLOG_H
#define _QB50_SYS_SYSLOG_H

#include "device/UART.h"

#include <iostream>
#include <sstream>
#include <task.h>

#include <cstdio>
#include <cstdarg>


#define RED( MSG ) "\033[31;1m" MSG "\033[0m"
#define GREEN( MSG ) "\033[32;1m" MSG "\033[0m"
#define WHITE( MSG ) "\033[1m" MSG "\033[0m"

#define kprintf SYSLOG.printf


namespace qb50 {

   class Syslog : public Device
   {

      protected:

         struct LogLine;

      public:

         Syslog( const char *name, UART& uart );
         virtual ~Syslog();

         Syslog& init    ( void );
         Syslog& enable  ( bool silent = false );
         Syslog& disable ( bool silent = false );

         Syslog& printf  ( const char *fmt, ... );

         void run( void );

      protected:

         struct LogLine
         {
            LogLine();
            ~LogLine();

            char   *_x;
            size_t  _len;
         };

         UART&        _uart;
         xQueueHandle _ioQueue;
         TaskHandle_t _ioTask;

   };

   extern qb50::Syslog SYSLOG;

} /*qb50*/


#endif /*_QB50_SYS_SYSLOG_H*/

/*EoF*/
