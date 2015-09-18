
#include "device/Satellite.h"
#include "system/Logger.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Satellite::Satellite( const char *name,
                      GPIOPin& selPin,
                      GPIOPin& asPin,
                      GPIOPin& adPin )
	: _name( name ),
	  _selPin( selPin ),
	  _asPin( asPin ),
	  _adPin( adPin )
{ ; }


Satellite::~Satellite()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

Satellite& Satellite::enable( void )
{
   _selPin.enable().in().noPull();
   _asPin.enable().in().noPull();
   _adPin.enable().out().off();

   switch( id() ) {

      case Satellite::FR01:
         LOG << "ONFR01 (X-CubeSat - Ecole Polytechnique)" << std::flush;
         break;

      case Satellite::FR05:
         LOG << "ONFR05 (SpaceCube - Mines ParisTech)" << std::flush;
         break;

      default:
         ;
   }

   return *this;
}


Satellite& Satellite::disable( void )
{
   _selPin.disable();

   return *this;
}


Satellite::SatSel Satellite::id( void )
{
	return
		_selPin.read() ? Satellite::FR01 : Satellite::FR05;
}


Satellite::AntState Satellite::aState( void )
{
	return
		_asPin.read() ? Satellite::RETRACTED : Satellite::DEPLOYED;
}


Satellite::AntState Satellite::aDeploy( void )
{
	Satellite::AntState st;

	_adPin.on();

	for( int i = 0 ; i < 3 ; ++i )
	{
		LOG << "Trying to deploy antenna (" << ( i + 1 ) << "/3)..." << std::flush;
		delay( 5000 );

		st = aState();
		if( st == Satellite::DEPLOYED )
			break;
	}

	_adPin.off();

	if( aState() == Satellite::DEPLOYED )
		LOG << "Antenna deployed" << std::flush;
	else
		LOG << "Giving up on antenna deployment" << std::flush;

	return st;
}


/*EoF*/
