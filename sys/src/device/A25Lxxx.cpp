
#include "device/A25Lxxx.h"

using namespace qb50;


/*
 * 64 blocks
 * 64 blocks * 16 sectors/block = 1024 sectors
 * 64 blocks * 16 sectors/block * 16 pages/sector = 16384 pages
 * 64 blocks * 16 secrots/block * 16 pages/sector * 256 bytes/page = 4194304 bytes
 */


/* SPI commands */

static const uint8_t RDIDCmd[]  = { 0x9f, 0xff, 0xff, 0xff };
static const uint8_t REMSCmd[]  = { 0x90, 0xff, 0xff, 0x00, 0xff, 0xff };
static const uint8_t RDSR1Cmd[] = { 0x05, 0xff };
static const uint8_t RDSR2Cmd[] = { 0x35, 0xff };
static const uint8_t WRENCmd[]  = { 0x06 };


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

A25Lxxx::A25Lxxx( SPI& spi, GPIOPin& csPin )
   : _spi( spi ), _csPin( csPin )
{ ; }


A25Lxxx::~A25Lxxx()
{ disable(); }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

A25Lxxx& A25Lxxx::enable( void )
{
   _csPin.enable()
         .pullUp()
         .out();

   _spi.enable();

   return *this;
}


A25Lxxx& A25Lxxx::disable( void )
{
   _csPin.disable();
   //_spi.disable();

   return *this;
}


A25Lxxx& A25Lxxx::RDID( RDIDResp *rdid )
{
   _csPin.off();
   _spi.xfer( RDIDCmd, rdid, sizeof( RDIDCmd ));
   _csPin.on();

   return *this;
}


A25Lxxx& A25Lxxx::REMS( REMSResp *rems )
{
   _csPin.off();
   _spi.xfer( REMSCmd, rems, sizeof( REMSCmd ));
   _csPin.on();

   return *this;
}


A25Lxxx& A25Lxxx::RDSR1( RDSRResp *rdsr )
{
   _csPin.off();
   _spi.xfer( RDSR1Cmd, rdsr, sizeof( RDSR1Cmd ));
   _csPin.on();

   return *this;
}


A25Lxxx& A25Lxxx::RDSR2( RDSRResp *rdsr )
{
   _csPin.off();
   _spi.xfer( RDSR2Cmd, rdsr, sizeof( RDSR2Cmd ));
   _csPin.on();

   return *this;
}


A25Lxxx& A25Lxxx::READ( uint32_t addr, void *x, uint32_t len )
{
   uint8_t READCmd[ 4 ];

   READCmd[ 0 ] = 0x03;
   READCmd[ 1 ] = ( addr >> 16 ) & 0x3f;
   READCmd[ 2 ] = ( addr >>  8 ) & 0xff;
   READCmd[ 3 ] =   addr         & 0xff;

   _csPin.off();
   _spi.write( READCmd, sizeof( READCmd ));
   _spi.read( x, len );
   _csPin.on();

   return *this;
}


A25Lxxx& A25Lxxx::WREN( void )
{
   _csPin.off();
   _spi.write( WRENCmd, sizeof( WRENCmd ));
   _csPin.on();

   return *this;
}


A25Lxxx& A25Lxxx::SE( uint32_t addr )
{
   uint8_t SECmd[ 4 ];

   SECmd[ 0 ] = 0x20;
   SECmd[ 1 ] = ( addr >> 16 ) & 0x3f;
   SECmd[ 2 ] = ( addr >>  8 ) & 0xf0;
   SECmd[ 3 ] =   addr         & 0x00;

   _csPin.off();
   _spi.write( SECmd, sizeof( SECmd ));
   _csPin.on();

   return *this;
}


A25Lxxx& A25Lxxx::BE( uint32_t addr )
{
   uint8_t BECmd[ 4 ];

   BECmd[ 0 ] = 0x20;
   BECmd[ 1 ] = ( addr >> 16 ) & 0x3f;
   BECmd[ 2 ] = ( addr >>  8 ) & 0x00;
   BECmd[ 3 ] =   addr         & 0x00;

   _csPin.off();
   _spi.write( BECmd, sizeof( BECmd ));
   _csPin.on();

   return *this;
}


A25Lxxx& A25Lxxx::PP( uint32_t addr, void *x, uint32_t len )
{
   uint8_t PPCmd[ 4 ];

   PPCmd[ 0 ] = 0x02;
   PPCmd[ 1 ] = ( addr >> 16 ) & 0x3f;
   PPCmd[ 2 ] = ( addr >>  8 ) & 0xff;
   PPCmd[ 3 ] =   addr         & 0xff;

   _csPin.off();
   _spi.write( PPCmd, sizeof( PPCmd ));
   _spi.write( x, len );
   _csPin.on();

   return *this;
}

/*EoF*/
