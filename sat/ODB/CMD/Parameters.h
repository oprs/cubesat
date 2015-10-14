
#ifndef _QB50_PARAMETERS_H
#define _QB50_PARAMETERS_H

#define _QB50_NPARAMS 15


namespace qb50 {

   class Parameters
   {

      public:

         Parameters();
         virtual ~Parameters();

         void set( int pnum, long pval );
         long get( int pnum );


      private:

         long pv[ _QB50_NPARAMS ];

   };

} /* qb50 */


#endif /*_QB50_PARAMETERS_H*/

/*EoF*/
