
#ifndef _QB50_SYS_DEVICE_A25LXXX_H
#define _QB50_SYS_DEVICE_A25LXXX_H

#include "device/FlashMemory.h"
#include "device/SPISlave.h"

#include <task.h>


namespace qb50 {

   class A25Lxxx : public FlashMemory, public SPISlave
   {

      private:

         struct IOReq;

      public:

         A25Lxxx( SPI& spi, const char *name, GPIOPin& csPin );
         ~A25Lxxx();

         void run( void );

         /* FlashMemory interface */

         A25Lxxx& init        ( void );
         A25Lxxx& enable      ( bool silent = false );
         A25Lxxx& disable     ( bool silent = false );
         A25Lxxx& ioctl       ( IOReq *req, TickType_t maxWait = portMAX_DELAY );

         A25Lxxx& pageRead    ( uint32_t addr, void *x       );
         A25Lxxx& pageWrite   ( uint32_t addr, const void *x );
         A25Lxxx& sectorErase ( uint32_t addr                );
         A25Lxxx& sectorRead  ( uint32_t addr, void *x       );
         A25Lxxx& sectorWrite ( uint32_t addr, const void *x );
         A25Lxxx& blockErase  ( uint32_t addr                );

      private:

         xQueueHandle _ioQueue;
         TaskHandle_t _ioTask;

         /* type definition for A25Lxxx chips */

         struct A25LChip {
            const uint16_t sig;  /* JEDEC signature   */
            const uint16_t mask; /* signature mask    */
            const char    *name; /* chip name         */
            uint16_t       bpc;  /* blocks per chip   */
            uint16_t       spb;  /* sectors per block */
            uint16_t       pps;  /* pages per sector  */
            uint16_t       bpp;  /* bytes per page    */
         };

         static A25LChip chips[];

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
            SR      = 4,
            SW      = 5,
            BE      = 6,
            PP      = 7
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

         struct IOReq_ENABLE : public IOReq
         {
            bool _silent;

            IOReq_ENABLE( bool silent )
            : IOReq( ENABLE ), _silent( silent )
            { ; }
         };

         struct IOReq_DISABLE : public IOReq
         {
            bool _silent;

            IOReq_DISABLE( bool silent )
            : IOReq( DISABLE ), _silent( silent )
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

         struct IOReq_SR : public IOReq
         {
            uint32_t _addr;
            void    *_x;

            IOReq_SR( uint32_t addr, void *x )
            : IOReq( SR ), _addr( addr ), _x( x )
            { ; }
         };

         struct IOReq_SW : public IOReq
         {
            uint32_t    _addr;
            const void *_x;

            IOReq_SW( uint32_t addr, const void *x )
            : IOReq( SW ), _addr( addr ), _x( x )
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

         void _enable      ( IOReq_ENABLE  *req );
         void _disable     ( IOReq_DISABLE *req );
         void _pageWrite   ( IOReq_PP      *req );
         void _pageRead    ( IOReq_READ    *req );
         void _sectorErase ( IOReq_SE      *req );
         void _sectorRead  ( IOReq_SR      *req );
         void _sectorWrite ( IOReq_SW      *req );
         void _blockErase  ( IOReq_BE      *req );

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

} /* qb50 */


#endif /*_QB50_SYS_DEVICE_A25LXXX_H*/

/*EoF*/
