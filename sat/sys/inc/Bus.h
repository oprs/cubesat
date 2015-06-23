
#ifndef _QB50_SYSTEM_BUS_H
#define _QB50_SYSTEM_BUS_H

#include <stdint.h>


namespace qb50 {

	class BusDevice;

	class Bus
	{
		public:
			Bus( const char *name ) : _name( name )
			{ ; }

			virtual ~Bus()
			{ ; }

			const char *name ( void ) const { return _name; }

			virtual Bus&     enable  ( BusDevice *dev ) = 0;
			virtual Bus&     disable ( BusDevice *dev ) = 0;
			virtual uint32_t freq    ( void )           = 0;

		protected:

			const char *_name;

	};

} /* qb50 */


#endif /*_QB50_SYSTEM_BUS_H*/

/*EoF*/
