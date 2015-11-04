
#include "device/STM32_PWR.h"
#include "device/STM32_RCC.h"
#include "device/STM32_RTC.h"
#include "system/Logger.h"

#include <safe_stm32f4xx.h>

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

STM32_RTC::STM32_RTC( Bus& bus,
                      const uint32_t iobase,
                      const uint32_t periph,
                      const char    *name )
   : Device( name ), BusSlave( bus, iobase, periph )
{ ; }


STM32_RTC::~STM32_RTC()
{ ; }


//  - - - - - - - - - - - - - -  //
//  P U B L I C   M E T H O D S  //
//  - - - - - - - - - - - - - -  //

STM32_RTC& STM32_RTC::init( void )
{
   RTC_TypeDef *RTCx = (RTC_TypeDef*)iobase;

   LOG << _name << ": STM32F4xx Real-Time Clock controller at " << bus.name;

   lock();

// RTC_ReadBackupRegister
//RTC_BKP_DR19
//#define RTC_BKP_DR19                      ((uint32_t)0x00000013)^M

/*
  *          ===================================================================
  *                                   Backup Domain Access
  *          ===================================================================
  *          After reset, the backup domain (RTC registers, RTC backup data
  *          registers and backup SRAM) is protected against possible unwanted
  *          write accesses.
  *          To enable access to the RTC Domain and RTC registers, proceed as follows:
  *            - Enable the Power Controller (PWR) APB1 interface clock using the
  *              RCC_APB1PeriphClockCmd() function.
  *            - Enable access to RTC domain using the PWR_BackupAccessCmd() function.
  *            - Select the RTC clock source using the RCC_RTCCLKConfig() function.
  *            - Enable RTC Clock using the RCC_RTCCLKCmd() function.
*/

   PWR.enable( false );          // enable the power controller
   PWR.enableBKP();              // enable access to backup domain
   RCC.enableRTC( 0x00000200 );  // select the RTC source (LSI) and enable RTC

   RTCx->WPR = 0xca;
   RTCx->WPR = 0x53;

   _enterInit();
   _exitInit();

   RTCx->WPR = 0x00;

   unlock();

   return *this;
}


STM32_RTC& STM32_RTC::enable( bool silent )
{
   if( _incRef() > 0 )
      return *this;

   RTC_TypeDef *RTCx = (RTC_TypeDef*)iobase;

   lock();

   /* see the STM32F4 Ref. Manual sec. 26.3.5 */
   RTCx->WPR = 0xca;
   RTCx->WPR = 0x53;

   if( !silent )
      LOG << _name << ": enabled";

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

   if( !silent )
      LOG << _name << ": disabled";

   unlock();

   return *this;
}


//  - - - - - - - - - - - - - - -  //
//  P R I V A T E   M E T H O D S  //
//  - - - - - - - - - - - - - - -  //

void STM32_RTC::_enterInit( void )
{
   RTC_TypeDef *RTCx = (RTC_TypeDef*)iobase;

   if(( RTCx->ISR & RTC_ISR_INITF ) == 0 ) {
      LOG << _name << ": initializing RTC (hardware reset)";
      RTCx->ISR = (uint32_t)0xffffffff;

//RTC_EnterInitMode
//RTC_INIT_MASK
      for( int cnt = 0 ; cnt < 10000 ; ++cnt ) {
         if(( RTCx->ISR & RTC_ISR_INITF ) != 0 )
            break;
      }

      if(( RTCx->ISR & RTC_ISR_INITF ) != 0 ) {
         LOG << _name << ": success";
      } else {
         LOG << _name << ": failure, ISR: " << RTCx->ISR;
      }
   } else {
      LOG << _name << ": already initialized (software reset)";
   }
}


/**
  * @brief  Exits the RTC Initialization mode.
  * @note   When the initialization sequence is complete, the calendar restarts
  *         counting after 4 RTCCLK cycles.
  * @note   The RTC Initialization mode is write protected, use the
  *         RTC_WriteProtectionCmd(DISABLE) before calling this function.
  * @param  None
  * @retval None
  */

void STM32_RTC::_exitInit( void )
{
   RTC_TypeDef *RTCx = (RTC_TypeDef*)iobase;
   /* Exit Initialization mode */
   RTCx->ISR &= (uint32_t)~RTC_ISR_INIT;
}


/*EoF*/
