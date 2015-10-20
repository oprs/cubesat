
#include "device/EXTI.h"
#include "device/NVIC.h"
#include "device/GPIO.h"

#include <stm32f4xx.h> /* XXX */

#undef EXTI

using namespace qb50;


EXTI::EXTI()
{
    for( int i = 0; i < 16; i++ )
        _extiHandler[i] = (EXTIHandler*)0;
}


EXTI::~EXTI()
{
    for( int i = 0; i < 16; i++ )
        _extiHandler[i] = (EXTIHandler*)0;
}


void EXTI::registerHandler( GPIO::Pin& pin, EXTIHandler *handler, Edge edge )
{
    EXTI_TypeDef *EXTIx = (EXTI_TypeDef*)EXTI_BASE;

    const unsigned pinId  = pin.id();
    const unsigned portId = pin.portId();

    const unsigned pinHi  = ( pinId >> 2 ) & 0x03;
    const unsigned pinLo  =   pinId        & 0x03;

    register uint32_t tmp32;

    /* register handler */

    _extiHandler[ pinId ] = handler;

    /* set pin as input */

    pin.enable().in().noPull();
/*
    if( edge == FALLING ) {
        pin.pullUp();
    } else {
        pin.pullDn();
    }
*/

    /* XXX enable clock for SYSCFG */

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    /* setup the external interrupt */

    tmp32  = SYSCFG->EXTICR[ pinHi ];
    tmp32 &= ~( 0x000f << ( 4 * pinLo ));
    tmp32 |=    portId << ( 4 * pinLo );
    SYSCFG->EXTICR[ pinHi ] = tmp32;

    uint32_t exti_mask = 0x0001 << pinId;

    EXTIx->IMR |= exti_mask;

    switch( edge ) {
        case RISING:
            EXTIx->RTSR |=  exti_mask;
            EXTIx->FTSR &= ~exti_mask;
            break;

        case FALLING:
            EXTIx->RTSR &= ~exti_mask;
            EXTIx->FTSR |=  exti_mask;
            break;

        case BOTH:
        default:
            EXTIx->RTSR |=  exti_mask;
            EXTIx->FTSR |=  exti_mask;
            break;
    }

    EXTIx->SWIER |= exti_mask; // XXX
    EXTIx->PR    |= exti_mask;

    /* XXX - NVIC IRQ channel configuration*/

    IRQ.enable( EXTI0_IRQn     );
    IRQ.enable( EXTI1_IRQn     );
    IRQ.enable( EXTI2_IRQn     );
    IRQ.enable( EXTI3_IRQn     );
    IRQ.enable( EXTI4_IRQn     );
    IRQ.enable( EXTI9_5_IRQn   );
    IRQ.enable( EXTI15_10_IRQn );

}


//  - - - - - - - - - - - -  //
//  I S R   H A N D L E R S  //
//  - - - - - - - - - - - -  //

void EXTI::isr( EXTIn i )
{
    EXTIHandler *handler = _extiHandler[ i ];
    if( handler != 0 )
        handler->handle( i );
}


//  - - - - - - - - - - - - - - - - -  //
//  E X T I _ I R Q   H A N D L E R S  //
//  - - - - - - - - - - - - - - - - -  //

/* EXTI0_IRQHandler */

void EXTI0_IRQHandler( void )
{
    EXTI_TypeDef *EXTIx = (EXTI_TypeDef*)EXTI_BASE;

    EXTIx->PR |= EXTI_PR_PR0;
    qb50::EXTI1.isr( EXTI::EXTI0 );
}

/* EXTI1_IRQHandler */

void EXTI1_IRQHandler( void )
{
    EXTI_TypeDef *EXTIx = (EXTI_TypeDef*)EXTI_BASE;

    EXTIx->PR |= EXTI_PR_PR1;
    qb50::EXTI1.isr( EXTI::EXTI1 );
}

/* EXTI2_IRQHandler */

void EXTI2_IRQHandler( void )
{
    EXTI_TypeDef *EXTIx = (EXTI_TypeDef*)EXTI_BASE;

    EXTIx->PR |= EXTI_PR_PR2;
    qb50::EXTI1.isr( EXTI::EXTI2 );
}

/* EXTI3_IRQHandler */

void EXTI3_IRQHandler( void )
{
    EXTI_TypeDef *EXTIx = (EXTI_TypeDef*)EXTI_BASE;

    EXTIx->PR |= EXTI_PR_PR3;
    qb50::EXTI1.isr( EXTI::EXTI3 );
}

/* EXTI4_IRQHandler */

void EXTI4_IRQHandler( void )
{
    EXTI_TypeDef *EXTIx = (EXTI_TypeDef*)EXTI_BASE;

    EXTIx->PR |= EXTI_PR_PR4;
    qb50::EXTI1.isr( EXTI::EXTI4 );
}

/* EXTI9_5_IRQHandler */

void EXTI9_5_IRQHandler( void )
{
    EXTI_TypeDef *EXTIx = (EXTI_TypeDef*)EXTI_BASE;

    if( EXTIx->PR & EXTI_PR_PR5 )
    {
         EXTIx->PR |= EXTI_PR_PR5;
         qb50::EXTI1.isr( EXTI::EXTI5 );
    }

    if( EXTIx->PR & EXTI_PR_PR6 )
    {
         EXTIx->PR |= EXTI_PR_PR6;
         qb50::EXTI1.isr( EXTI::EXTI6 );
    }

    if( EXTIx->PR & EXTI_PR_PR7 )
    {
         EXTIx->PR |= EXTI_PR_PR7;
         qb50::EXTI1.isr( EXTI::EXTI7 );
    }

    if( EXTIx->PR & EXTI_PR_PR8 )
    {
         EXTIx->PR |= EXTI_PR_PR8;
         qb50::EXTI1.isr( EXTI::EXTI8 );
    }

    if( EXTIx->PR & EXTI_PR_PR9 )
    {
         EXTIx->PR |= EXTI_PR_PR9;
         qb50::EXTI1.isr( EXTI::EXTI9 );
    }

}

/* EXTI15_10_IRQHandler */

void EXTI15_10_IRQHandler( void )
{
    EXTI_TypeDef *EXTIx = (EXTI_TypeDef*)EXTI_BASE;

    if( EXTIx->PR & EXTI_PR_PR10 )
    {
         EXTIx->PR |= EXTI_PR_PR10;
         qb50::EXTI1.isr( EXTI::EXTI10 );
    }

    if( EXTIx->PR & EXTI_PR_PR11 )
    {
         EXTIx->PR |= EXTI_PR_PR11;
         qb50::EXTI1.isr( EXTI::EXTI11 );
    }

    if( EXTIx->PR & EXTI_PR_PR12 )
    {
         EXTIx->PR |= EXTI_PR_PR12;
         qb50::EXTI1.isr( EXTI::EXTI12 );
    }

    if( EXTIx->PR & EXTI_PR_PR13 )
    {
         EXTIx->PR |= EXTI_PR_PR13;
         qb50::EXTI1.isr( EXTI::EXTI13 );
    }

    if( EXTIx->PR & EXTI_PR_PR14 )
    {
         EXTIx->PR |= EXTI_PR_PR14;
         qb50::EXTI1.isr( EXTI::EXTI14 );
    }

    if( EXTIx->PR & EXTI_PR_PR15 )
    {
         EXTIx->PR |= EXTI_PR_PR15;
         qb50::EXTI1.isr( EXTI::EXTI15 );
    }

}
