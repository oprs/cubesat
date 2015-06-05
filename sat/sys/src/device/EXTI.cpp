
#include "device/EXTI.h"
#include "device/NVIC.h"
#include "device/GPIOPin.h"
#include <stm32f4xx.h>
#undef EXTI
#undef NVIC

using namespace qb50;


EXTI::EXTI()
{
    int i(0);

    for( i = 0; i < 16; i++ )
    {
        _extiLock[i] = xSemaphoreCreateMutex();

    }
}


EXTI::~EXTI()
{
    vSemaphoreDelete(_extiLock[16]);
}


void EXTI::trigged(GPIOPin& Pin)
{
    EXTI_TypeDef *x = (EXTI_TypeDef*)EXTI_BASE;
    register uint32_t tmp32;

    /* Select Pin as input */
    Pin.enable().in().noPull();

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; //Enable clock SYSCFG


    /* Set Pin C9 as EXTI9 with SYSCFG module */
    tmp32  = SYSCFG->EXTICR[2];
    tmp32 &= 0xFF0F; //Clear EXTI9 pin data
    tmp32 |= 0x0020; //PC2 equals 2
    SYSCFG->EXTICR[2] = tmp32;

    uint32_t exti_mask = 0x0001 << Pin.id();

    x->IMR   |= exti_mask; //Interrupt mask.
    x->RTSR  |= exti_mask;
    x->SWIER |= exti_mask; // XXX
    x->PR    |= exti_mask;

    /* NVIC IRQ channel configuration*/
    IRQ.enable( EXTI0_IRQn );
    IRQ.enable( EXTI1_IRQn );
    IRQ.enable( EXTI2_IRQn );
    IRQ.enable( EXTI3_IRQn );
    IRQ.enable( EXTI4_IRQn );
    IRQ.enable( EXTI9_5_IRQn );
    IRQ.enable( EXTI15_10_IRQn );


}


//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void EXTI::isr( int i )
{
    portBASE_TYPE higherPriorityTask  = pdFALSE;

    //PC8.toggle();
    xSemaphoreGiveFromISR( _extiLock[i], &higherPriorityTask );

    if ( higherPriorityTask == pdTRUE )
    {
        portEND_SWITCHING_ISR( higherPriorityTask );
    }
}


//  - - - - - - - - - - - - - - - - -  //
//  E X T I _ I R Q   H A N D L E R S  //
//  - - - - - - - - - - - - - - - - -  //

/* EXTI0_IRQHandler */

void EXTI0_IRQHandler(void)
{
    EXTI_TypeDef *x = (EXTI_TypeDef*)EXTI_BASE;

    x->PR |= EXTI_PR_PR0;
    qb50::EXTI1.isr(0);
}

/* EXTI1_IRQHandler */

void EXTI1_IRQHandler(void)
{
    EXTI_TypeDef *x = (EXTI_TypeDef*)EXTI_BASE;

    x->PR |= EXTI_PR_PR1;
    qb50::EXTI1.isr(1);
}

/* EXTI2_IRQHandler */

void EXTI2_IRQHandler(void)
{
    EXTI_TypeDef *x = (EXTI_TypeDef*)EXTI_BASE;

    x->PR |= EXTI_PR_PR2;
    qb50::EXTI1.isr(2);
}

/* EXTI3_IRQHandler */

void EXTI3_IRQHandler(void)
{
    EXTI_TypeDef *x = (EXTI_TypeDef*)EXTI_BASE;

    x->PR |= EXTI_PR_PR3;
    qb50::EXTI1.isr(3);
}

/* EXTI4_IRQHandler */

void EXTI4_IRQHandler(void)
{
    EXTI_TypeDef *x = (EXTI_TypeDef*)EXTI_BASE;

    x->PR |= EXTI_PR_PR4;
    qb50::EXTI1.isr(4);
}

/* EXTI9_5_IRQHandler */

void EXTI9_5_IRQHandler(void)
{
    EXTI_TypeDef *x = (EXTI_TypeDef*)EXTI_BASE;

    //PB0.toggle(); //LED2

    if ( x->PR & (EXTI_PR_PR5) )
    {
         x->PR |= EXTI_PR_PR5;
         qb50::EXTI1.isr(5);
    }

    if ( x->PR & (EXTI_PR_PR6) )
    {
         x->PR |= EXTI_PR_PR6;
         qb50::EXTI1.isr(6);
    }

    if ( x->PR & (EXTI_PR_PR7) )
    {
         x->PR |= EXTI_PR_PR7;
         qb50::EXTI1.isr(7);
    }

    if ( x->PR & (EXTI_PR_PR8) )
    {
         x->PR |= EXTI_PR_PR8;
         qb50::EXTI1.isr(8);
    }

    if ( x->PR & (EXTI_PR_PR9) )
    {
         x->PR |= EXTI_PR_PR9;
         qb50::EXTI1.isr(9);
    }

}

/* EXTI15_10_IRQHandler */

void EXTI15_10_IRQHandler(void)
{
    EXTI_TypeDef *x = (EXTI_TypeDef*)EXTI_BASE;

    if ( x->PR & (EXTI_PR_PR10) )
    {
         x->PR |= EXTI_PR_PR10;
         qb50::EXTI1.isr(10);
    }

    if ( x->PR & (EXTI_PR_PR11) )
    {
         x->PR |= EXTI_PR_PR11;
         qb50::EXTI1.isr(11);
    }

    if ( x->PR & (EXTI_PR_PR12) )
    {
         x->PR |= EXTI_PR_PR12;
         qb50::EXTI1.isr(12);
    }

    if ( x->PR & (EXTI_PR_PR13) )
    {
         x->PR |= EXTI_PR_PR13;
         qb50::EXTI1.isr(13);
    }

    if ( x->PR & (EXTI_PR_PR14) )
    {
         x->PR |= EXTI_PR_PR14;
         qb50::EXTI1.isr(14);
    }

    if ( x->PR & (EXTI_PR_PR15) )
    {
         x->PR |= EXTI_PR_PR15;
         qb50::EXTI1.isr(15);
    }

}
