
#include "system/qb50.h"
#include "FormParser.h"
#include "Parameters.h"

#include <iostream>

using namespace qb50;

extern QueueHandle_t cmdQueue;


static Form* _parseLine( UART& uart )
{
   uint8_t x[128];
   size_t i, n;

   n = uart.readLine( x, 128 );
   hexdump( x, n );

   for( i = 0 ; i < n ; ++i )
      if( x[i] == ':' ) break;

   if( i == n )
      throw( "_parseLine()" );

   ++i;

   return
      FormParser::parse( &x[i], n - i );
}


void CMDThread( Thread *self )
{
   Form *form;

   (void)self;

   UART6.enable();

   for( ;; ) {
      try {
         form = _parseLine( UART6 );
      } catch( const char *e ) {
         std::cout << "- " << e << "\r\n";
         continue;
      }

      switch( form->type ) {
         case Form::FORM_TYPE_C:
         {
            xQueueSendToBack( cmdQueue, form, portMAX_DELAY );
            break;
         }

         case Form::FORM_TYPE_H:
         {
            char tmp[ 32 ];

            HForm *hform = (HForm*)form;
            (void)strftime( tmp, 32, "%a, %d %b %Y %T %Z", gmtime( &hform->tv.tv_sec ));
            std::cout << "+ H" << hform->tv.tv_sec << " [" << tmp << "]\r\n";
            break;
         }

         case Form::FORM_TYPE_P:
         {
            PForm *pform = (PForm*)form;
            try {
               long was = PARAMS.get( pform->pnum );
               if( pform->pval == was )
                  std::cout << "+ P" << pform->pnum << ',' << pform->pval << " (unchanged)\r\n";
               else
                  std::cout << "+ P" << pform->pnum << ',' << pform->pval << " (was: " << was << ")\r\n";
                  PARAMS.set( pform->pnum, pform->pval );
            } catch( const char *e ) {
               std::cout << "- " << e << "\r\n";
            }
            break;
         }

         case Form::FORM_TYPE_T1:
         {
            T1Form *t1form = (T1Form*)form;
            std::cout << "+ T1:\r\n";
            std::cout << "             Satellite number: " << t1form->sat << "\r\n";
            std::cout << "                   Epoch year: " << t1form->eyr << "\r\n";
            std::cout << "        Epoch day of the year: " << t1form->edy << "\r\n";
            std::cout << "      1st. derivative of mm/2: " << t1form->d1m << "\r\n";
            std::cout << "      2nd. derivative of mm/6: " << t1form->d2m << "\r\n";
            std::cout << "              BSTAR drag term: " << t1form->bdt << "\r\n";
            break;
         }

         case Form::FORM_TYPE_T2:
         {
            T2Form *t2form = (T2Form*)form;
            std::cout << "+ T2:\r\n";
            std::cout << "             Satellite number: " << t2form->sat << "\r\n";
            std::cout << "        Inclination (degrees): " << t2form->inc << "\r\n";
            std::cout << "            R.A.A.N (degrees): " << t2form->ran << "\r\n";
            std::cout << "                 Eccentricity: " << t2form->ecc << "\r\n";
            std::cout << "    Arg. of perigee (degrees): " << t2form->aop << "\r\n";
            std::cout << "       Mean anomaly (degrees): " << t2form->man << "\r\n";
            std::cout << "        Mean motion (rev/day): " << t2form->mmo << "\r\n";
            std::cout << "    Revolution number @ epoch: " << t2form->rev << "\r\n";
            break;
         }

         default:
            ;
      }

      delete form;
   }
}

/*EoF*/
