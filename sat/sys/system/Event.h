
#ifndef _QB50_EVENT_H
#define _QB50_EVENT_H


namespace qb50 {

   class Event
   {

      public:

         enum EventType {
            BAT_HIGH = 0,
            BAT_LOW  = 1,
            FORM     = 2
         };

         Event( EventType type );
         ~Event();

         EventType type( void ) const
         { return _type; }


      protected:

         EventType _type;

   };

} /* qb50 */


#endif /*_QB50_EVENT_H*/

/*EoF*/

