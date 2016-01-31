
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

static const char *alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


static char mvCode( unsigned mv )
{
   if( mv < 6000 ) mv = 5900;
   if( mv > 8400 ) mv = 8400;

   return
      alpha[ ( mv - 5900 ) / 100 ];
}


static char maCode( unsigned ma )
{
   if( ma > 2000 ) ma = 2000;

   return
      alpha[ ma / 100 ];
}

static char dcCode( int dc )
{
   if( dc < -20 ) dc = -25;
   if( dc >  60 ) dc =  60;

   return
      alpha[ ( dc + 25 ) / 5 ];
}


void CWThread::run( void )
{
   char x[8];
   unsigned dt;

   Morse cw( PB1 );

   for( ;; ) {

      _wait();  // wait if suspended

      x[0] = 'F';
      x[1] = 'R';
      x[2] = SAT.id() == ODB::FR01 ? '1' : '5';
      x[3] = ' ';
      x[4] = mvCode( SAT.mvBat );
      x[5] = maCode( SAT.maIRx + SAT.maITx );
      x[6] = maCode( SAT.maI[0] + SAT.maI[1] + SAT.maI[2] + SAT.maI[3] );
      x[7] = dcCode( SAT.dcBat );

#if 1
      LOG << "SAT.mvBat: " << SAT.mvBat;
      LOG << "SAT.maIRx: " << SAT.maIRx;
      LOG << "SAT.maITx: " << SAT.maITx;
      LOG << "SAT.dcBat: " << SAT.dcBat;
#endif
      LOG << name << " - " << x[0] << x[1] << x[2] << x[3] << x[4] << x[5] << x[6] << x[7];

      cw.write( x, 8 );

      dt = CONF.getParam( Config::PARAM_CW_CYCLE_TX );
      dt = ( 10 + 5 * dt ) * 1000;

      delay( dt );
   }
}

/*EoF*/
