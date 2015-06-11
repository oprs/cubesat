#ifndef EXTI_H_INCLUDED
#define EXTI_H_INCLUDED

#include <FreeRTOS.h>
#include <semphr.h>

#include "device/GPIOPin.h"
#include "Device.h"


namespace qb50 {

    class EXTI
    {
        public:

            EXTI();
            ~EXTI();

            void trigged(GPIOPin &Pin);
            void isr( int i );


        private:

            xSemaphoreHandle _extiLock[16];
    };

    extern qb50::EXTI EXTI1;
}


extern "C" {
    void     EXTI0_IRQHandler( void );
    void     EXTI1_IRQHandler( void );
    void     EXTI2_IRQHandler( void );
    void     EXTI3_IRQHandler( void );
    void     EXTI4_IRQHandler( void );
    void   EXTI9_5_IRQHandler( void );
    void EXTI15_10_IRQHandler( void );
};

#endif /* EXTI_H_INCLUDED */
