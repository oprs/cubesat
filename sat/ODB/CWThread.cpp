
#include "config.h"
#include "CWThread.h"
#include "Morse.h"
#include "system/Application.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

CWThread::CWThread()
   : Thread( "CW Transmitter", 1 )
{ ; }


CWThread::~CWThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void CWThread::run( void )
{
   const char *id = SAT.id() == ODB::FR01 ? "FR1" : "FR5";

   Morse cw( PB1 );

   for( ;; ) {
      LOG << name << " - " << id;
      cw.write( id );
      delay( 30 * 1000 );
   }
}

/*EoF*/

