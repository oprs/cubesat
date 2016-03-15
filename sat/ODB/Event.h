
#ifndef _QB50_ODB_EVENT_H
#define _QB50_ODB_EVENT_H

#include "Form.h"


namespace qb50 {

   struct Event
   {

      static const char *events[];

      enum event_t {

         GENERIC     = 0x00,  /* generic event                    */

         AD_SUCCESS  = 0x01,  /* antenna deployment (success)     */
         AD_FAILURE  = 0x02,  /* antenna deployment (failure)     */
         VBAT_HIGH   = 0x03,  /* V_Bat crossed the high threshold */
         VBAT_LOW    = 0x04,  /* V_Bat crossed the low threshold  */
         FORM        = 0x05,  /* command from the ground          */
         WOD_EMPTY   = 0x06,  /* WOD store is empty               */

      };

      Event( event_t type, Form *form = (Form*)0 )
         : type( type ), form( form )
      { ; }

      ~Event()
      {
         if(( type == FORM ) && ( form != 0 ))
            delete form;
      }

      const char *name( void )
      { return events[ type ]; }

      event_t type;
      Form   *form;

   };

} /* qb50 */


#endif /*_QB50_ODB_EVENT_H*/

/*EoF*/
