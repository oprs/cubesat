
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

/* supported A25Lxxx chips */

A25Lxxx::A25LChip A25Lxxx::chips[] = {
  /* sig.    mask     part #     bpc  spb  pps  bpp */
   { 0x3010, 0xffff, "A25L512",    1,  16,  16, 256 }, /* 512 Kbit */
   { 0x3011, 0xffff, "A25L010",    2,  16,  16, 256 }, /*   1 Mbit */
   { 0x3012, 0xffff, "A25L020",    4,  16,  16, 256 }, /*   2 Mbit */
   { 0x3013, 0xffff, "A25L040",    8,  16,  16, 256 }, /*   4 Mbit */
   { 0x3014, 0xffff, "A25L080",   16,  16,  16, 256 }, /*   8 Mbit */
   { 0x3015, 0xffff, "A25L016",   32,  16,  16, 256 }, /*  16 Mbit */
   { 0x4015, 0xffff, "A25LQ16",   32,  16,  16, 256 }, /*  16 Mbit */
   { 0x3016, 0xffff, "A25L032",   64,  16,  16, 256 }, /*  32 Mbit */
   { 0x4016, 0xffff, "A25LQ32A",  64,  16,  16, 256 }, /*  32 Mbit */
   { 0x4017, 0xffff, "A25LQ64",  128,  16,  16, 256 }, /*  64 Mbit */
   {      0,      0,  NULL,        0,   0,   0,   0 }
};

/* SPI commands */

static const uint8_t RDIDCmd[]  = { 0x9f, 0xff, 0xff, 0xff };
static const uint8_t REMSCmd[]  = { 0x90, 0xff, 0xff, 0x00, 0xff, 0xff };
static const uint8_t RDSR1Cmd[] = { 0x05, 0xff };
static const uint8_t RDSR2Cmd[] = { 0x35, 0xff };
static const uint8_t WRENCmd[]  = { 0x06 };
static const uint8_t WRDICmd[]  = { 0x04 };

static void _trampoline( void *x );


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

A25Lxxx::A25Lxxx( SPI& spi, const char *name, GPIOPin& csPin )
   : FlashMemory( name ), SPISlave( spi, csPin, SPISlave::ActiveLow )
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

   (void)SPISlave::init();

   /* temporarily (silently) enable the device
    * in order to read its identification ID */

   _spi.grab();
   IOReq_ENABLE re( true );
   _enable( &re ); /* be silent */

   _RDID( &rdid );

   IOReq_DISABLE rd( true );
   _disable( &rd ); /* be silent */
   _spi.release();

   /* display ID infos */

   uint16_t  sig  = ( rdid.memType << 8 ) | rdid.memCap;
   A25LChip *chip = chips;

   while(( chip->mask != 0 ) && ( chip->sig != ( sig & chip->mask )))
      ++chip;

   if( chip->mask == 0 ) {
      LOG << _name << ": unknown chip - defaulting to AMIC A25L032";
      chip = &chips[7];
   }

   _geo.bpc = chip->bpc;
   _geo.spb = chip->spb;
   _geo.pps = chip->pps;
   _geo.bpp = chip->bpp;

   LOG << _name << ": Onboard AMIC " << chip->name
       << " serial flash (" << ( chipSize() >> 17 ) << "Mbit) at "
       << _spi.name() << ", cs: " << _csPin.name();

   LOG << _name << ": " << _geo.bpc << " blocks * "
                        << _geo.spb << " sectors * "
                        << _geo.pps << " pages * "
                        << _geo.bpp << " bytes";

   (void)xTaskCreate( _trampoline, _name, 768, this, configMAX_PRIORITIES - 1, &_ioTask );

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
   IOReq_ENABLE req( silent );
   (void)ioctl( &req );

   if( !silent )
      LOG << _name << ": enabled";

   return *this;
}


A25Lxxx& A25Lxxx::disable( bool silent )
{
   IOReq_DISABLE req( silent );
   (void)ioctl( &req );

   if( !silent )
      LOG << _name << ": disabled";

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

      _spi.grab();

      switch( req->_op ) {
         case ENABLE:  _enable      (  (IOReq_ENABLE*)req ); break;
         case DISABLE: _disable     ( (IOReq_DISABLE*)req ); break;
         case READ:    _pageRead    (    (IOReq_READ*)req ); break;
         case SE:      _sectorErase (      (IOReq_SE*)req ); break;
         case BE:      _blockErase  (      (IOReq_BE*)req ); break;
         case PP:      _pageWrite   (      (IOReq_PP*)req ); break;
      }

      _spi.release();

      (void)xTaskNotifyGive( req->_handle );
   }
}


