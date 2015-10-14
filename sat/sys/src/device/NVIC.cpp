
#include "device/NVIC.h"

#include <safe_stm32f4xx.h>


using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

NVIC::NVIC()
{
	/*
	 * See the STM32F4 Programming Manual sec. 4.4.5,
	 * "Application interrupt and reset control register" (pp. 212-213)
	 *
	 * "To write to this register, you must write 0x5FA to the
	 *  VECTKEY Field, otherwise the processor ignores the write."
	 *
	 * Also: http://qb50.oprs.eu/nosuchthing.gif
	 */

	SCB->AIRCR = ( 0x05fa << 16 )  /* VECTKEY  */
	           | (   0x03 <<  8 ); /* PRIGROUP */
}


NVIC::~NVIC()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void NVIC::enable( uint32_t IRQn, Priority sel )
{
	NVIC_Type *NVICx = (NVIC_Type*)NVIC_BASE;

	NVICx->IP[ IRQn ] = sel << 4;
	NVICx->ISER[ IRQn >> 0x05 ] = 0x01 << ( IRQn & 0x1f );
	//clear( IRQn );
}


void NVIC::disable( uint32_t IRQn )
{
	(void)IRQn; /* XXX */
}


void NVIC::clear( uint32_t IRQn )
{
	NVIC_Type *NVICx = (NVIC_Type*)NVIC_BASE;
	NVICx->ICPR[ IRQn >> 0x05 ] = 0x01 << ( IRQn & 0x1f );
}

/*EoF*/
