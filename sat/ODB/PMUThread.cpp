
#include "devices.h"
#include "PMUThread.h"
#include "Modem1200.h"
#include "Config.h"
#include "Event.h"
#include "WodStore.h"
#include "system/Application.h"

using namespace qb50;


extern QueueHandle_t evQueue;

#define STEADY 2.0


static const char* chNames[] = {

   /*  0 */ "V4",
   /*  1 */ "I4",
   /*  2 */ "T4",
   /*  3 */ "V1",
   /*  4 */ "T1",
   /*  5 */ "I1",
   /*  6 */ "T_Bat",
   /*  7 */ "V_Bat",

   /*  8 */ "V2",
   /*  9 */ "T2",
   /* 10 */ "I2",
   /* 11 */ "V3",
   /* 12 */ "T3",
   /* 13 */ "I3",
   /* 14 */ "I_Surt",
   /* 15 */ "X0",

   /* 16 */ "I_ADCS",
   /* 17 */ "T_ARM",
   /* 18 */ "I_RX",
   /* 19 */ "RSSI",
   /* 20 */ "I_TX",
   /* 21 */ "P_TX",
   /* 22 */ "P_PA",
   /* 23 */ "T_PA",

   /* 24 */ "X1",
   /* 25 */ "I_GPS",
   /* 26 */ "X2",
   /* 27 */ "I_3V3_FIPEX",
   /* 28 */ "V_3V3_FIPEX",
   /* 29 */ "I_5V_FIPEX",
   /* 30 */ "V_5V_FIPEX",
   /* 31 */ "SU_TH_G0",

};


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

PMUThread::PMUThread()
   : Thread( "Monitor", 1, SUSPENDED, 384 /* XXX check with 256 */ ),
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
   unsigned ms, i, n;
   Config::pval_t dt;

   for( n = 0 ;; ++n ) {

      /* wait if suspended */

      _wait();

      /* wait for next cycle */

      dt = CONF.getParam( Config::PARAM_WODEX_CYCLE_TX ) - 1;
      ms = dt >= 0 ? ( 30000 / ( 1 << dt )) : 30000;

      kprintf( "%s: waiting for %.2f sec...\r\n", name, 0.001 * ms );
      delay( ms );

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
         if( _raw[i].stdev > STEADY ) {
/*
            kprintf( RED( "%s: ADC%uCH%u (%s) not steady, stdev: %.2f" ) "\r\n",
                     name,
                     ( i >> 3 ) + 1,
                     ( i & 0x07 ),
                     chNames[i],
                     _raw[i].stdev
            );
*/
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
      WodStore::WEH hdr;
      (void)WOD.write( WodStore::ADC, _raw8, 32, &hdr );

      if( CONF.mode() != Config::TELEM1200 ) {
         M12K.enable();
         M12K.send( &hdr, _raw8 );
         M12K.disable();
      }
#endif

      /* check battery voltage */

      if( _raw[ SAMPLE_V_Bat ].stdev <= STEADY ) {
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

      if( _raw[ SAMPLE_T_PA ].stdev <= STEADY ) {
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
   }
}

/*EoF*/
