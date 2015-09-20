
#ifndef _QB50_SYS_SYSTEM_UART_H
#define _QB50_SYS_SYSTEM_UART_H

#include <iostream>
#include <sstream>

#include "system/UserLock.h"


namespace qb50 {

   class Logger : public std::ostream
   {

      public:

         Logger();
         virtual ~Logger();

      private:

         class LogBuf : public std::stringbuf
         {

            public:

               LogBuf( std::ostream& os );
               virtual ~LogBuf();

               virtual int sync( void );


            protected:

               std::ostream& _os;
               UserLock _lock;

         };

   };

   extern qb50::Logger LOG;

}


#endif /*_QB50_SYS_SYSTEM_UART_H*/

/*EoF*/
