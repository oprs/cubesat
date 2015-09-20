
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


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

A25Lxxx::A25Lxxx( SPI& spi, const char *name, GPIOPin& csPin )
   : SPIDevice( spi, csPin, SPIDevice::ActiveLow, name )
{ ; }


A25Lxxx::~A25Lxxx()
{ deselect(); }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

A25Lxxx& A25Lxxx::init( void )
{
   LOG << _name << ": Onboard AMIC A25Lxxx (Serial Flash Memory)"
       << " at " << _spi.name() << ", cs: " << _csPin.name()
       << std::flush;

   (void)SPIDevice::init();

#if 0

   uint16_t  sig  = ( rdid.memType << 8 ) | rdid.memCap;
   A25LPart *part = parts;

   while(( part->mask != 0 ) && ( part->sig != ( sig & part->mask )))
      ++part;

   if( part->mask == 0 )
      throw( "unsupported flash chip" ); /* XXX exception... */

/*
   _bpc = part->bpc;
   _ppb = part->ppb;
   _bpp = part->bpp;
*/

   LOG << _name << ": AMIC " << part->name
       << " Onboard serial flash (" << (( part->bpc * part->ppb * part->bpp ) >> 17 ) << "Mbit) at "
       << _spi.name() << ", cs: " << _csPin.name()
       << std::flush;

#else

/*
   LOG << _name << ": AMIC A25L";

   switch( rdid.memType ) {
      case 0x30: LOG << "032";  break;
      case 0x40: LOG << "Q32A"; break;
      default:   LOG << "xxx";  break;
   }

   LOG << " Serial Flash Memory (";

   switch( rdid.memCap ) {
      case 0x16: LOG << "32Mbit";  break;
      default:   LOG << "unknown"; break;
   }

   LOG << ") at " << _spi.name() << ", cs: " << _csPin.name()
       << std::flush;
*/

#endif

   return *this;
}


A25Lxxx& A25Lxxx::RDID( RDIDResp *rdid )
{
   select();
   _spi.pollXfer( RDIDCmd, rdid, sizeof( RDIDCmd ));
   deselect();

   return *this;
}


A25Lxxx& A25Lxxx::REMS( REMSResp *rems )
{
   select();
   _spi.pollXfer( REMSCmd, rems, sizeof( REMSCmd ));
   deselect();

   return *this;
}


A25Lxxx& A25Lxxx::RDSR1( RDSRResp *rdsr )
{
   select();
   _spi.pollXfer( RDSR1Cmd, rdsr, sizeof( RDSR1Cmd ));
   deselect();

   return *this;
}


A25Lxxx& A25Lxxx::RDSR2( RDSRResp *rdsr )
{
   select();
   _spi.pollXfer( RDSR2Cmd, rdsr, sizeof( RDSR2Cmd ));
   deselect();

   return *this;
}


A25Lxxx& A25Lxxx::READ( uint32_t addr, void *x, uint32_t len )
{
   uint8_t READCmd[ 4 ];

   READCmd[ 0 ] = 0x03;
   READCmd[ 1 ] = ( addr >> 16 ) & 0x3f;
   READCmd[ 2 ] = ( addr >>  8 ) & 0xff;
   READCmd[ 3 ] =   addr         & 0xff;

   select();
   _spi.pollXfer( READCmd, NULL, sizeof( READCmd ));
   _spi.read( x, len );
   deselect();

   return *this;
}


A25Lxxx& A25Lxxx::WREN( void )
{
   select();
   _spi.pollXfer( WRENCmd, NULL, sizeof( WRENCmd ));
   deselect();

   return *this;
}


A25Lxxx& A25Lxxx::SE( uint32_t addr )
{
   uint8_t SECmd[ 4 ];

   SECmd[ 0 ] = 0x20;
   SECmd[ 1 ] = ( addr >> 16 ) & 0x3f;
   SECmd[ 2 ] = ( addr >>  8 ) & 0xf0;
   SECmd[ 3 ] =   addr         & 0x00;

   select();
   _spi.pollXfer( SECmd, NULL, sizeof( SECmd ));
   _WIPWait( tSE );
   deselect();

   return *this;
}


A25Lxxx& A25Lxxx::BE( uint32_t addr )
{
   uint8_t BECmd[ 4 ];

   BECmd[ 0 ] = 0x20;
   BECmd[ 1 ] = ( addr >> 16 ) & 0x3f;
   BECmd[ 2 ] = ( addr >>  8 ) & 0x00;
   BECmd[ 3 ] =   addr         & 0x00;

   select();
   _spi.pollXfer( BECmd, NULL, sizeof( BECmd ));
   _WIPWait( tBE );
   deselect();

   return *this;
}


A25Lxxx& A25Lxxx::PP( uint32_t addr, void *x, uint32_t len )
{
   uint8_t PPCmd[ 4 ];

   PPCmd[ 0 ] = 0x02;
   PPCmd[ 1 ] = ( addr >> 16 ) & 0x3f;
   PPCmd[ 2 ] = ( addr >>  8 ) & 0xff;
   PPCmd[ 3 ] =   addr         & 0xff;

   select();
   _spi.pollXfer( PPCmd, NULL, sizeof( PPCmd ));
   _spi.write( x, len );
   _WIPWait( tPP );
   deselect();

   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

A25Lxxx& A25Lxxx::_WIPWait( unsigned ms )
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
      } while( rx & 0x01 );
   }

   return *this;
}

/*EoF*/