void A25Lxxx::_enable( IOReq_ENABLE *req )
{
   if( _incRef() > 0 )
      return;

   _spi.enable( req->_silent );
}


void A25Lxxx::_disable( IOReq_DISABLE *req )
{
   if( _decRef() > 0 )
      return;

   _spi.disable( req->_silent );
}


void A25Lxxx::_pageWrite( IOReq_PP *req )
{
   _WREN();
   _PP( req->_addr, req->_x );
   _WRDI();
}


void A25Lxxx::_pageRead( IOReq_READ *req )
{ _READ( req->_addr, req->_x ); }


void A25Lxxx::_sectorErase( IOReq_SE *req )
{
   _WREN();
   _SE( req->_addr );
   _WRDI();
}


void A25Lxxx::_blockErase( IOReq_BE *req )
{
   _WREN();
   _BE( req->_addr );
   _WRDI();
}


void A25Lxxx::_RDID( RDIDResp *rdid )
{
   _select();
   _spi.pollXfer( RDIDCmd, rdid, sizeof( RDIDCmd ));
   _deselect();
}


void A25Lxxx::_READ( uint32_t addr, void *x )
{
   uint8_t cmd[ 4 ];

   cmd[ 0 ] = 0x03;
   cmd[ 1 ] = ( addr >> 16 ) & 0x3f;
   cmd[ 2 ] = ( addr >>  8 ) & 0xff;
   cmd[ 3 ] =   addr         & 0xff;

   _select();
   _spi.pollXfer( cmd, NULL, sizeof( cmd ));
   _spi.read( x, 256 /*req->_len*/ );
   _deselect();
}


void A25Lxxx::_SE( uint32_t addr )
{
   uint8_t cmd[ 4 ];

   cmd[ 0 ] = 0x20;
   cmd[ 1 ] = ( addr >> 16 ) & 0x3f;
   cmd[ 2 ] = ( addr >>  8 ) & 0xf0;
   cmd[ 3 ] =   addr         & 0x00;

   _select();
   _spi.pollXfer( cmd, NULL, sizeof( cmd ));
   _WIPWait( tSE );
   _deselect();
}


void A25Lxxx::_BE( uint32_t addr )
{
   uint8_t cmd[ 4 ];

   cmd[ 0 ] = 0x20;
   cmd[ 1 ] = ( addr >> 16 ) & 0x3f;
   cmd[ 2 ] = ( addr >>  8 ) & 0x00;
   cmd[ 3 ] =   addr         & 0x00;

   _select();
   _spi.pollXfer( cmd, NULL, sizeof( cmd ));
   _WIPWait( tBE );
   _deselect();
}


void A25Lxxx::_PP( uint32_t addr, const void *x )
{
   uint8_t cmd[ 4 ];

   cmd[ 0 ] = 0x02;
   cmd[ 1 ] = ( addr >> 16 ) & 0x3f;
   cmd[ 2 ] = ( addr >>  8 ) & 0xff;
   cmd[ 3 ] =   addr         & 0xff;

   _select();
   _spi.pollXfer( cmd, NULL, sizeof( cmd ));
   _spi.write( x, 256 /*req->_len*/ );
   _deselect();

   _WIPWait( tPP );
}


void A25Lxxx::_WREN( void )
{
   _select();
   _spi.pollXfer( WRENCmd, NULL, sizeof( WRENCmd ));
   _deselect();
}


void A25Lxxx::_WRDI( void )
{
   _select();
   _spi.pollXfer( WRDICmd, NULL, sizeof( WRDICmd ));
   _deselect();
}


void A25Lxxx::_REMS( REMSResp *rems )
{
   _select();
   _spi.pollXfer( REMSCmd, rems, sizeof( REMSCmd ));
   _deselect();
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

   _select();
   _spi.pollXfer( RDSR1Cmd, &rdsr, sizeof( RDSR1Cmd ));

   if( rdsr.sr & 0x01 ) {
      do {
         if( ms > 0 ) delay( ms );
         _spi.pollXfer( &tx, &rx, 1 );
      } while( rx & 0x01 ); // XXX hard limit
   }
   _deselect();
}

/*EoF*/
