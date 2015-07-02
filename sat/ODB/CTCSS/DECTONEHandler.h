#ifndef DECTONEHANDLER_H_INCLUDED
#define DECTONEHANDLER_H_INCLUDED

#include "system/qb50.h"
#include <FreeRTOS.h>
#include <semphr.h>


namespace qb50 {

    class DECTONEHandler:public EXTIHandler
    {
        public:

            DECTONEHandler(xSemaphoreHandle &ctcssLock);
            virtual ~DECTONEHandler();

            virtual void handle( EXTI::EXTIn );

        private:

            xSemaphoreHandle &_ctcssLock;

    };

    extern qb50::DECTONEHandler dectone;

}



#endif /* DECTONEHANDLER_H_INCLUDED */
