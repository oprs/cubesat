
#include "devices.h"
#include "PMUThread.h"
#include "Config.h"
#include "WodStore.h"
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

   uint16_t raw[ 32 ];       // 4 ADCs, 8 channels each

 //unsigned dt;

   ADC1.enable( true );
   ADC2.enable( true );
   ADC3.enable( true );
   ADC4.enable( true );

   float dK, dC; // degres (Kelvin/Celsius)

   for( ;; ) {

      int i;

      _wait(); // wait if suspended

      /* read all the channels */

      for( i = 0 ; i < 32 ; ++i )
         raw[ i ] = 0;

      for( i = 0 ; i < 4 ; ++i ) {

         /* ADC1 */

         raw[ 0] += ADC1CH0.read();
         raw[ 1] += ADC1CH1.read();
         raw[ 2] += ADC1CH2.read();
         raw[ 3] += ADC1CH3.read();
         raw[ 4] += ADC1CH4.read();
         raw[ 5] += ADC1CH5.read();
         raw[ 6] += ADC1CH6.read();
         raw[ 7] += ADC1CH7.read();

         /* ADC2 */

         raw[ 8] += ADC2CH0.read();
         raw[ 9] += ADC2CH1.read();
         raw[10] += ADC2CH2.read();
         raw[11] += ADC2CH3.read();
         raw[12] += ADC2CH4.read();
         raw[13] += ADC2CH5.read();
         raw[14] += ADC2CH6.read();
         raw[15] += ADC2CH7.read();

         /* ADC3 */

         raw[16] += ADC3CH0.read();
         raw[17] += ADC3CH1.read();
         raw[18] += ADC3CH2.read();
         raw[19] += ADC3CH3.read();
         raw[20] += ADC3CH4.read();
         raw[21] += ADC3CH5.read();
         raw[22] += ADC3CH6.read();
         raw[23] += ADC3CH7.read();

         /* ADC4 */

         raw[24] += ADC4CH0.read();
         raw[25] += ADC4CH1.read();
         raw[26] += ADC4CH2.read();
         raw[27] += ADC4CH3.read();
         raw[28] += ADC4CH4.read();
         raw[29] += ADC4CH5.read();
         raw[30] += ADC4CH6.read();
         raw[31] += ADC4CH7.read();

      }

      WodStore::ADCEntry *ae = new WodStore::ADCEntry( 0 );

      for( i = 0 ; i < 32 ; ++i ) {
         raw[ i ] >>= 2;
         ae->_raw[ i ] = ( raw[ i ] & 0xff );
      }

      //WOD.write( ae );
      delete ae;

      /*
       * R26 = 2.67K, R8 = 9.09K
       *
       * mV = vbat / 256 * 2048 * (( R26 + R8 ) / R26 )
       *    = vbat * 8 * 4.404494
       *    = vbat * 35.235952
       */

      vbat = raw[7]; /* ADC1CH7 */


      /*
       * R58 = 2.67K, R59 = 2.67K, LM335: 10mV / dK
       *
       * dK = tbat / 256 * 2048 * (( R58 + R59 ) / R58 ) / 10
       *    = tbat * 8 * 2 / 10
       *    = tbat * 1.6
       */

      tbat = raw[6]; /* ADC1CH6 */
      dK   = 1.6 * COEF( tbat );
      dC   = dK - 273.15;


      /*
       * R1 = 1, ZXCT1084: Vout = 25 * V_R1
       *
       * mA = irx / 256 * 2048 / 25
       *    = irx * 8 / 25
       *    = irx * 0.32
       */

      irx = raw[18]; /* ADC3CH2 */


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

      itx = raw[19]; /* ADC3CH4 */


      /*
       * R = 0.15, ZXCT1084: Vout = 25 * V_R
       *
       * mA = i[1-4] / 256 * 2048 / ( 25 * 0.15 )
       *    = i[1-4] * 8 / 3.75
       *    = i[1-4] * 32 / 15
       */

      i1 = raw[ 5]; /* ADC1CH5 */
      i2 = raw[10]; /* ADC2CH2 */
      i3 = raw[13]; /* ADC2CH5 */
      i4 = raw[ 1]; /* ADC1CH1 */

      v1 = raw[ 3]; /* ADC1CH3 */
      v2 = raw[ 8]; /* ADC2CH0 */
      v3 = raw[11]; /* ADC2CH3 */
      v4 = raw[ 0]; /* ADC1CH0 */


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

      float mvMin = 5300.0 + ( 100 * CONF.getParam( Config::PARAM_VBAT_LOW  ));
      float mvMax = 6300.0 + ( 100 * CONF.getParam( Config::PARAM_VBAT_HIGH ));

      if( SAT.mvBat <= mvMax ) {
         if( SAT.mvBat <= mvMin ) {
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
