
#include "devices.h"
#include "ADCSThread.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

ADCSThread::ADCSThread()
   : Thread( "ADCS Thread", 1, true )
{ ; }


ADCSThread::~ADCSThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void ADCSThread::run( void )
{
	for( ;; ) {
		delay( 2000 );
		LOG << "--------[ ADCS ]--------";
	}
}

/*EoF*/
