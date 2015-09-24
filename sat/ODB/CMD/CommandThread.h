
#ifndef _QB50_COMMAND_THREAD_H
#define _QB50_COMMAND_THREAD_H

#include "system/qb50.h"


namespace qb50 {

   class CommandThread : public Thread
   {

      public:

         CommandThread();
         ~CommandThread();

         void run( void );

   };

} /* qb50 */


#endif /*_QB50_COMMAND_THREAD_H*/

/*EoF*/
