
#ifndef _QB50_SYS_DEVICE_MAX111X_H
#define _QB50_SYS_DEVICE_MAX111X_H

#include "device/SPIDevice.h"


namespace qb50 {

	class MAX111x : public SPIDevice
	{
		public:

			MAX111x( SPI& spi, GPIOPin& csPin );
			~MAX111x();

			MAX111x& enable  ( void );
			MAX111x& disable ( void );

			/* channel selection */

			enum Channel {
				CH0 = 0, /*!< channel 0 */
				CH1 = 4, /*!< channel 1 */
				CH2 = 1, /*!< channel 2 */
				CH3 = 5, /*!< channel 3 */
				CH4 = 2, /*!< channel 4 */
				CH5 = 6, /*!< channel 5 */
				CH6 = 3, /*!< channel 6 */
				CH7 = 7  /*!< channel 7 */
			};

			int readChannel( Channel sel );
	};

	extern qb50::MAX111x ADC1;
	extern qb50::MAX111x ADC2;
	extern qb50::MAX111x ADC3;
	extern qb50::MAX111x ADC4;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_MAX111X_H*/

/*EoF*/
