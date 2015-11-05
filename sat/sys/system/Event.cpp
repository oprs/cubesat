
#include "system/Event.h"

using namespace qb50;


const char *Event::events[] = {
   "GENERIC",
   "AD_SUCCESS",
   "AD_FAILURE",
   "VBAT_HIGH",
   "VBAT_LOW",
   "FORM"
};


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

Event::Event( Event::event_t type )
   : _type( type )
{ ; }


Event::~Event()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //


/*EoF*/
