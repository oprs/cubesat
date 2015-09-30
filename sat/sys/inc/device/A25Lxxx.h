
#ifndef _QB50_SYS_DEVICE_A25LXXX_H
#define _QB50_SYS_DEVICE_A25LXXX_H

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#include "device/SPIDevice.h"


namespace qb50 {

   class A25Lxxx : public SPIDevice
   {

      private:

         struct IOReq;

      public:

         A25Lxxx( SPI& spi, const char *name, GPIOPin& csPin );
         ~A25Lxxx();

         A25Lxxx& init( void );

         A25Lxxx& ioctl( IOReq *req, TickType_t maxWait = portMAX_DELAY );

         A25Lxxx& enable      ( bool silent = false );
         A25Lxxx& disable     ( bool silent = false );
         A25Lxxx& pageRead    ( uint32_t addr, void *x );
         A25Lxxx& pageWrite   ( uint32_t addr, const void *x );
         A25Lxxx& sectorErase ( uint32_t addr );
         A25Lxxx& blockErase  ( uint32_t addr );

         void run( void );

      private:

         xQueueHandle _ioQueue;
         TaskHandle_t _ioTask;

         /* read device id */

         struct RDIDResp {
            uint8_t z0;      /*!< dummy byte      */
            uint8_t manId;   /*!< Manufacturer ID */
            uint8_t memType; /*!< Memory Type     */
            uint8_t memCap;  /*!< Memory Capacity */
         } __attribute__(( packed ));

         /* read electronic manufacturer id */

         struct REMSResp {
            uint8_t z0;      /*!< dummy byte      */
            uint8_t z1;      /*!< dummy byte      */
            uint8_t z2;      /*!< dummy byte      */
            uint8_t z3;      /*!< dummy byte      */
            uint8_t manId;   /*!< Manufacturer ID */
            uint8_t devId;   /*!< Device ID       */
         } __attribute__(( packed ));

         /* read status register */

         struct RDSRResp {
            uint8_t z0;      /*!< dummy byte      */
            uint8_t sr;      /*!< status register */
         } __attribute__(( packed ));

         /* IOCTLs */

         enum IOCTL {
            ENABLE  = 0,
            DISABLE = 1,
            READ    = 2,
            SE      = 3,
            BE      = 4,
            PP      = 5
         };

         struct IOReq
         {
            IOCTL        _op;
            TaskHandle_t _handle;

            IOReq( IOCTL op ) : _op( op )
            { _handle = xTaskGetCurrentTaskHandle(); }

            ~IOReq()
            { ; }
         };

         struct IOReq_READ : public IOReq
         {
            uint32_t _addr;
            void    *_x;

            IOReq_READ( uint32_t addr, void *x )
            : IOReq( READ ), _addr( addr ), _x( x )
            { ; }
         };

         struct IOReq_SE : public IOReq
         {
            uint32_t _addr;

            IOReq_SE( uint32_t addr ) : IOReq( SE ), _addr( addr )
            { ; }
         };

         struct IOReq_BE : public IOReq
         {
            uint32_t _addr;

            IOReq_BE( uint32_t addr ) : IOReq( BE ), _addr( addr )
            { ; }
         };

         struct IOReq_PP : public IOReq
         {
            uint32_t    _addr;
            const void *_x;

            IOReq_PP( uint32_t addr, const void *x )
            : IOReq( PP ), _addr( addr ), _x( x )
            { ; }
         };

         /* operations */

         void _pageWrite   ( IOReq_PP   *req );
         void _pageRead    ( IOReq_READ *req );
         void _sectorErase ( IOReq_SE   *req );
         void _blockErase  ( IOReq_BE   *req );

         void _SE   ( uint32_t addr );
         void _BE   ( uint32_t addr  );
         void _RDID ( RDIDResp *rdid );
         void _READ ( uint32_t addr, void * );
         void _PP   ( uint32_t addr, const void *x );
         void _WREN ( void );
         void _WRDI ( void );
         void _REMS ( REMSResp *rems );

         void _WIPWait( unsigned ms = 10 );

   };

   extern qb50::A25Lxxx FLASH0;
   extern qb50::A25Lxxx FLASH1;

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_A25LXXX_H*/

/*EoF*/
