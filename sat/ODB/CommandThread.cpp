
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
   : Thread( "Command Handler", 1 )
{ ; }


CommandThread::~CommandThread()
{ ; }


//  - - - - - - -  //
//  M E T H O D S  //
//  - - - - - - -  //

void CommandThread::run( void )
{
   Form *form;

   UART6.enable(); /* XXX UART6 */

   for( ;; ) {

      try {
         form = _parseLine( UART6 /* XXX UART6 */ );
      } catch( const char *e ) {
         kprintf( "Exception: %s\r\n", e );
         continue;
      }

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
            kprintf( "+ H %lu [%s]\r\n", hform->tv.tv_sec, tmp );
            break;
         }

         case Form::FORM_TYPE_P:
         {
            PForm *pform = (PForm*)form;

            if( pform->pid == Config::PARAM_NONE ) {
               kprintf( "- P %d parameter out of bounds\r\n", pform->pid );
               break;
            }

            Config::pval_t old = CONF.setParam( pform->pid, pform->pval );

            if( pform->pval == old ) {
               kprintf( "+ P%d,%d (unchanged)\r\n", pform->pid, pform->pval );
            } else {
               kprintf( "+ P%d,%d (was: %d)\r\n", pform->pid, pform->pval, old );
            }

            break;
         }

         case Form::FORM_TYPE_T1:
         {
            T1Form *t1form = (T1Form*)form;
            kprintf( "+ T1:\r\n" );
            kprintf( "             Satellite number: %l\r\n", t1form->sat );
            kprintf( "                   Epoch year: %l\r\n", t1form->eyr );
            kprintf( "        Epoch day of the year: %f\r\n", t1form->edy );
            kprintf( "      1st. derivative of mm/2: %f\r\n", t1form->d1m );
            kprintf( "      2nd. derivative of mm/6: %f\r\n", t1form->d2m );
            kprintf( "              BSTAR drag term: %f\r\n", t1form->bdt );
            break;
         }

         case Form::FORM_TYPE_T2:
         {
            T2Form *t2form = (T2Form*)form;
            kprintf( "+ T2:\r\n" );
            kprintf( "             Satellite number: %l\r\n", t2form->sat );
            kprintf( "        Inclination (degrees): %f\r\n", t2form->inc );
            kprintf( "            R.A.A.N (degrees): %f\r\n", t2form->ran );
            kprintf( "                 Eccentricity: %f\r\n", t2form->ecc );
            kprintf( "    Arg. of perigee (degrees): %f\r\n", t2form->aop );
            kprintf( "       Mean anomaly (degrees): %f\r\n", t2form->man );
            kprintf( "        Mean motion (rev/day): %f\r\n", t2form->mmo );
            kprintf( "    Revolution number @ epoch: %l\r\n", t2form->rev );
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
