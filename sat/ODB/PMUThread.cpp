
#include "devices.h"
#include "PMUThread.h"
#include "Config.h"
#include "Event.h"
#include "WodStore.h"
#include "system/Application.h"

using namespace qb50;


extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

PMUThread::PMUThread()
   : Thread( "Power Monitor", 1, SUSPENDED, 384 /* XXX check with 256 */ ),
     _modeBat( HIGH ),
     _modePA( LOW )
{
   _raw  = new MAX111x::Sample[ 32 ];
   _raw8 = new uint8_t[ 32 ];
   _cur  = 0;
   _rdy  = false;
}


PMUThread::~PMUThread()
{
   delete[] _raw8;
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
   float min, max;

   unsigned i, n;

   for( n = 0 ;; ++n ) {

      /* wait if suspended */

      _wait();

      /* update samples */

      (void)ADC1CH0.read( &_raw[ SAMPLE_V4          ]);
      (void)ADC1CH1.read( &_raw[ SAMPLE_I4          ]);
      (void)ADC1CH2.read( &_raw[ SAMPLE_T4          ]);
      (void)ADC1CH3.read( &_raw[ SAMPLE_V1          ]);
      (void)ADC1CH4.read( &_raw[ SAMPLE_T1          ]);
      (void)ADC1CH5.read( &_raw[ SAMPLE_I1          ]);
      (void)ADC1CH6.read( &_raw[ SAMPLE_T_Bat       ]);
      (void)ADC1CH7.read( &_raw[ SAMPLE_V_Bat       ]);

      (void)ADC2CH0.read( &_raw[ SAMPLE_V2          ]);
      (void)ADC2CH1.read( &_raw[ SAMPLE_T2          ]);
      (void)ADC2CH2.read( &_raw[ SAMPLE_I2          ]);
      (void)ADC2CH3.read( &_raw[ SAMPLE_V3          ]);
      (void)ADC2CH4.read( &_raw[ SAMPLE_T3          ]);
      (void)ADC2CH5.read( &_raw[ SAMPLE_I3          ]);
      (void)ADC2CH6.read( &_raw[ SAMPLE_I_Surt      ]);
      (void)ADC2CH7.read( &_raw[ SAMPLE_X0          ]);

      (void)ADC3CH0.read( &_raw[ SAMPLE_I_ADCS      ]);
      (void)ADC3CH1.read( &_raw[ SAMPLE_T_ARM       ]);
      (void)ADC3CH2.read( &_raw[ SAMPLE_I_RX        ]);
      (void)ADC3CH3.read( &_raw[ SAMPLE_RSSI        ]);
      (void)ADC3CH4.read( &_raw[ SAMPLE_I_TX        ]);
      (void)ADC3CH5.read( &_raw[ SAMPLE_P_TX        ]);
      (void)ADC3CH6.read( &_raw[ SAMPLE_P_PA        ]);
      (void)ADC3CH7.read( &_raw[ SAMPLE_T_PA        ]);

      (void)ADC4CH0.read( &_raw[ SAMPLE_X1          ]);
      (void)ADC4CH1.read( &_raw[ SAMPLE_I_GPS       ]);
      (void)ADC4CH2.read( &_raw[ SAMPLE_X2          ]);
      (void)ADC4CH3.read( &_raw[ SAMPLE_I_3V3_FIPEX ]);
      (void)ADC4CH4.read( &_raw[ SAMPLE_V_3V3_FIPEX ]);
      (void)ADC4CH5.read( &_raw[ SAMPLE_I_5V_FIPEX  ]);
      (void)ADC4CH6.read( &_raw[ SAMPLE_V_5V_FIPEX  ]);
      (void)ADC4CH7.read( &_raw[ SAMPLE_SU_TH_G0    ]);

      for( i = 0 ; i < 32 ; ++i ) {
         if( !_raw[i].steady ) {
            kprintf( RED( "%s: channel %u not steady" ) "\r\n", name, i );
            _raw8[i] = 0;
         } else {
            _raw8[i] = _raw[i].value;
         }
      }

      /* write WOD */

#if 0
      if(( n % 4 /*120*/ ) == 0 ) {
         (void)WOD.write( WodStore::ADC, _raw8, 32 );
      }
#else
      (void)WOD.write( WodStore::ADC, _raw8, 32 );
#endif

      /* check battery voltage */

      if( _raw[ SAMPLE_V_Bat ].steady ) {
         float mvBat = 35.24 * _raw[ SAMPLE_V_Bat ].value;

         min = 5300.0 + ( 100 * CONF.getParam( Config::PARAM_VBAT_LOW  ));
         max = 6300.0 + ( 100 * CONF.getParam( Config::PARAM_VBAT_HIGH ));

         if( mvBat <= max ) {
            if( mvBat <= min ) {
               if( _modeBat != LOW ) {
                  Event *ev = new Event( Event::VBAT_LOW );
kprintf( YELLOW( "%s: V_BAT: %.2fmV (raw: %u)" ) "\r\n", name, mvBat, _raw[ SAMPLE_V_Bat ].value );
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
      }

      /* check PA temperature */

      if( _raw[ SAMPLE_T_PA ].steady ) {
         float dK = 1.6 * _raw[ SAMPLE_T_PA ].value;
         float dC = dK - 273.15;

         min = 60.0 + ( 2 * CONF.getParam( Config::PARAM_PA_TEMP_LOW  ));
         max = 73.0 + ( 2 * CONF.getParam( Config::PARAM_PA_TEMP_HIGH ));

kprintf( "T_PA: %.2fdK - %.2fdC (raw: %u)\r\n", dK, dC, _raw[ SAMPLE_T_PA ].value );

         if( dC <= max ) {
            if( dC <= min ) {
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

      delay( 500 );

   }
}

/*EoF*/
