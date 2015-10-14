
#ifndef _QB50_DECTONE_HANDLER_H
#define _QB50_DECTONE_HANDLER_H

#include <semphr.h>
#undef EXTI

#include "device/EXTI.h"


namespace qb50 {

    class DECTONEHandler : public EXTIHandler
    {
        public:

            DECTONEHandler( xSemaphoreHandle &ctcssLock );
            virtual ~DECTONEHandler();

            virtual void handle( EXTI::EXTIn );

        private:

            xSemaphoreHandle &_ctcssLock;

    };

} /* qb50 */


#endif /* _QB50_DECTONE_HANDLER_H */
