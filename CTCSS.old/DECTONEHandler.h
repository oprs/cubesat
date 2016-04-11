
#ifndef _QB50_DECTONE_HANDLER_H
#define _QB50_DECTONE_HANDLER_H

#include <semphr.h>
#undef EXTI

#include "STM32/STM32_EXTI.h"


namespace qb50 {

    class DECTONEHandler : public STM32_EXTIHandler
    {
        public:

            DECTONEHandler( xSemaphoreHandle &ctcssLock );
            virtual ~DECTONEHandler();

            virtual void handle( STM32_EXTI::EXTIn );

        private:

            xSemaphoreHandle &_ctcssLock;

    };

} /* qb50 */


#endif /* _QB50_DECTONE_HANDLER_H */
