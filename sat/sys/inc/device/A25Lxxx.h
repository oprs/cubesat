
#ifndef _QB50_SYS_DEVICE_A25LXXX_H
#define _QB50_SYS_DEVICE_A25LXXX_H

#include "device/SPIDevice.h"


namespace qb50 {

	class A25Lxxx : public SPIDevice
	{
		public:

			A25Lxxx( SPI& spi, const char *name, GPIOPin& csPin );
			~A25Lxxx();

			A25Lxxx& enable  ( void );
			A25Lxxx& disable ( void );

			const char *name ( void ) const { return _name; }

			/* read device id */

			struct RDIDResp {
				uint8_t z0;      /*!< dummy byte      */
				uint8_t manId;   /*!< Manufacturer ID */
				uint8_t memType; /*!< Memory Type     */
				uint8_t memCap;  /*!< Memory Capacity */
			} __attribute__(( packed ));

			A25Lxxx& RDID( RDIDResp *rdid );

			/* read electronic manufacturer id */

			struct REMSResp {
				uint8_t z0;      /*!< dummy byte      */
				uint8_t z1;      /*!< dummy byte      */
				uint8_t z2;      /*!< dummy byte      */
				uint8_t z3;      /*!< dummy byte      */
				uint8_t manId;   /*!< Manufacturer ID */
				uint8_t devId;   /*!< Device ID       */
			} __attribute__(( packed ));

			A25Lxxx& REMS( REMSResp *rems );

			/* read status register */

			struct RDSRResp {
				uint8_t z0;      /*!< dummy byte      */
				uint8_t sr;      /*!< status register */
			} __attribute__(( packed ));

			A25Lxxx& RDSR1( RDSRResp *rdsr );
			A25Lxxx& RDSR2( RDSRResp *rdsr );

			/* read data bytes */

			A25Lxxx& READ( uint32_t addr, void *x, uint32_t len );

			/* write enable */

			A25Lxxx& WREN( void );

			/* sector erase */

			A25Lxxx& SE( uint32_t addr );

			/* block erase */

			A25Lxxx& BE( uint32_t addr );

			/* page program */

			A25Lxxx& PP( uint32_t addr, void *x, uint32_t len );

		private:

			const char *_name;

			A25Lxxx& _WIPWait( unsigned ms = 10 );
	};

	extern qb50::A25Lxxx flash0;
	extern qb50::A25Lxxx flash1;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_A25LXXX_H*/

/*EoF*/
