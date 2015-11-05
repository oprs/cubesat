
#ifndef _QB50_EVENT_H
#define _QB50_EVENT_H


namespace qb50 {

   class Event
   {

      public:

         enum event_t {
            GENERIC    = 0,  /* generic event                    */
            AD_SUCCESS = 1,  /* antenna deployment (success)     */
            AD_FAILURE = 2,  /* antenna deployment (failure)     */
            VBAT_HIGH  = 3,  /* V_Bat crossed the high threshold */
            VBAT_LOW   = 4,  /* V_Bat crossed the low threshold  */
            FORM       = 5   /* command (form) from the ground   */
         };

         static const char *events[];

         Event( event_t type );
         ~Event();

         event_t type( void ) const
         { return _type; }

         const char *name( void )
         { return Event::events[ _type ]; }


      protected:

         event_t _type;

   };

} /* qb50 */


#endif /*_QB50_EVENT_H*/

/*EoF*/

