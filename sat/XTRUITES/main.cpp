#include "system/qb50.h"
#include "XTRUITES.h"

using namespace qb50;
using namespace qb50::XTRUITES;

void XTRUITESInputThread(Thread *self )
{
  // Ne pas faire de printf ou autre fonctions d'écriture
  // Le syscalls ne fonctionne pas!

  (void)self;

  uint8_t keyPress= 0x00;

  while(1)
  {
    UART3.read(&keyPress, 1);
    XTRUITESContainer.pushKey(keyPress);
  }
}


void XTRUITES_State_Machine_Thread(Thread *self )
{
  // Ne pas faire de printf ou autre fonctions d'écriture
  // Le syscalls ne fonctionne pas!

  (void)self;

  while(1)
  {
    XTRUITESContainer.action();
    XTRUITESContainer.transition();
  }
}



int main( void )
{
  // Ne pas faire de printf ou autre fonctions d'écriture
  // Le syscalls ne fonctionne pas!

  UART3.enable();

	/*
	PA0.enable().pullUp().out().on();
	PA4.enable().pullUp().out().on();
	PA5.enable().pullUp().out().on();
	PA6.enable().pullUp().out().on();
	PA7.enable().pullUp().out().on();
	PC4.enable().pullUp().out().on();
	PC10.enable().out().off();
	*/

	(void)createThread( "Thread XTRUITE - Machine à états"       , XTRUITES_State_Machine_Thread   );
	(void)createThread( "Thread XTRUITE - Réception des touches" , XTRUITESInputThread             );

	run();

	for( ;; );
}

/*EoF*/
