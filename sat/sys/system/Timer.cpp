
#include "system/Timer.h"

using namespace qb50;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Timer::Timer()
{
   _incr = 0;
   _prev = 0;
}


Timer::~Timer()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

Timer& Timer::every( unsigned ms )
{
   if( ms > portMAX_DELAY ) {
      ms = portMAX_DELAY;
   }

   if( _prev == 0 ) {
      _prev = ::xTaskGetTickCount();
   }

   _incr = (TickType_t)ms / portTICK_RATE_MS;

   (void)::vTaskDelayUntil( &_prev, _incr );

   return *this;
}


/*EoF*/
