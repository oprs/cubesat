
#ifndef _QB50_ODB_EVENT_H
#define _QB50_ODB_EVENT_H


namespace qb50 {

   struct Event
   {

      static const char *events[];

      enum event_t {

         GENERIC     = 0,  /* generic event                    */

         AD_SUCCESS  = 1,  /* antenna deployment (success)     */
         AD_FAILURE  = 2,  /* antenna deployment (failure)     */
         VBAT_HIGH   = 3,  /* V_Bat crossed the high threshold */
         VBAT_LOW    = 4,  /* V_Bat crossed the low threshold  */
         FORM        = 5,  /* command (form) from the ground   */

      };

      Event( event_t type )
         : type( type )
      { ; }

      ~Event()
      { ; }

      const char *name( void )
      { return events[ type ]; }

      event_t type;

   };

} /* qb50 */


#endif /*_QB50_ODB_EVENT_H*/

/*EoF*/
