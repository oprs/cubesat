
#ifndef _QB50_SYS_BUS_AHB_H
#define _QB50_SYS_BUS_AHB_H

#include "Bus.h"
#include "BusDevice.h"


namespace qb50 {

	class AHB : public Bus
	{

		public:

			enum BusId {
				BUS1 = 1,
				BUS2 = 2,
				BUS3 = 3
			};

			AHB( BusId id, const char *name );
			~AHB();

			AHB&     init    ( void );
			AHB&     enable  ( BusDevice *dev, bool silent = false );
			AHB&     disable ( BusDevice *dev, bool silent = false );
			uint32_t freq    ( void );

		protected:

			const BusId _id;

	};

	extern qb50::AHB AHB1;
	extern qb50::AHB AHB2;
	extern qb50::AHB AHB3;

} /* qb50 */


#endif /*_QB50_SYS_BUS_AHB_H*/

/*EoF*/
