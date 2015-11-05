
#include "devices.h"
#include "CWThread.h"
#include "Morse.h"
#include "Config.h"
#include "system/Application.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

CWThread::CWThread()
   : Thread( "CW Transmitter", 1, true )
{ ; }


CWThread::~CWThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void CWThread::run( void )
{
   const char *id = SAT.id() == ODB::FR01 ? "FR1" : "FR5";
   unsigned dt;

   Morse cw( PB1 );

   for( ;; ) {
      _wait();  // wait if suspended

      LOG << name << " - " << id;
      cw.write( id );

      dt = CONF.getParam( Config::PARAM_CW_CYCLE_TX );
      dt = ( 10 + 5 * dt ) * 1000;

      delay( dt );
   }
}

/*EoF*/

