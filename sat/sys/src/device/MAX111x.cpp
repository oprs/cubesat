
#include "device/MAX111x.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

MAX111x::MAX111x( SPI& spi, const char *name, GPIO::Pin& csPin )
   : ADC( name ), SPISlave( spi, csPin, SPISlave::ActiveLow )
{
   _ioQueue = xQueueCreate( 1, sizeof( IOReq* ));
}


MAX111x::~MAX111x()
{ vQueueDelete( _ioQueue ); }


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
   (void)ADC::init();

   LOG << _name << ": Onboard MAX111x serial ADC at " << _spi.name()
       << ", cs: " << _csPin.name();

   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

void MAX111x::_enable( IOReq_enable *req )
{
   if( _incRef() > 0 )
      return;

   _spi.enable( req->_silent );

   if( !req->_silent )
      LOG << _name << ": enabled";
}


void MAX111x::_disable( IOReq_disable *req )
{
   if( _decRef() > 0 )
      return;

   _spi.disable( req->_silent );

   if( !req->_silent )
      LOG << _name << ": disabled";
}


void MAX111x::_read( IOReq_read *req )
{
   MAX111x::Channel& ch = static_cast<MAX111x::Channel&>( req->_ch );

   uint8_t ConvCmd[ 4 ];
   uint8_t ConvRes[ 4 ];

   ConvCmd[ 0 ] = 0x00;
   ConvCmd[ 1 ] = 0x8f | (( ch._id & 0x07 ) << 4 ) ;
   ConvCmd[ 2 ] = 0x00;
   ConvCmd[ 3 ] = 0x00;

   _spi.pollXfer( ConvCmd, ConvRes, sizeof( ConvCmd ));

   req->_rv = (( ConvRes[2] << 8 ) | ConvRes[3] ) >> 6;
}

/*EoF*/
