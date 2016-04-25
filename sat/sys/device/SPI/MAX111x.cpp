
#include "SPI/MAX111x.h"
#include "system/Logger.h"

#include <math.h>


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

static const uint8_t read4Cmd1[ 8 * 12 ] = {
   0x8f, 0x00, 0x00,  0x8f, 0x00, 0x00,  0x8f, 0x00, 0x00,  0x8f, 0x00, 0x00,
   0xcf, 0x00, 0x00,  0xcf, 0x00, 0x00,  0xcf, 0x00, 0x00,  0xcf, 0x00, 0x00,
   0x9f, 0x00, 0x00,  0x9f, 0x00, 0x00,  0x9f, 0x00, 0x00,  0x9f, 0x00, 0x00,
   0xdf, 0x00, 0x00,  0xdf, 0x00, 0x00,  0xdf, 0x00, 0x00,  0xdf, 0x00, 0x00,
   0xaf, 0x00, 0x00,  0xaf, 0x00, 0x00,  0xaf, 0x00, 0x00,  0xaf, 0x00, 0x00,
   0xef, 0x00, 0x00,  0xef, 0x00, 0x00,  0xef, 0x00, 0x00,  0xef, 0x00, 0x00,
   0xbf, 0x00, 0x00,  0xbf, 0x00, 0x00,  0xbf, 0x00, 0x00,  0xbf, 0x00, 0x00,
   0xff, 0x00, 0x00,  0xff, 0x00, 0x00,  0xff, 0x00, 0x00,  0xff, 0x00, 0x00,
};

static const uint8_t read4Cmd[ 8 * 12 ] = {
   0x8f, 0x00, 0x00,  0x8f, 0x00, 0x00,  0x8f, 0x00, 0x00,  0x8f, 0x00, 0x00,
   0x9f, 0x00, 0x00,  0x9f, 0x00, 0x00,  0x9f, 0x00, 0x00,  0x9f, 0x00, 0x00,
   0xaf, 0x00, 0x00,  0xaf, 0x00, 0x00,  0xaf, 0x00, 0x00,  0xaf, 0x00, 0x00,
   0xbf, 0x00, 0x00,  0xbf, 0x00, 0x00,  0xbf, 0x00, 0x00,  0xbf, 0x00, 0x00,
   0xcf, 0x00, 0x00,  0xcf, 0x00, 0x00,  0xcf, 0x00, 0x00,  0xcf, 0x00, 0x00,
   0xdf, 0x00, 0x00,  0xdf, 0x00, 0x00,  0xdf, 0x00, 0x00,  0xdf, 0x00, 0x00,
   0xef, 0x00, 0x00,  0xef, 0x00, 0x00,  0xef, 0x00, 0x00,  0xef, 0x00, 0x00,
   0xff, 0x00, 0x00,  0xff, 0x00, 0x00,  0xff, 0x00, 0x00,  0xff, 0x00, 0x00,
};


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

MAX111x::MAX111x( SPI& spi, const char *name, GPIO::Pin& csPin )
   : SPI_Device( name, spi, csPin, SPI_Device::ActiveLow )
{
   _x = new uint8_t[ 12 ];
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


MAX111x& MAX111x::read( ADC::Channel& ch, Sample *sample )
{
   MAX111x::Channel& maxCh = static_cast<MAX111x::Channel&>( ch );
   float v1, v2, v3, v4;
   float tmp, avg, va;

   /* get a burst of 4 samples */

   lock();

   _select();
   _spi.xfer( read4Cmd + 12 * ( maxCh._id & 0x07 ), _x, 12 );
   _deselect();

   /* retrieve raw values */

   v1 = ( _x[  1 ] << 2 ) | ( _x[  2 ] >> 6 );
   v2 = ( _x[  4 ] << 2 ) | ( _x[  5 ] >> 6 );
   v3 = ( _x[  7 ] << 2 ) | ( _x[  8 ] >> 6 );
   v4 = ( _x[ 10 ] << 2 ) | ( _x[ 11 ] >> 6 );

 //kprintf( "v: [ %f %f %f %f ]\r\n", v1, v2, v3, v4 );

   /* compute the standard deviation (avg: average, va: variance) */

   avg = 0.25 * ( v1 + v2 + v3 + v4 );

   tmp = v1 - avg;  va  = tmp * tmp;
   tmp = v2 - avg;  va += tmp * tmp;
   tmp = v3 - avg;  va += tmp * tmp;
   tmp = v4 - avg;  va += tmp * tmp;

   sample->stdev = sqrtf( 0.25 * va );
   sample->value = avg;

   unlock();

   return *this;
}

/*EoF*/
