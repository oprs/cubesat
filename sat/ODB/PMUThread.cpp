
#include "devices.h"
#include "PMUThread.h"
#include "Config.h"
#include "Event.h"
#include "WodStore.h"
#include "system/Application.h"

using namespace qb50;


extern QueueHandle_t evQueue;


#define DEPTH 5
#define COEF( x ) ( (float)x / DEPTH )


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

PMUThread::PMUThread()
   : Thread( "Power Monitor", 1, SUSPENDED, 384 /* XXX check with 256 */ ),
     _modeBat( HIGH ),
     _modePA( LOW )
{
   _raw = new adcval_t[ 32 * DEPTH ];
   _sum = new adcval_t[ 32 ];
   _cur = 0;
   _rdy = false;
}


PMUThread::~PMUThread()
{
   delete[] _sum;
   delete[] _raw;
}


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void PMUThread::onSuspend( void )
{
   ADC4.disable();
   ADC3.disable();
   ADC2.disable();
   ADC1.disable();
   FCACHE.disable();

   _cur = 0;
   _rdy = false;

   Thread::onSuspend();
}


void PMUThread::onResume( void )
{
   Thread::onResume();

   FCACHE.enable();
   ADC1.enable();
   ADC2.enable();
   ADC3.enable();
   ADC4.enable();
}


void PMUThread::run( void )
{
   float dK, dC; // degres (Kelvin/Celsius)
   float min, max;

   unsigned i, n;

   for( n = 0 ;; ++n ) {

      /* wait if suspended */

      _wait();

      /* update sums */

      adcval_t *v = _raw + 32 * _cur;

      for( i = 0 ; i < 32 ; ++i )
         _sum[ i ] -= v[ i ];

      ADC1.readAll( v      );
      ADC2.readAll( v +  8 );
      ADC3.readAll( v + 16 );
      ADC4.readAll( v + 24 );

      for( i = 0 ; i < 32 ; ++i )
         _sum[ i ] += v[ i ];

      _cur = ( _cur + 1 ) % DEPTH;

      if( _rdy ) {

         /* write WOD */

         uint8_t raw8[ 32 ];

         for( i = 0 ; i < 32 ; ++i )
            raw8[ i ] = (uint8_t)COEF( _sum[ i ] );

         if(( n % 20 /*120*/ ) == 0 ) {
            (void)WOD.write( WodStore::ADC, raw8, sizeof( raw8 ));
         }

         /* conversions */

         SAT.maI[ 0 ] = COEF( _sum[ 5] ) * 32.0 / 15.0;
         SAT.mvV[ 0 ] = COEF( _sum[ 3] ) * 35.235952;

         SAT.maI[ 1 ] = COEF( _sum[10] ) * 32.0 / 15.0;
         SAT.mvV[ 1 ] = COEF( _sum[ 8] ) * 35.235952;

         SAT.maI[ 2 ] = COEF( _sum[13] ) * 32.0 / 15.0;
         SAT.mvV[ 2 ] = COEF( _sum[11] ) * 35.235952;

         SAT.maI[ 3 ] = COEF( _sum[ 1] ) * 32.0 / 15.0;
         SAT.mvV[ 3 ] = COEF( _sum[ 0] ) * 35.235952;

         SAT.maIRx    = COEF( _sum[18] ) * 0.32;
         SAT.maITx    = COEF( _sum[19] ) * 3.20;
         SAT.mvBat    = COEF( _sum[ 7] ) * 35.235952;

         /* battery temperature */

         dK = 1.6 * COEF( _sum[6] );
         dC = dK - 273.15;
         SAT.dcBat = dC;

kprintf( "T_BAT: %d - %.2fdK - %.2fdC\r\n", v[6], dK, dC );

         /* check battery voltage */

         min = 5300.0 + ( 100 * CONF.getParam( Config::PARAM_VBAT_LOW  ));
         max = 6300.0 + ( 100 * CONF.getParam( Config::PARAM_VBAT_HIGH ));

         if( SAT.mvBat <= max ) {
            if( SAT.mvBat <= min ) {
               if( _modeBat != LOW ) {
                  Event *ev = new Event( Event::VBAT_LOW );
                  xQueueSendToBack( evQueue, &ev, portMAX_DELAY );
                  _modeBat = LOW;
               }
            }
         } else {
            if( _modeBat != HIGH ) {
               Event *ev = new Event( Event::VBAT_HIGH );
               xQueueSendToBack( evQueue, &ev, portMAX_DELAY );
               _modeBat = HIGH;
            }
         }

         /* check PA temperature */

         dK = 1.6 * COEF( _sum[23] );
         dC = dK - 273.15;
         SAT.dcPA = dC;

         min = 60.0 + ( 2 * CONF.getParam( Config::PARAM_PA_TEMP_LOW  ));
         max = 73.0 + ( 2 * CONF.getParam( Config::PARAM_PA_TEMP_HIGH ));

kprintf( " T_PA: %d - %.2fdK - %.2fdC\r\n", v[23], dK, dC );

         if( SAT.dcPA <= max ) {
            if( SAT.dcPA <= min ) {
               if( _modePA != LOW ) {
                  Event *ev = new Event( Event::TPA_LOW );
                  xQueueSendToBack( evQueue, &ev, portMAX_DELAY );
                  _modePA = LOW;
               }
            }
         } else {
            if( _modePA != HIGH ) {
               Event *ev = new Event( Event::TPA_HIGH );
               xQueueSendToBack( evQueue, &ev, portMAX_DELAY );
               _modePA = HIGH;
            }
         }
      }

      else {
         if( _cur == 0 ) {
            _rdy = true;
         }
      }

      delay( 500 );
   }
}

/*EoF*/
