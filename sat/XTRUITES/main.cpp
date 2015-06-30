

#include "../XTRUITES/XTRUITES.h"
#include "system/qb50.h"



using namespace std;
using namespace qb50;
using namespace qb50::XTRUITES;

void XTRUITESInputThread(Thread *self )
{
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
    (void)self;

    while(1)
    {
        XTRUITESContainer.action();
        XTRUITESContainer.transition();
    }
}

int main( void )
{
    UART3.enable();

	(void)createThread( "Thread XTRUITE - Machine à états"       , XTRUITES_State_Machine_Thread   );
	(void)createThread( "Thread XTRUITE - Réception des touches" , XTRUITESInputThread             );

	run();

	for( ;; );
}

/*EoF*/
