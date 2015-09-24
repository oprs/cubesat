
#ifndef _QB50_EVENT_H
#define _QB50_EVENT_H


namespace qb50 {

   class Event
   {

      public:

         enum EventType {
            BAT_HIGH = 0,
            BAT_LOW  = 1,
            CMD      = 2
         };

         Event( EventType type );
         ~Event();


      protected:

         EventType _type;

   };

} /* qb50 */


#endif /*_QB50_EVENT_H*/

/*EoF*/

