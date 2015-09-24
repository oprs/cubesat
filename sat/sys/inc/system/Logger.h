
#ifndef _QB50_SYS_SYSTEM_UART_H
#define _QB50_SYS_SYSTEM_UART_H

#include <iostream>
#include <sstream>


#define LOG Logger().get()


namespace qb50 {

   class Logger : public std::ostream
   {

      public:

         Logger();
         virtual ~Logger();

         std::ostringstream& get( void );


      protected:

         std::ostringstream _os;

   };

}


#endif /*_QB50_SYS_SYSTEM_UART_H*/

/*EoF*/
