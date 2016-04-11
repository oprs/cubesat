
#ifndef _QB50_CTCSS_THREAD_H
#define _QB50_CTCSS_THREAD_H

#include "system/qb50.h"
#include "device/STM32/STM32_EXTI.h"

namespace qb50 {

   class CTCSSThread : public Thread, public STM32_EXTIHandler
   {

      public:

         CTCSSThread();
         ~CTCSSThread();

         void handle    ( STM32_EXTI::EXTIn );

         void onSuspend ( void );
         void onResume  ( void );
         void run       ( void );


      private:

         xSemaphoreHandle _semCTCSS;

   };

} /* qb50 */


#endif /*_QB50_CTCSS_THREAD_H*/

/*EoF*/
