
#include "device/A25Lxxx.h"
#include "system/Application.h"
#include "system/Logger.h"

using namespace qb50;

/*
 * 64 blocks
 * 64 blocks * 16 sectors/block = 1024 sectors
 * 64 blocks * 16 sectors/block * 16 pages/sector = 16384 pages
 * 64 blocks * 16 sectors/block * 16 pages/sector * 256 bytes/page = 4194304 bytes
 */

/* typical Sector Erase Cycle Time (ms) */
#define tSE 40

/* typical Block Erase Cycle Time (ms) */
#define tBE 500

/* typical Chip Erase Cycle Time (ms) */
#define tCE 32000

/* typical Page Program Cycle Time (ms) */
#define tPP 2

/* A25Lxxx parts definitions */

struct A25LPart {
   const uint16_t sig;  /* JEDEC signature */
   const uint16_t mask; /* signature mask  */
   const char    *name; /* part name       */
   const size_t   bpc;  /* blocks per chip */
   const size_t   ppb;  /* pages per block */
   const size_t   bpp;  /* bytes per page  */
};

static A25LPart parts[] = {
   /* sig.    mask    part #     bpc  ppb  bpp */
   { 0x3010, 0xffff, "A25L512",    1, 256, 256 }, /* 512 Kbit */
   { 0x3011, 0xffff, "A25L010",    2, 256, 256 }, /*   1 Mbit */
   { 0x3012, 0xffff, "A25L020",    4, 256, 256 }, /*   2 Mbit */
   { 0x3013, 0xffff, "A25L040",    8, 256, 256 }, /*   4 Mbit */
   { 0x3014, 0xffff, "A25L080",   16, 256, 256 }, /*   8 Mbit */
   { 0x3015, 0xffff, "A25L016",   32, 256, 256 }, /*  16 Mbit */
   { 0x4015, 0xffff, "A25LQ16",   32, 256, 256 }, /*  16 Mbit */
   { 0x3016, 0xffff, "A25L032",   64, 256, 256 }, /*  32 Mbit */
   { 0x4016, 0xffff, "A25LQ32A",  64, 256, 256 }, /*  32 Mbit */
   { 0x4017, 0xffff, "A25LQ64",  128, 256, 256 }, /*  64 Mbit */
   {      0,      0,  NULL,        0,   0,   0 }
};

/* SPI commands */

static const uint8_t RDIDCmd[]  = { 0x9f, 0xff, 0xff, 0xff };
static const uint8_t REMSCmd[]  = { 0x90, 0xff, 0xff, 0x00, 0xff, 0xff };
static const uint8_t RDSR1Cmd[] = { 0x05, 0xff };
static const uint8_t RDSR2Cmd[] = { 0x35, 0xff };
static const uint8_t WRENCmd[]  = { 0x06 };

static void _trampoline( void *x );


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

A25Lxxx::A25Lxxx( SPI& spi, const char *name, GPIOPin& csPin )
   : SPIDevice( spi, csPin, SPIDevice::ActiveLow, name )
{
   _ioQueue = xQueueCreate( 1, sizeof( IOReq* ));
}


