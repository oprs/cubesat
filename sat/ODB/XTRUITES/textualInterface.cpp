/**
 *  textualInterface.cpp
 *  11/05/2015
 */


#include "textualInterface.h"


using namespace qb50;
using namespace std;


bool XTRUITES::enable= false;

XTRUITESInputHandler::XTRUITESInputHandler(uint8_t keyVal, std::function<void ()> _handlerVal)
{
    key= keyVal;
    _handler= _handlerVal;
}

XTRUITESInputHandler&   XTRUITESInputHandler::setHandler(std::function<void ()> _handlerVal)
{
    _handler= _handlerVal;
    return *this;
}

XTRUITESInputHandler&   XTRUITESInputHandler::setKey(uint8_t keyVal)
{
    key= keyVal;
    return *this;
}

uint8_t XTRUITESInputHandler::getKey()
{
    return key;
}

XTRUITESInputHandler& XTRUITESInputHandler::launch()
{
    _handler();
    return *this;
}



XTRUITES::XTRUITES(void)
{
    initialize();
}


XTRUITES::~XTRUITES(void)
{
    quit();
}


XTRUITES&  XTRUITES::displayDefaultLayout()
{
    escapeSequences::resetAttributes();
    escapeSequences::setBackground(XTRUITES_DEFAULT_BACKGROUND, true);
    escapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND, true);
    escapeSequences::clearScreen();
    escapeSequences::scrollScreen(1, 24);

    /**
     * Write window layout
     */
    escapeSequences::moveCursor(0,0);
    escapeSequences::write("╔══════╡"                                                                            );
    escapeSequences::reversesColors();
    escapeSequences::write(        " XCubeSat Textual Rapid User Interface to Test Embedded Systems "            );
    escapeSequences::reversesColors();
    escapeSequences::write(                                                                        "╞══════╗\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                                                                              ║\r\n" \
                           "║                      ▫ "                                                           );
    escapeSequences::setForeground(XTRUITES_KEY_FOREGROUND, true);
    escapeSequences::write(                         "^H"                                                         );
    escapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND, true);
    escapeSequences::write(                           " Home ▫ "                                                 );
    escapeSequences::setForeground(XTRUITES_KEY_FOREGROUND, true);
    escapeSequences::write(                                   "^R"                                               );
    escapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND, true);
    escapeSequences::write(                                     " Refresh ▫ "                                    );
    escapeSequences::setForeground(XTRUITES_KEY_FOREGROUND, true);
    escapeSequences::write(                                                "^Q"                                  );
    escapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND, true);
    escapeSequences::write(                                                  " Quit ▫                      ║\r\n" \
                           "╟────────┬─────────────────────────────────────────────────────────────────────╢\r\n" \
                           "║00:00:00│                                                                     ║\r\n" \
                           "╚════════╧═════════════════════════════════════════════════════════════════════╝"    );

    return *this;
}


XTRUITES&  XTRUITES::displayLocation()
{
    escapeSequences::setBackground(XTRUITES_DEFAULT_BACKGROUND);

    escapeSequences::moveCursor(10,22);
    escapeSequences::write("                                                        \r\n"); // clear location
    escapeSequences::moveCursor(10,22);

    escapeSequences::setForeground(XTRUITES_LOCATION_FOREGROUND);
    for(char& c : page->getName())
    {
        if(isprint(c))
        {
            escapeSequences::write("%c", c);
        }
        else
        {
            escapeSequences::write(" ");
        }
    }

    escapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND);
    escapeSequences::write(" ■ ");
    escapeSequences::setHomePosition(page->getName().length()+14, 22);
    escapeSequences::moveCursorHome();
    escapeSequences::write("\n");

    return *this;
}






XTRUITES&  XTRUITES::refresh()
{
    page->unload();
    displayDefaultLayout();
    displayLocation();
    page->load();
    return *this;
}


XTRUITES&  XTRUITES::clearContent()
{
    escapeSequences::moveCursor(0, 1);

    // Clear screen
    for(uint8_t line=1; line < 20; line++)
    {
        escapeSequences::erasesEntireCurrentLine();
        escapeSequences::write("║");
        escapeSequences::moveCursor(79, line);
        escapeSequences::write("║\r\n");
    }

    return *this;
}

XTRUITES&  XTRUITES::quit()
{
    page->unload();
    clearContent();
    escapeSequences::resetAttributes();
    escapeSequences::clearScreen();
    escapeSequences::scrollScreen(0, 22);
    escapeSequences::moveCursor(60,23);
    escapeSequences::write("▫ ^T Open XTRUITE ▫");
    escapeSequences::moveCursor(0,0);
    escapeSequences::write("\r\n");

    XTRUITES::enable= false;

    return *this;
}


XTRUITES&  XTRUITES::initialize()
{
    XTRUITES::enable= true;

    displayDefaultLayout();

    // load page
    page= new XTRUITEShomePage ( *this );
    page->load();

    displayLocation();

    return *this;
}

XTRUITES& XTRUITES::loadPage(XTRUITESPage *newPage)
{
    page->unload();
    page= newPage;
    page->load();

    displayLocation();

    return *this;
}




bool XTRUITES::readKey(uint8_t key)
{
    bool actionLaunched= false;

    if(!XTRUITES::enable)
    {
        if(key == 0x14) // ^T
        {
            initialize();
            return true;
        }
        return false;
    }
    else
    {
        actionLaunched |= page->keypress(key);
    }

    // Default actions
    switch(key)
    {
        case 0x11: // ^Q: Quit
            quit();
            actionLaunched= true;
        break;

        case 0x12: // ^R: Refresh
            refresh();
            actionLaunched= true;
        break;

        case 0x08: // ^H: Home
            initialize();
            actionLaunched= true;
        break;
    }
/*
    #if XTRUITES_DEBUG_ENABLED
        escapeSequences::setBackground(XTRUITES_DEFAULT_BACKGROUND);
        escapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND);
        escapeSequences::moveCursor(66, 21);
        escapeSequences::write("┬");
        escapeSequences::moveCursor(66, 22);
        escapeSequences::write("│");
        escapeSequences::moveCursor(66, 23);
        escapeSequences::write("╧");
        escapeSequences::moveCursor(67, 22);
        escapeSequences::write("LastKey=0x%02X", key);
        escapeSequences::moveCursorHome();
        escapeSequences::write("\n");
    #endif*/

    return actionLaunched;
}

/*EoF*/
