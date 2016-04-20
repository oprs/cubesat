
#ifndef _QB50_T9600_THREAD_H
#define _QB50_T9600_THREAD_H

#include "system/qb50.h"


namespace qb50 {

   class T9600Thread : public Thread
   {

      public:

         T9600Thread();
         ~T9600Thread();

         void run       ( void );
         void onSuspend ( void );
         void onResume  ( void );

      private:

         uint8_t *_x;

   };

} /* qb50 */


#endif /*_QB50_T9600_THREAD_H*/

/*EoF*/
