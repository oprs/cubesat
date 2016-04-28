
#ifndef _QB50_T1200_THREAD_H
#define _QB50_T1200_THREAD_H

#include "system/qb50.h"


namespace qb50 {

   class T1200Thread : public Thread
   {

      public:

         T1200Thread();
         ~T1200Thread();

         void run       ( void );
         void onSuspend ( void );
         void onResume  ( void );

      private:

         void _wrb( const uint8_t tx );

   };

} /* qb50 */


#endif /*_QB50_T1200_THREAD_H*/

/*EoF*/
