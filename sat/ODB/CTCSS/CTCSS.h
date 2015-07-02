#ifndef CTCSS_H_INCLUDED
#define CTCSS_H_INCLUDED

#include "system/qb50.h"
#include <FreeRTOS.h>
#include "DECTONEHandler.h"
#include "device/GPIOPin.h"

#define T_PA_MAX 75
#define T_PA_MIN 60

#define WAIT1MN 60000 // 1mn = ( 60 * 1000ms)


namespace qb50 {

    class CTCSS
    {
        public:

            CTCSS( GPIOPin& txPin, GPIOPin& paPin );
            ~CTCSS();

            CTCSS& enable( void );
            CTCSS& disable( void );

            void modeRelaisFM();

        private:

            GPIOPin& _txPin;
            GPIOPin& _paPin;

            DECTONEHandler *_handle;

            xSemaphoreHandle _ctcssLock;

            int temp_PA14[8];
            int temp_PA15[6];
    };

    extern qb50::CTCSS ctcss;
}



#endif /* CTCSS_H_INCLUDED */
