
#include "devices.h"
#include "CommandThread.h"
#include "FormParser.h"
#include "Config.h"

using namespace qb50;


extern QueueHandle_t evQueue;


//  - - - - - - - - -  //
//  S T R U C T O R S  //
//  - - - - - - - - -  //

CommandThread::CommandThread()
   : Thread( "Command Handler", 1, true  )
{ ; }


CommandThread::~CommandThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void CommandThread::run( void )
{
   Form *form;

   UART2.enable(); /* XXX UART6 */

   for( ;; ) {

      _wait();

      try {
         form = _parseLine( UART2 /* XXX UART6 */ );
      } catch( const char *e ) {
         LOG << "Exception: " << e;
         continue;
      }

      _wait();

      switch( form->formType ) {
         case Form::FORM_TYPE_C:
         {
            xQueueSendToBack( evQueue, &form, portMAX_DELAY );
            break;
         }

         case Form::FORM_TYPE_H:
         {
            char tmp[ 32 ];

            HForm *hform = (HForm*)form;
            (void)strftime( tmp, 32, "%a, %d %b %Y %T %Z", gmtime( &hform->tv.tv_sec ));
            LOG << "+ H" << hform->tv.tv_sec << " [" << tmp << ']';
            break;
         }

         case Form::FORM_TYPE_P:
         {
            PForm *pform = (PForm*)form;

            if( pform->pid == Config::PARAM_NONE ) {
               LOG << "- P" << pform->pid << " parameter out of bounds";
               break;
            }

            Config::pval_t old = CONF.setParam( pform->pid, pform->pval );

            if( pform->pval == old )
               LOG << "+ P" << pform->pid << ',' << pform->pval << " (unchanged)";
            else
               LOG << "+ P" << pform->pid << ',' << pform->pval << " (was: " << old << ')';

            break;
         }

         case Form::FORM_TYPE_T1:
         {
            T1Form *t1form = (T1Form*)form;
            LOG << "+ T1:";
            LOG << "             Satellite number: " << t1form->sat;
            LOG << "                   Epoch year: " << t1form->eyr;
            LOG << "        Epoch day of the year: " << t1form->edy;
            LOG << "      1st. derivative of mm/2: " << t1form->d1m;
            LOG << "      2nd. derivative of mm/6: " << t1form->d2m;
            LOG << "              BSTAR drag term: " << t1form->bdt;
            break;
         }

         case Form::FORM_TYPE_T2:
         {
            T2Form *t2form = (T2Form*)form;
            LOG << "+ T2:\r\n";
            LOG << "             Satellite number: " << t2form->sat;
            LOG << "        Inclination (degrees): " << t2form->inc;
            LOG << "            R.A.A.N (degrees): " << t2form->ran;
            LOG << "                 Eccentricity: " << t2form->ecc;
            LOG << "    Arg. of perigee (degrees): " << t2form->aop;
            LOG << "       Mean anomaly (degrees): " << t2form->man;
            LOG << "        Mean motion (rev/day): " << t2form->mmo;
            LOG << "    Revolution number @ epoch: " << t2form->rev;
            break;
         }

         default:
            ;
      }

      delete form;
   }
}


Form* CommandThread::_parseLine( UART& uart )
{
   uint8_t x[128];
   size_t i, n;

   n = uart.readLine( x, 128 );

   for( i = 0 ; i < n ; ++i )
      if( x[i] == ':' ) break;

   if( i == n )
      throw( "_parseLine()" );

   ++i;

   return
      FormParser::parse( &x[i], n - i );
}


/*EoF*/
