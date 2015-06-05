#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED


#include <FreeRTOS.h>
#include "device/NRZI.h"


namespace qb50 {

    class FIFO
    {
        public:
            FIFO();
            ~FIFO();

            void push( Sample bit);
    };


}





#endif /* FIFO_H_INCLUDED */
