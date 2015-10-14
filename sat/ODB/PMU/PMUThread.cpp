
#include "config.h"
#include "PMUThread.h"
#include "system/Application.h"

using namespace qb50;

#define ADC_DIRECT 1

#ifdef ADC_DIRECT
   #define NS 1
#else
   #define NS 4
#endif
#define COEF( x ) ( (float)x / NS )


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

PMUThread::PMUThread()
   : Thread( "Power Monitor", 1 )
{ ; }


PMUThread::~PMUThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void PMUThread::run( void )
{
   PMU0.enable();

 //uint8_t channels[ 32 ];

   unsigned vbat, tbat,      // tension + temperature batterie
            irx, itx,        // courant global consommé
            i1, i2, i3, i4,  // courant paneaux solaires
            v1, v2, v3, v4;  // tension paneaux solaires

   float dK, dC;        // degres (Kelvin/Celsius)

   for( ;; ) {

      PMU0.update( NS );

      /*
       * R26 = 2.67K, R8 = 9.09K
       *
       * mV = vbat / 256 * 2048 * (( R26 + R8 ) / R26 )
       *    = vbat * 8 * 4.404494
       *    = vbat * 35.235952
       */

#ifdef ADC_DIRECT
      vbat = ADC1.readChannel( MAX111x::CH7 );
#else
      vbat = PMU0.get( PMU::V_BAT );
#endif
      LOG << "VBAT: " << vbat << " (" << 35.235952 * COEF( vbat ) << "mV)";


      /*
       * R58 = 2.67K, R59 = 2.67K, LM335: 10mV / dK
       *
       * dK = tbat / 256 * 2048 * (( R58 + R59 ) / R58 ) / 10
       *    = tbat * 8 * 2 / 10
       *    = tbat * 1.6
       */

#ifdef ADC_DIRECT
      tbat = ADC1.readChannel( MAX111x::CH6 );
#else
      tbat = PMU0.get( PMU::T_BAT );
#endif
      dK = 1.6 * COEF( tbat );
      dC = dK - 273.15;
      LOG << "TBAT: " << tbat << " (" << dK << "K|" << dC << "C)";


      /*
       * R1 = 1, ZXCT1084: Vout = 25 * V_R1
       *
       * mA = irx / 256 * 2048 / 25
       *    = irx * 8 / 25
       *    = irx * 0.32
       */

#ifdef ADC_DIRECT
      irx = ADC3.readChannel( MAX111x::CH2 );
#else
      irx = PMU0.get( PMU::I_RX );
#endif
      LOG << " IRX: " << irx << " (" << 0.32 * COEF( irx ) << "mA)";


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

#ifdef ADC_DIRECT
      itx = ADC3.readChannel( MAX111x::CH4 );
#else
      itx = PMU0.get( PMU::I_TX );
#endif
      LOG << " ITX: " << itx << " (" << 3.2 * COEF( itx ) << "mA)";


      /*
       * R = 0.15, ZXCT1084: Vout = 25 * V_R
       *
       * mA = i[1-4] / 256 * 2048 / ( 25 * 0.15 )
       *    = i[1-4] * 8 / 3.75
       *    = i[1-4] * 32 / 15
       */

#ifdef ADC_DIRECT
      i1 = ADC1.readChannel( MAX111x::CH5 );
      i2 = ADC2.readChannel( MAX111x::CH2 );
      i3 = ADC2.readChannel( MAX111x::CH5 );
      i4 = ADC1.readChannel( MAX111x::CH1 );
#else
      i1 = PMU0.get( PMU::I1 );
      i2 = PMU0.get( PMU::I2 );
      i3 = PMU0.get( PMU::I3 );
      i4 = PMU0.get( PMU::I4 );
#endif

#ifdef ADC_DIRECT
      v1 = ADC1.readChannel( MAX111x::CH3 );
      v2 = ADC2.readChannel( MAX111x::CH0 );
      v3 = ADC2.readChannel( MAX111x::CH3 );
      v4 = ADC1.readChannel( MAX111x::CH0 );
#else
      v1 = PMU0.get( PMU::V1 );
      v2 = PMU0.get( PMU::V2 );
      v3 = PMU0.get( PMU::V3 );
      v4 = PMU0.get( PMU::V4 );
#endif

      LOG << "  I1: " << i1 << " (" << 32.0 * COEF( i1 ) / 15.0 << "mA)"
          << ", V1: " << v1 << " (" << 35.235952 * COEF( v1 ) << "mV)";

      LOG << "  I2: " << i2 << " (" << 32.0 * COEF( i2 ) / 15.0 << "mA)"
          << ", V2: " << v2 << " (" << 35.235952 * COEF( v2 ) << "mV)";

      LOG << "  I3: " << i3 << " (" << 32.0 * COEF( i3 ) / 15.0 << "mA)"
          << ", V3: " << v3 << " (" << 35.235952 * COEF( v3 ) << "mV)";

      LOG << "  I4: " << i4 << " (" << 32.0 * COEF( i4 ) / 15.0 << "mA)"
          << ", V4: " << v4 << " (" << 35.235952 * COEF( v4 ) << "mV)";

      delay( 30 * 1000 );
   }
}

/*EoF*/
