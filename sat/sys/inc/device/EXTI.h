
#ifndef _QB50_SYS_EXTI_H
#define _QB50_SYS_EXTI_H

#include "device/GPIO.h"
#include "device/FIFO.hpp"
#include "Device.h"


namespace qb50 {

    /* forward declaration */
    class EXTIHandler;

    class EXTI
    {
        public:

            EXTI();
            ~EXTI();

            enum EXTIn {
                EXTI0  = 0,  EXTI1  = 1,
                EXTI2  = 2,  EXTI3  = 3,
                EXTI4  = 4,  EXTI5  = 5,
                EXTI6  = 6,  EXTI7  = 7,
                EXTI8  = 8,  EXTI9  = 9,
                EXTI10 = 10, EXTI11 = 11,
                EXTI12 = 12, EXTI13 = 13,
                EXTI14 = 14, EXTI15 = 15
            };

            enum Edge {
                RISING = 0, FALLING = 1, BOTH = 2
            };

            //void trigged( GPIO::Pin &Pin );
            void registerHandler( GPIO::Pin &Pin, EXTIHandler *handler, Edge edge = RISING );
            void isr( EXTIn i );


        private:

            //xSemaphoreHandle _extiLock[16];
            EXTIHandler* _extiHandler[16];
    };

    class EXTIHandler
    {
        public:

            EXTIHandler() { ; }
            virtual ~EXTIHandler() { ; } //ajout de virtual

            virtual void handle( EXTI::EXTIn ) = 0;
    };

    extern qb50::EXTI EXTI1;

} /* qb50 */


extern "C" {
    void     EXTI0_IRQHandler( void );
    void     EXTI1_IRQHandler( void );
    void     EXTI2_IRQHandler( void );
    void     EXTI3_IRQHandler( void );
    void     EXTI4_IRQHandler( void );
    void   EXTI9_5_IRQHandler( void );
    void EXTI15_10_IRQHandler( void );
};

#endif /*_QB50_SYS_EXTI_H*/

/*EoF*/
