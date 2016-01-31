
#include "A25Lxxx/A25Lxxx.h"
#include "system/Application.h"
#include "system/Logger.h"

#define A25Lxxx_HARD_LIMIT 1000

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


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

A25Lxxx::A25Lxxx( SPI& spi, const char *name, GPIO::Pin& csPin )
   : Device( name ), SPISlave( spi, csPin, SPISlave::ActiveLow )
{ ; }


A25Lxxx::~A25Lxxx()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

A25Lxxx& A25Lxxx::init( void )
{
   RDIDResp rdid;

   (void)SPISlave::init();

   /* temporarily (silently) enable the device
    * in order to read its identification ID */

   _spi.lock();
   enable( true /* be quiet */ );

   _RDID( &rdid );

   disable( true /* be quiet */ );
   _spi.unlock();

   /* display ID infos */

   uint16_t  sig  = ( rdid.memType << 8 ) | rdid.memCap;
   A25LChip *chip = chips;

   while(( chip->mask != 0 ) && ( chip->sig != ( sig & chip->mask )))
      ++chip;

   if( chip->mask == 0 ) {
      LOG << _name << ": unknown chip - using default";
      chip = &chips[7];
   }

   _geo.bpc = chip->bpc;
   _geo.spb = chip->spb;
   _geo.pps = chip->pps;
   _geo.bpp = chip->bpp;

   LOG << _name << ": Onboard AMIC " << chip->name
       << " serial flash (" << ( chipSize() >> 17 ) << "Mbit)"
       << ", cs: " << _csPin.name();

   LOG << _name << ": " << _geo.bpc << " blocks * "
                        << _geo.spb << " sectors * "
                        << _geo.pps << " pages * "
                        << _geo.bpp << " bytes";

   return *this;
}


A25Lxxx& A25Lxxx::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

 //_spi.enable( silent );

   if( !silent )
      LOG << _name << ": enabled";

   return *this;
}


A25Lxxx& A25Lxxx::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

 //_spi.disable( silent );

   if( !silent )
      LOG << _name << ": disabled";

   return *this;
}


A25Lxxx& A25Lxxx::pageRead( uint32_t addr, void *x )
{
   _READ( addr, x );
   return *this;
}


A25Lxxx& A25Lxxx::pageWrite( uint32_t addr, const void *x )
{
   _WREN();
   _PP( addr, x );
   return *this;
}


A25Lxxx& A25Lxxx::sectorErase( uint32_t addr )
{
   _WREN();
   _SE( addr );
   return *this;
}


A25Lxxx& A25Lxxx::sectorRead( uint32_t addr, void *x )
{
   uint8_t *dst = (uint8_t*)x;

   for( int i = 0 ; i < _geo.pps ; ++i ) {
      (void)_READ( addr, dst );
      dst  += _geo.bpp;
      addr += _geo.bpp;
   }

   return *this;
}


A25Lxxx& A25Lxxx::sectorWrite( uint32_t addr, const void *x )
{
   const uint8_t *src = (const uint8_t*)x;

   _WREN();
   _SE( addr );

   for( int i = 0 ; i < _geo.pps ; ++i ) {
      _WREN();
      _PP( addr, src );
      src  += _geo.bpp;
      addr += _geo.bpp;
   }

   return *this;
}


A25Lxxx& A25Lxxx::blockErase( uint32_t addr )
{
   _WREN();
   _BE( addr );
   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

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
   _deselect();

   _WIPWait( tSE );
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
   _deselect();

   _WIPWait( tBE );
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

   int n;
   uint8_t rx;
   uint8_t tx = 0xff;

   if( ms > 0 ) {
      delay( ms );
      ms >>= 3;
   }

   _select();
   _spi.pollXfer( RDSR1Cmd, &rdsr, sizeof( RDSR1Cmd ));

   if( rdsr.sr & 0x01 ) {
      for( n = 0 ; n < A25Lxxx_HARD_LIMIT ; ++n ) {
         if( ms > 0 ) delay( ms );
         _spi.pollXfer( &tx, &rx, 1 );
         if( !( rx & 0x01 )) break;
      }

      if( n == A25Lxxx_HARD_LIMIT ) {
         LOG << _name << ": timeout in A25Lxxx::_WIPWait()";
      }
   }
   _deselect();
}

/*EoF*/
