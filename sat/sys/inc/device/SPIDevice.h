
#ifndef _QB50_SYS_DEVICE_SPI_DEVICE_H
#define _QB50_SYS_DEVICE_SPI_DEVICE_H

#include "device/SPI.h"
#include "device/GPIOPin.h"


namespace qb50 {

	class SPIDevice : public Device
	{
		public:

			enum SelectMode {
				ActiveLow  = 0,
				ActiveHigh = 1
			};

			SPIDevice( SPI& spi, GPIOPin& csPin, SelectMode csMode );
			~SPIDevice();

			virtual SPIDevice& enable  ( void ) = 0;
			virtual SPIDevice& disable ( void ) = 0;

			SPIDevice& select   ( void );
			SPIDevice& deselect ( void );

		protected:

			SPI&       _spi;
			GPIOPin&   _csPin;
			SelectMode _csMode;
	};

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_SPI_DEVICE_H*/

/*EoF*/

