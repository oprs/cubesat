
#include "device/MAX111x.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

MAX111x::MAX111x( SPI& spi, const char *name, GPIO::Pin& csPin )
   : ADC( name ), SPISlave( spi, csPin, SPISlave::ActiveLow )
{ ; }


MAX111x::~MAX111x()
{ ; }


//  - - - - - - - - - - - - - - -  //
//  C H A N N E L   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

MAX111x::Channel&
MAX111x::Channel::init( void )
{
 //_adc.init();
   return *this;
}


MAX111x::Channel&
MAX111x::Channel::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

 //_adc.enable( silent )
   MAX111x& adc = static_cast<MAX111x&>( _adc );
   adc.enable( silent );

   return *this;
}


MAX111x::Channel&
MAX111x::Channel::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

 //_adc.disable( silent )
   MAX111x& adc = static_cast<MAX111x&>( _adc );
   adc.disable( silent );

   return *this;
}


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

MAX111x& MAX111x::init( void )
{
   (void)SPISlave::init();

   LOG << _name << ": Onboard MAX111x serial ADC at " << _spi.name()
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

   _spi.pollXfer( ConvCmd, ConvRes, sizeof( ConvCmd ));

   return
      (( ConvRes[2] << 8 ) | ConvRes[3] ) >> 6;
}

/*EoF*/
