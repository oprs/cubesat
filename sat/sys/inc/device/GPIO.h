
#ifndef _QB50_SYS_GPIO_H
#define _QB50_SYS_GPIO_H

#include "BusDevice.h"
#include "Bus.h"


namespace qb50 {

	class GPIOPin;

	class GPIO : public BusDevice
	{
		public:

			GPIO( Bus& bus, const uint32_t iobase, const uint32_t periph, const unsigned id, const char *name, GPIOPin *pins );
			~GPIO();

			GPIO& enable  ( void );
			GPIO& disable ( void );

			unsigned id ( void ) const { return _id;   }

		private:

			const unsigned _id;
			GPIOPin *_pins;
	};

	extern qb50::GPIO GPIOA;
	extern qb50::GPIO GPIOB;
	extern qb50::GPIO GPIOC;
	extern qb50::GPIO GPIOD;
	extern qb50::GPIO GPIOE;

} /* qb50 */


#endif /*_QB50_SYS_GPIO_H*/

/*EoF*/
