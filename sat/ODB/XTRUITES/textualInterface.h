/**
 *  textualInterface.h
 *  11/05/2015
 */


#ifndef _QB50_TEXTUAL_INTERFACE_H_
#define _QB50_TEXTUAL_INTERFACE_H_


#include <functional>
#include <vector>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <sstream>

#include "system/qb50.h"

#include "conditionalPrinter.h" // Disable/Enable printf and hexdump
#include "escapeSequences.h"    // ANSI Escape Sequence lib

// Controls
#include "control/textBlock.h"
#include "control/listTextBlock.h"

// Pages
#include "page.h"
#include "pageDirectory/homePage.h"
#include "pageDirectory/colorPalette.h"
#include "pageDirectory/ADCS_test/ADC_TestPage.h"


namespace qb50
{


    class XTRUITESTextBlock;

    /**
     *  @author     Jérôme Skoda    <jerome.skoda@hotmail.fr>
     *  @version    1.2             (29/05/2015 - 02/06/2015)
     */
    class XTRUITESInputHandler
    {


        public:

            uint8_t                 key;

            XTRUITESInputHandler(uint8_t keyVal, std::function<void ()> _handlerVal);

            XTRUITESInputHandler&   setKey(uint8_t keyVal);
            uint8_t                 getKey();
            XTRUITESInputHandler&   setHandler(std::function<void ()> _handlerVal);
            XTRUITESInputHandler&   launch();

        private:

            std::function<void()>   _handler;


    };


    /**
     *  @author     Jérôme Skoda    <jerome.skoda@hotmail.fr>
     *  @version    1.8             (11/05/2015 - 02/06/2015)
     */
    class XTRUITES
    {


        public:

            XTRUITESPage*                       page;
            static bool                         enable;


            XTRUITES(void);
            ~XTRUITES(void);


            XTRUITES&   refresh();
            XTRUITES&   quit();
            XTRUITES&   initialize();


            XTRUITES&   displayDefaultLayout();
            XTRUITES&   displayLocation();
            XTRUITES&   clearContent();


            XTRUITES&   loadPage(XTRUITESPage *newPage);
            bool        readKey(uint8_t key);


    };


} /* namespace: qb50 */


#endif /* _QB50_TEXTUAL_INTERFACE_H_ */


/*EoF*/
