
#include "MAX111x/MAX111x.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

MAX111x::MAX111x( SPI& spi, const char *name, GPIO::Pin& csPin )
   : Device( name ), SPISlave( spi, csPin, SPISlave::ActiveLow )
{ ; }


MAX111x::~MAX111x()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

MAX111x& MAX111x::init( void )
{
   (void)SPISlave::init();

   LOG << _name << ": Onboard MAX111x serial ADC"
       << ", cs: " << _csPin.name();

   return *this;
}


MAX111x& MAX111x::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   _spi.enable( silent );

   if( !silent )
      LOG << _name << ": enabled";

   return *this;
}


MAX111x& MAX111x::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   _spi.disable( silent );

   if( !silent )
      LOG << _name << ": disabled";

   return *this;
}


adcval_t MAX111x::read( ADC::Channel& ch )
{
   MAX111x::Channel& maxCh = static_cast<MAX111x::Channel&>( ch );

   uint8_t ConvCmd[ 4 ];
   uint8_t ConvRes[ 4 ];

   ConvCmd[ 0 ] = 0x00;
   ConvCmd[ 1 ] = 0x8f | (( maxCh._id & 0x07 ) << 4 ) ;
   ConvCmd[ 2 ] = 0x00;
   ConvCmd[ 3 ] = 0x00;

   _spi.lock();
   _select();
   _spi.pollXfer( ConvCmd, ConvRes, sizeof( ConvCmd ));
   _deselect();
   _spi.unlock();

   return
      (( ConvRes[2] << 8 ) | ConvRes[3] ) >> 6;
}

/*EoF*/
