
#ifndef _QB50_SYS_NRZI_H
#define _QB50_SYS_NRZI_H

#include <FreeRTOS.h>


namespace qb50 {

/*
    enum Sample {
        LOW = 0, HIGH = 1
    };
*/

    class NRZI
    {
        public:

            NRZI();
            ~NRZI();

            bool push( bool current );

        private:

            bool _backValue;
    };

}

#endif /*_QB50_SYS_NRZI_H*/

/*EoF*/
