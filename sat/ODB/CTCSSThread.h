
#ifndef _QB50_CTCSS_THREAD_H
#define _QB50_CTCSS_THREAD_H

#include "system/qb50.h"


namespace qb50 {

   class CTCSSThread : public Thread
   {

      public:

         CTCSSThread();
         ~CTCSSThread();

         void run( void );

   };

} /* qb50 */


#endif /*_QB50_CTCSS_THREAD_H*/

/*EoF*/
