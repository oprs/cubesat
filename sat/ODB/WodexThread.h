
#ifndef _QB50_WODEX_THREAD_H
#define _QB50_WODEX_THREAD_H

#include "system/qb50.h"


namespace qb50 {

   class WodexThread : public Thread
   {

      public:

         WodexThread();
         ~WodexThread();

         void run( void );

   };

} /* qb50 */


#endif /*_QB50_WODEX_THREAD_H*/

/*EoF*/
