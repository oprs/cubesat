
#include "device/A25Lxxx.h"

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
	: SPIDevice( spi, csPin, SPIDevice::ActiveLow )
{ ; }


A25Lxxx::~A25Lxxx()
{ deselect(); }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

A25Lxxx& A25Lxxx::enable( void )
{
	_spi.enable();
	return *this;
}


A25Lxxx& A25Lxxx::disable( void )
{ return *this; }


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
