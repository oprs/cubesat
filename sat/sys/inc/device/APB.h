
#ifndef _QB50_SYS_BUS_APB_H
#define _QB50_SYS_BUS_APB_H

#include "Bus.h"
#include "BusDevice.h"


namespace qb50 {

	class APB : public Bus
	{
		public:

			APB( uint32_t APBn, const char *name );
			~APB();

			APB&     enable  ( BusDevice *dev );
			APB&     disable ( BusDevice *dev );
			uint32_t freq    ( void );

			uint32_t _APBn;
	};

	extern qb50::APB APB1;
	extern qb50::APB APB2;

} /* qb50 */


#endif /*_QB50_SYS_BUS_APB_H*/

/*EoF*/
