
#ifndef _QB50_SYSTEM_DEVICE_H
#define _QB50_SYSTEM_DEVICE_H

#include "system/Application.h"

namespace qb50 {

	class Device
	{
		public:

			Device() : _refCount( 0 )
			{ ; }

			virtual ~Device()
			{ ; }

			virtual Device& enable  ( void ) = 0;
			virtual Device& disable ( void ) = 0;

		protected:

			unsigned _refCount;

			inline unsigned _incRef( void )
			{ return _refCount++; }

			inline unsigned _decRef( void )
			{
				if( _refCount > 0 ) _refCount--;
				return _refCount;
			}

	};

} /* qb50 */


#endif /*_QB50_SYSTEM_DEVICE_H*/

/*EoF*/
