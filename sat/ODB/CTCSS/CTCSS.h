
#ifndef _QB50_CTCSS_H
#define _QB50_CTCSS_H

#include <semphr.h>

#include "system/qb50.h"
#include "DECTONEHandler.h"
#include "device/GPIOPin.h"

#define T_PA_MAX 75
#define T_PA_MIN 60

//#define WAIT1MN 60000 // 1mn = ( 60 * 1000ms)


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

            DECTONEHandler *_handleRise;
            DECTONEHandler *_handleFall;

            xSemaphoreHandle _ctcssRise;
            xSemaphoreHandle _ctcssFall;

            int temp_PA14[8];
            int temp_PA15[6];

    };

} /* qb50 */

#endif /* _QB50_CTCSS_H */
