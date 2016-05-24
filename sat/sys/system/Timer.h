
#ifndef _QB50_SYSTEM_TIMER_H
#define _QB50_SYSTEM_TIMER_H

#include <FreeRTOS.h>
#include <task.h>


namespace qb50 {

   class Timer
   {

      public:

         Timer();
         virtual ~Timer();

         Timer& every( unsigned ms );


      protected:

         TickType_t _incr;
         TickType_t _prev;

   };

} /* qb50 */


#endif /*_QB50_SYSTEM_TIMER_H*/

/*EoF*/
