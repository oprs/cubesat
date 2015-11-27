
#include "system/Event.h"

using namespace qb50;


const char *Event::events[] = {
   "GENERIC",
   "AD_SUCCESS", "AD_FAILURE", "VBAT_HIGH",  "VBAT_LOW",   "FORM",
   "(unknown)",  "(unknown)",  "(unknown)",  "(unknown)",  "(unknown)",
   "CMD_1",      "CMD_2",      "CMD_3",      "CMD_4",      "CMD_5",
   "CMD_6",      "CMD_7",      "CMD_8",      "CMD_9",      "CMD_10",
   "CMD_11",     "CMD_12",     "CMD_13",     "CMD_14",     "CMD_15"
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
