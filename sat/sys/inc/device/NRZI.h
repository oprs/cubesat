#ifndef NRZI_H_INCLUDED
#define NRZI_H_INCLUDED

#include <FreeRTOS.h>




namespace qb50 {

    enum Sample {
        LOW = 0, HIGH = 1
    };


    class NRZI
    {
        public:

            NRZI();
            ~NRZI();
            Sample push( Sample current);

        private:

            Sample _backValue;
    };

}



#endif /* NRZI_H_INCLUDED */
