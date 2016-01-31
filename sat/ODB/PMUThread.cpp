
#include "devices.h"
#include "PMUThread.h"
#include "Config.h"
#include "system/Application.h"

using namespace qb50;


extern QueueHandle_t evQueue;


#define COEF( x ) ( (float)x )


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

PMUThread::PMUThread()
   : Thread( "Power Monitor", 1, true ),
     _mode( HIGH )
{ ; }


PMUThread::~PMUThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void PMUThread::run( void )
{
   unsigned vbat, tbat,      // tension + temperature batterie
            irx, itx,        // courant global consommé
            i1, i2, i3, i4,  // courant paneaux solaires
            v1, v2, v3, v4;  // tension paneaux solaires

   ADC1.enable( true );
   ADC2.enable( true );
   ADC3.enable( true );
   ADC4.enable( true );

   float dK, dC; // degres (Kelvin/Celsius)

   for( ;; ) {

      _wait(); // wait if suspended

      /*
       * R26 = 2.67K, R8 = 9.09K
       *
       * mV = vbat / 256 * 2048 * (( R26 + R8 ) / R26 )
       *    = vbat * 8 * 4.404494
       *    = vbat * 35.235952
       */

      vbat = ADC1CH7.read();


      /*
       * R58 = 2.67K, R59 = 2.67K, LM335: 10mV / dK
       *
       * dK = tbat / 256 * 2048 * (( R58 + R59 ) / R58 ) / 10
       *    = tbat * 8 * 2 / 10
       *    = tbat * 1.6
       */

      tbat = ADC1CH6.read();
      dK   = 1.6 * COEF( tbat );
      dC   = dK - 273.15;


      /*
       * R1 = 1, ZXCT1084: Vout = 25 * V_R1
       *
       * mA = irx / 256 * 2048 / 25
       *    = irx * 8 / 25
       *    = irx * 0.32
       */

      irx = ADC3CH2.read();


      /*
       * R6 = 0.1, R7 = 0.1
       *
       * 1/Rsense = 1/R6 + 1/R7
       * Rsense = 0.05
       * Vsense = 0.05 * I
       *
       * ZXCT1086: Vout = 50 * Vsense
       *
       * mA = itx / 256 * 2048 / ( 50 * 0.05 )
       *    = itx * 8 / 2.5
       *    = itx * 3.2
       */

      itx = ADC3CH4.read();


      /*
       * R = 0.15, ZXCT1084: Vout = 25 * V_R
       *
       * mA = i[1-4] / 256 * 2048 / ( 25 * 0.15 )
       *    = i[1-4] * 8 / 3.75
       *    = i[1-4] * 32 / 15
       */

      i1 = ADC1CH5.read();
      i2 = ADC2CH2.read();
      i3 = ADC2CH5.read();
      i4 = ADC1CH1.read();

      v1 = ADC1CH3.read();
      v2 = ADC2CH0.read();
      v3 = ADC2CH3.read();
      v4 = ADC1CH0.read();


      /* conversions */

      SAT.maI[ 0 ] = COEF(   i1 ) * 32.0 / 15.0;
      SAT.mvV[ 0 ] = COEF(   v1 ) * 35.235952;

      SAT.maI[ 1 ] = COEF(   i2 ) * 32.0 / 15.0;
      SAT.mvV[ 1 ] = COEF(   v2 ) * 35.235952;

      SAT.maI[ 2 ] = COEF(   i3 ) * 32.0 / 15.0;
      SAT.mvV[ 2 ] = COEF(   v3 ) * 35.235952;

      SAT.maI[ 3 ] = COEF(   i4 ) * 32.0 / 15.0;
      SAT.mvV[ 3 ] = COEF(   v4 ) * 35.235952;

      SAT.maIRx    = COEF(  irx ) * 0.32;
      SAT.maITx    = COEF(  itx ) * 3.20;
      SAT.mvBat    = COEF( vbat ) * 35.235952;

      SAT.dcBat    = dC;

      /* check battery voltage */

      float vobs = 35.235952 * COEF( v4 );
      float vmin = 5300.0 + ( 100 * CONF.getParam( Config::PARAM_VBAT_LOW  ));
      float vmax = 6300.0 + ( 100 * CONF.getParam( Config::PARAM_VBAT_HIGH ));

      if( vobs <= vmax ) {
         if( vobs <= vmin ) {
            if( _mode != LOW ) {
               Event *ev = new Event( Event::VBAT_LOW );
               xQueueSendToBack( evQueue, &ev, portMAX_DELAY );
               _mode = LOW;
            }
         }
      } else {
         if( _mode != HIGH ) {
            Event *ev = new Event( Event::VBAT_HIGH );
            xQueueSendToBack( evQueue, &ev, portMAX_DELAY );
            _mode = HIGH;
         }
      }

      delay( 500 );
   }
}

/*EoF*/
