
#ifndef _QB50_SYS_DEVICE_DMA_H
#define _QB50_SYS_DEVICE_DMA_H

#include "DMAStream.h"
#include "BusDevice.h"


namespace qb50 {

	class DMA : public BusDevice
	{
		public:

			DMA( Bus& bus, const uint32_t iobase, const uint32_t periph, const char *name, DMAStream *streams );
			~DMA();

			DMA& enable  ( void );
			DMA& disable ( void );

			DMAStream *streams;
	};

	extern qb50::DMA DMA1;
	extern qb50::DMA DMA2;

} /* qb50 */


extern "C" {
	void DMA1_Stream0_IRQHandler( void );
	void DMA1_Stream1_IRQHandler( void );
	void DMA1_Stream2_IRQHandler( void );
	void DMA1_Stream3_IRQHandler( void );
	void DMA1_Stream4_IRQHandler( void );
	void DMA1_Stream5_IRQHandler( void );
	void DMA1_Stream6_IRQHandler( void );
	void DMA1_Stream7_IRQHandler( void );

	void DMA2_Stream0_IRQHandler( void );
	void DMA2_Stream1_IRQHandler( void );
	void DMA2_Stream2_IRQHandler( void );
	void DMA2_Stream3_IRQHandler( void );
	void DMA2_Stream4_IRQHandler( void );
	void DMA2_Stream5_IRQHandler( void );
	void DMA2_Stream6_IRQHandler( void );
	void DMA2_Stream7_IRQHandler( void );
}


#endif /*_QB50_SYS_DEVICE_DMA_H*/

/*EoF*/
