
#ifndef _QB50_SYSTEM_BUS_H
#define _QB50_SYSTEM_BUS_H

#include <stdint.h>


namespace qb50 {

	class BusDevice;

	class Bus
	{
		public:
			Bus() { ; }
			virtual ~Bus() { ; }

			virtual Bus&     enable  ( BusDevice *dev ) = 0;
			virtual Bus&     disable ( BusDevice *dev ) = 0;
			virtual uint32_t freq    ( void )           = 0;
	};

} /* qb50 */


#endif /*_QB50_SYSTEM_BUS_H*/

/*EoF*/
