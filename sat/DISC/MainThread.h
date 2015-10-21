
#ifndef _QB50_DISC_MAIN_THREAD_H
#define _QB50_DISC_MAIN_THREAD_H

#include "system/qb50.h"


namespace qb50 {

   class MainThread : public Thread
   {

      public:

         MainThread();
         ~MainThread();

         void run( void );

      private:

         void initDevices( void );

   };

} /* qb50 */


#endif /*_QB50_DISC_MAIN_THREAD_H*/

/*EoF*/