A25Lxxx::~A25Lxxx()
{
   vQueueDelete( _ioQueue );
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

A25Lxxx& A25Lxxx::init( void )
{
   RDIDResp rdid;

   (void)SPIDevice::init();

   /* temporarily (silently) enable the device
    * in order to read its identification ID */

   _spi.grab();
   select();
   _enable( true ); /* be silent */

   IOReq_RDID req( &rdid );
   _RDID( &req );

   _disable( true ); /* be silent */
   deselect();
   _spi.release();

   /* display ID infos */

   uint16_t  sig  = ( rdid.memType << 8 ) | rdid.memCap;
   A25LPart *part = parts;

   while(( part->mask != 0 ) && ( part->sig != ( sig & part->mask )))
      ++part;

   if( part->mask == 0 ) {
      LOG << _name << ": unknown chip - defaulting to AMIC A25L032 at "
          << _spi.name() << ", cs: " << _csPin.name();
   } else {
      LOG << _name << ": AMIC " << part->name
          << " Onboard serial flash (" << (( part->bpc * part->ppb * part->bpp ) >> 17 ) << "Mbit) at "
          << _spi.name() << ", cs: " << _csPin.name();
   }

   (void)xTaskCreate( _trampoline, _name, 512, this, configMAX_PRIORITIES - 1, &_ioTask );

   return *this;
}


A25Lxxx& A25Lxxx::ioctl( IOReq *req, TickType_t maxWait )
{
   (void)xQueueSend( _ioQueue, &req, maxWait );
   (void)ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
   return *this;
}


A25Lxxx& A25Lxxx::enable( bool silent )
{
   (void)silent; /*XXX*/
   IOReq req( ENABLE );
   (void)ioctl( &req );
   return *this;
}


A25Lxxx& A25Lxxx::disable( bool silent )
{
   (void)silent; /*XXX*/
   IOReq req( DISABLE );
   (void)ioctl( &req );
   return *this;
}


A25Lxxx& A25Lxxx::readId( RDIDResp *rdid )
{
   IOReq_RDID req( rdid );
   (void)ioctl( &req );
   return *this;
}


A25Lxxx& A25Lxxx::pageRead( uint32_t addr, void *x )
{
   IOReq_READ req( addr, x );
   (void)ioctl( &req );
   return *this;
}


A25Lxxx& A25Lxxx::pageWrite( uint32_t addr, const void *x )
{
   IOReq_PP req( addr, x );
   (void)ioctl( &req );
   return *this;
}


A25Lxxx& A25Lxxx::sectorErase( uint32_t addr )
{
   IOReq_SE req( addr );
   (void)ioctl( &req );
   return *this;
}


A25Lxxx& A25Lxxx::blockErase( uint32_t addr )
{
   IOReq_BE req( addr );
   (void)ioctl( &req );
   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

static void _trampoline( void *x )
{
   A25Lxxx *self = (A25Lxxx*)x;
   self->run();
   vTaskDelete( NULL );
}


void A25Lxxx::run( void )
{
   IOReq *req;

   for( ;; ) {
      if( xQueueReceive( _ioQueue, &req, portMAX_DELAY ) != pdPASS )
         continue;

      _spi.grab(); // lock the SPI bus
      select();    // chip select ON

      switch( req->_op ) {
         case ENABLE:  _enable();                  break;
         case DISABLE: _disable();                 break;
         case RDID:    _RDID ( (IOReq_RDID*)req ); break;
         case READ:    _READ ( (IOReq_READ*)req ); break;
         case SE:      _SE   (   (IOReq_SE*)req ); break;
         case BE:      _BE   (   (IOReq_BE*)req ); break;
         case PP:      _PP   (   (IOReq_PP*)req ); break;
      }

      deselect();     // chip select OFF
      _spi.release(); // release the SPI bus

      (void)xTaskNotifyGive( req->_handle );
   }
}


void A25Lxxx::_RDID( IOReq_RDID *req )
{
   _spi.pollXfer( RDIDCmd, req->_rdid, sizeof( RDIDCmd ));
}


void A25Lxxx::_READ( IOReq_READ *req )
{
   uint8_t cmd[ 4 ];

   cmd[ 0 ] = 0x03;
   cmd[ 1 ] = ( req->_addr >> 16 ) & 0x3f;
   cmd[ 2 ] = ( req->_addr >>  8 ) & 0xff;
   cmd[ 3 ] =   req->_addr         & 0xff;

   _spi.pollXfer( cmd, NULL, sizeof( cmd ));
   _spi.read( req->_x, 256 /*req->_len*/ );
}


void A25Lxxx::_SE( IOReq_SE *req )
{
   uint8_t cmd[ 4 ];

   cmd[ 0 ] = 0x20;
   cmd[ 1 ] = ( req->_addr >> 16 ) & 0x3f;
   cmd[ 2 ] = ( req->_addr >>  8 ) & 0xf0;
   cmd[ 3 ] =   req->_addr         & 0x00;

   _spi.pollXfer( cmd, NULL, sizeof( cmd ));
   _WIPWait( tSE );
}


void A25Lxxx::_BE( IOReq_BE *req )
{
   uint8_t cmd[ 4 ];

   cmd[ 0 ] = 0x20;
   cmd[ 1 ] = ( req->_addr >> 16 ) & 0x3f;
   cmd[ 2 ] = ( req->_addr >>  8 ) & 0x00;
   cmd[ 3 ] =   req->_addr         & 0x00;

   _spi.pollXfer( cmd, NULL, sizeof( cmd ));
   _WIPWait( tBE );
}


void A25Lxxx::_PP( IOReq_PP *req )
{
   uint8_t cmd[ 4 ];

   cmd[ 0 ] = 0x02;
   cmd[ 1 ] = ( req->_addr >> 16 ) & 0x3f;
   cmd[ 2 ] = ( req->_addr >>  8 ) & 0xff;
   cmd[ 3 ] =   req->_addr         & 0xff;

   _spi.pollXfer( cmd, NULL, sizeof( cmd ));
   _spi.write( req->_x, 256 /*req->_len*/ );
   _WIPWait( tPP );
}


void A25Lxxx::_WREN( void )
{
   _spi.pollXfer( WRENCmd, NULL, sizeof( WRENCmd ));
}


void A25Lxxx::_REMS( REMSResp *rems )
{
   _spi.pollXfer( REMSCmd, rems, sizeof( REMSCmd ));
}


void A25Lxxx::_RDSR1( RDSRResp *rdsr )
{
   _spi.pollXfer( RDSR1Cmd, rdsr, sizeof( RDSR1Cmd ));
}


void A25Lxxx::_RDSR2( RDSRResp *rdsr )
{
   _spi.pollXfer( RDSR2Cmd, rdsr, sizeof( RDSR2Cmd ));
}


void A25Lxxx::_WIPWait( unsigned ms )
{
   RDSRResp rdsr;
   uint8_t rx;
   uint8_t tx = 0xff;

   if( ms > 0 ) {
      delay( ms );
      ms >>= 3;
   }

   _spi.pollXfer( RDSR1Cmd, &rdsr, sizeof( RDSR1Cmd ));

   if( rdsr.sr & 0x01 ) {
      do {
         if( ms > 0 ) delay( ms );
         _spi.pollXfer( &tx, &rx, 1 );
      } while( rx & 0x01 ); // XXX hard limit
   }
}

/*EoF*/
