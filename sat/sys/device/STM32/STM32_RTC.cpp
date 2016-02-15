
#include "STM32/STM32_PWR.h"
#include "STM32/STM32_RCC.h"
#include "STM32/STM32_RTC.h"
#include "STM32/STM32_BKP.h"
#include "system/Logger.h"

#include <safe_stm32f4xx.h>

#define RTC_HARD_LIMIT 100000

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

STM32_RTC::STM32_RTC( Bus& bus,
                      const uint32_t iobase,
                      const uint32_t periph,
                      const char    *name )
   : STM32_Device( name, bus, iobase, periph )
{ ; }


STM32_RTC::~STM32_RTC()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

STM32_RTC& STM32_RTC::init( void )
{
#if 0
   RTC_TypeDef *RTCx = (RTC_TypeDef*)iobase;

   lock();

   PWR.enable( false );          // enable the power controller
   PWR.enableBKP();              // enable access to backup domain
   RCC.enableRTC( 0x00000200 );  // select the RTC source (LSI) and enable RTC

   RTCx->WPR = 0xca;
   RTCx->WPR = 0x53;

   _enterInit();
   _exitInit();

   RTCx->WPR = 0x00;

   unlock();
#endif

   kprintf( "%s: STM32F4xx Real-Time Clock controller at %s\r\n", _name, bus.name );

   return *this;
}


STM32_RTC& STM32_RTC::enable( bool silent )
{
   Time t;
   int  n;

   if( _incRef() > 0 )
      return *this;

   lock();

   PWR.enable( silent );         // enable the power controller
   PWR.enableBKP();              // enable access to backup domain
   BKP.enable( silent );

//RCC_LSICmd

   //RCC.enable( this, silent );
   RCC.enableRTC( 0x00000200 );  // select the RTC source (LSI) and enable RTC

   RTC_TypeDef *RTCx = (RTC_TypeDef*)iobase;

   if(( RTCx->ISR & RTC_ISR_INITS ) == 0 ) {
      kprintf( "%s: calendar not initialized\r\n", _name );
   } else {
      kprintf( "%s: calendar already initialized\r\n", _name );
   }

   /* see the STM32F4 Ref. Manual sec. 26.3.5 */

   RTCx->WPR = 0xca;
   RTCx->WPR = 0x53;

   /* init sequence */

   RTCx->ISR |= (uint32_t)RTC_ISR_INIT;

   for( n = 0 ; n < RTC_HARD_LIMIT ; ++n ) {
      if(( RTCx->ISR & RTC_ISR_INITF ) != 0 )
         break;
   }

   if(( RTCx->ISR & RTC_ISR_INITF ) == 0 ) {
      kprintf( RED( "%s: timeout while waiting for RTC_ISR_INITF" ) "\r\n", _name );
   }

   /* set prescaler to 32678 */

   RTCx->PRER |= 0x000000ff; /*  synchronous prescaler */
   RTCx->PRER |= 0x007f0000; /* asynchronous prescaler */

   /* set calendar */

   ;

   /* exit init mode */

   RTCx->ISR &= (uint32_t)~RTC_ISR_INIT;

   /* lock RTC registers */

   RTCx->WPR = 0xff;

   //RTC->CR   = 0x00;

   /* - */

   (void)getTime( t );

   kprintf( "%s: date is %04d-%02d-%02d (YYYY-MM-DD)\r\n", _name, t.year, t.mon, t.day );
   kprintf( "%s: time is %02d:%02d:%02d (hh:mm:ss)\r\n", _name, t.hour, t.min, t.sec );

   unlock();

   return *this;
}


STM32_RTC& STM32_RTC::disable( bool silent )
{
   if( _decRef() > 0 )
      return *this;

   RTC_TypeDef *RTCx = (RTC_TypeDef*)iobase;

   lock();

   RTCx->WPR = 0x00;

   RCC.disable( this, silent );

   unlock();

   return *this;
}


STM32_RTC& STM32_RTC::getTime( Time &t )
{
   int n;

   RTC_TypeDef *RTCx = (RTC_TypeDef*)iobase;

   for( n = 0 ; n < RTC_HARD_LIMIT ; ++n ) {
      if(( RTCx->ISR & RTC_ISR_RSF ) != 0 )
         break;
   }

   if(( RTCx->ISR & RTC_ISR_RSF ) == 0 ) {
      kprintf( RED( "%s: timeout in STM32_RTC::getTime()" ) "\r\n", _name );

      t.year = t.mon = t.day = 0;
      t.hour = t.min = t.sec = 0;

      return *this;
   }

   /*
    * "To ensure consistency between the 3 values, reading either RTC_SSR or
    *  RTC_TR locks the values in the higher-order calendar shadow registers
    *  until RTC_DR is read." -- see Sec. 26.3.6 - "Reading the Calendar"
    */

   uint32_t TR = RTCx->TR;
   uint32_t DR = RTCx->DR;

   t.year = 10 * (( DR >> 20 ) & 0x0f )
               + (( DR >> 16 ) & 0x0f );

   t.mon  = 10 * (( DR >> 12 ) & 0x01 )
               + (( DR >>  8 ) & 0x0f );

   t.day  = 10 * (( DR >>  4 ) & 0x03 )
               + (  DR         & 0x0f );

   t.hour = 10 * (( TR >> 20 ) & 0x03 )
               + (( TR >> 16 ) & 0x0f );

   t.min  = 10 * (( TR >> 12 ) & 0x07 )
               + (( TR >>  8 ) & 0x0f );

   t.sec  = 10 * (( TR >>  4 ) & 0x07 )
               + (  TR         & 0x0f );

   return *this;
}


STM32_RTC& STM32_RTC::setTime( Time &t )
{
   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

void STM32_RTC::_enterInit( void )
{
   RTC_TypeDef *RTCx = (RTC_TypeDef*)iobase;

   if(( RTCx->ISR & RTC_ISR_INITF ) == 0 ) {
      kprintf( "%s: initializing RTC (hardware reset)\r\n", _name );
      RTCx->ISR = (uint32_t)0xffffffff;

      for( int cnt = 0 ; cnt < 10000 ; ++cnt ) {
         if(( RTCx->ISR & RTC_ISR_INITF ) != 0 )
            break;
      }

      if(( RTCx->ISR & RTC_ISR_INITF ) != 0 ) {
         kprintf( "%s: success\r\n", _name );
      } else {
         kprintf( "%s: failure, ISR: 0x%08lx\r\n", _name, RTCx->ISR );
      }
   } else {
      kprintf( "%s: already initialized (software reset)\r\n", _name );
   }
}


void STM32_RTC::_exitInit( void )
{
   RTC_TypeDef *RTCx = (RTC_TypeDef*)iobase;
   RTCx->ISR &= (uint32_t)~RTC_ISR_INIT;
}


/*EoF*/
