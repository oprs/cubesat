
#include "SPI/MAX111x.h"
#include "system/Logger.h"

using namespace qb50;


static const uint8_t readAllCmd[ 8 * 3 ] = {
   0x8f, 0x00, 0x00,
   0xcf, 0x00, 0x00,
   0x9f, 0x00, 0x00,
   0xdf, 0x00, 0x00,
   0xaf, 0x00, 0x00,
   0xef, 0x00, 0x00,
   0xbf, 0x00, 0x00,
   0xff, 0x00, 0x00
};


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

MAX111x::MAX111x( SPI& spi, const char *name, GPIO::Pin& csPin )
   : SPI_Device( name, spi, csPin, SPI_Device::ActiveLow )
{
   _x = new uint8_t[ 8 * 3 ];
}


MAX111x::~MAX111x()
{
   delete[] _x;
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

MAX111x& MAX111x::init( void )
{
   (void)SPI_Device::init();

   kprintf( "%s: Onboard MAX111x serial ADC, cs: %s\r\n",
            _name, _csPin.name() );

   return *this;
}


MAX111x& MAX111x::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   _spi.enable( silent );

   if( !silent ) {
      kprintf( "%s: enabled\r\n", _name );
   }

   return *this;
}


MAX111x& MAX111x::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   _spi.disable( silent );

   if( !silent ) {
      kprintf( "%s: disabled\r\n", _name );
   }

   return *this;
}


adcval_t MAX111x::read( ADC::Channel& ch )
{
   MAX111x::Channel& maxCh = static_cast<MAX111x::Channel&>( ch );

   uint8_t ConvCmd[ 3 ];
   uint8_t ConvRes[ 3 ];

   ConvCmd[ 0 ] = 0x8f | (( maxCh._id & 0x07 ) << 4 ) ;
   ConvCmd[ 1 ] = 0x00;
   ConvCmd[ 2 ] = 0x00;

   _spi.lock();
   _select();
   _spi.pollXfer( ConvCmd, ConvRes, sizeof( ConvCmd ));
   _deselect();
   _spi.unlock();

   return
      ( ConvRes[1] << 2 ) | ( ConvRes[2] >> 6 );
}


MAX111x& MAX111x::readAll( adcval_t *rvp )
{
   _spi.lock();
   _select();
   _spi.xfer( readAllCmd, _x, sizeof( readAllCmd ));
   _deselect();

   rvp[ 0 ] = ( _x[  1 ] << 2 ) | ( _x[  2 ] >> 6 );
   rvp[ 1 ] = ( _x[  4 ] << 2 ) | ( _x[  5 ] >> 6 );
   rvp[ 2 ] = ( _x[  7 ] << 2 ) | ( _x[  8 ] >> 6 );
   rvp[ 3 ] = ( _x[ 10 ] << 2 ) | ( _x[ 11 ] >> 6 );
   rvp[ 4 ] = ( _x[ 13 ] << 2 ) | ( _x[ 14 ] >> 6 );
   rvp[ 5 ] = ( _x[ 16 ] << 2 ) | ( _x[ 17 ] >> 6 );
   rvp[ 6 ] = ( _x[ 19 ] << 2 ) | ( _x[ 20 ] >> 6 );
   rvp[ 7 ] = ( _x[ 22 ] << 2 ) | ( _x[ 23 ] >> 6 );

   _spi.unlock();

   return *this;
}

/*EoF*/
