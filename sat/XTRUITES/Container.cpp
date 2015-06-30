/**
 *  @file       textualInterface.cpp
 *  @brief      Gestion comportemental de l'interface (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.9
 *  @date       11/05/2015 - 12/06/2015
 */

#include "XTRUITES.h"
#include "Container.h"
#include "EscapeSequences.h"
#include "PageRepertory/Page.h"
#include "PageRepertory/PageRepertory.h"
#include "OutputStream/OutputStreamChannel.h"
#include "OutputStream/OutputStream.h"

using namespace qb50::XTRUITES;


Container::Container(OutputStreamChannel* streamChannelVal) : _inputKey(4)
{
    _state= initialize;

    _pageRepertory= new PageRepertory(this);

    _currentPage= nullptr;
    _nextPage= _pageRepertory->getPageByName("Home");

    _streamChannel= streamChannelVal;
}

PageRepertory* Container::getRepertory( void )
{
    return _pageRepertory;
}

state_t Container::getState()
{
    return _state;
}


void Container::action()
{
    switch(_state)
    {
        case initialize:
            _initialize();
        break;

        case loadPage:
            _loadPage();
        break;

        case updatePage:
            _updatePage();
        break;

        case readKey:
            _readKey();
        break;

        case unloadPage:
            _unloadPage();
        break;

        default:
            _initialize();
    }
}


void Container::transition()
{
    switch(_state)
    {
        case initialize:
            _state= loadPage;
        break;

        case loadPage:
            _state= updatePage;
        break;

        case updatePage:
            _inputKey.lock();
            if(!_inputKey.isEmpty())
            {
                _state= readKey;
            }
            _inputKey.unlock();
        break;

        case readKey:
            if(_nextPage == nullptr)
            {
                _state= updatePage;
            }
            else
            {
                _state= unloadPage;
            }
        break;

        case unloadPage:
            if(_currentPage == _nextPage)
            {
                // Refresh action
                _state= initialize;
            }
            else
            {
                _state= loadPage;
            }
        break;

        default:
            _state= initialize;
    }
}



void Container::_initialize()
{
    // Bloque tous les canaux du OutputStream et active uniquement le canal de XTRUITES
    _streamChannel->getOutputStream()->off();
    _streamChannel->on();

    // Définition des attribus
    EscapeSequences::resetAttributes();
    EscapeSequences::setBackground(XTRUITES_DEFAULT_BACKGROUND, true);
    EscapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND, true);
    EscapeSequences::clearScreen();
    EscapeSequences::scrollScreen(1, XTRUITES_SCREEN_SIZE_HEIGHT);

    // Ecriture du cadre
    EscapeSequences::moveCursor(0,0);
    EscapeSequences::write("╔══════╡"                                                                            );
    EscapeSequences::reversesColors();
    EscapeSequences::write(        " XCubeSat Textual Rapid User Interface to Test Embedded Systems "            );
    EscapeSequences::reversesColors();
    EscapeSequences::write(                                                                        "╞══════╗\r\n" \
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
    EscapeSequences::setForeground(XTRUITES_KEY_FOREGROUND, true);
    EscapeSequences::write(                         "^H"                                                         );
    EscapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND, true);
    EscapeSequences::write(                           " Home ▫ "                                                 );
    EscapeSequences::setForeground(XTRUITES_KEY_FOREGROUND, true);
    EscapeSequences::write(                                   "^R"                                               );
    EscapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND, true);
    EscapeSequences::write(                                     " Refresh ▫ "                                    );
    EscapeSequences::setForeground(XTRUITES_KEY_FOREGROUND, true);
    EscapeSequences::write(                                                "^Q"                                  );
    EscapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND, true);
    EscapeSequences::write(                                                  " Quit ▫                      ║\r\n" \
                           "╟────────┬─────────────────────────────────────────────────────────────────────╢\r\n" \
                           "║00:00:00│                                                                     ║\r\n" \
                           "╚════════╧═════════════════════════════════════════════════════════════════════╝"    );

    return;
}

void Container::_loadPage()
{
    // Flush FIFO
    _inputKey.lock();
    _inputKey.flush();
    _inputKey.unlock();


    _currentPage= _nextPage;
    _nextPage= nullptr;

    displayLocation();

    _currentPage->onLoad();
}

void Container::_updatePage()
{
    _currentPage->onUpdate();
}

void Container::_unloadPage()
{
    _currentPage->onUnload();

    clearContent();
}

void Container::_readKey()
{
    _inputKey.lock();
    uint8_t key= _inputKey.pull();
    _inputKey.unlock();

    _currentPage->onKeyPress(key);

    if(_currentPage->getName() == "Quit")
    {
        if(key == 0x14) // ^T
        {
            _nextPage= _pageRepertory->getPageByName("Home");
        }
        return; // Disable default actions
    }

    // Display last key
    #if XTRUITES_DEBUG_ENABLED
        EscapeSequences::setBackground(XTRUITES_DEFAULT_BACKGROUND);
        EscapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND);
        EscapeSequences::moveCursor(66, 21);
        EscapeSequences::write("┬");
        EscapeSequences::moveCursor(66, 22);
        EscapeSequences::write("│");
        EscapeSequences::moveCursor(66, 23);
        EscapeSequences::write("╧");
        EscapeSequences::moveCursor(67, 22);
        EscapeSequences::write("LastKey=0x%02X", key);
        EscapeSequences::moveCursorHome();
        EscapeSequences::write("\n");
    #endif

    // Default actions
    switch(key)
    {
        case 0x11: // ^Q: Quit
            _nextPage= _pageRepertory->getPageByName("Quit");
        break;

        case 0x12: // ^R: Refresh
            _nextPage= _currentPage;
        break;

        case 0x08: // ^H: Home
            _nextPage= _pageRepertory->getPageByName("Home");
        break;
    }
}





void Container::displayLocation()
{
    EscapeSequences::setBackground(XTRUITES_DEFAULT_BACKGROUND);

    // clear location
    EscapeSequences::moveCursor(10,22);
    EscapeSequences::write("                                                        \r\n");
    EscapeSequences::moveCursor(10,22);

    // write name
    EscapeSequences::setForeground(XTRUITES_LOCATION_FOREGROUND);
    for(char& c : _currentPage->getName())
    {
        if(isprint(c))
        {
            EscapeSequences::write("%c", c);
        }
        else
        {
            EscapeSequences::write(" ");
        }
    }

    EscapeSequences::setForeground(XTRUITES_DEFAULT_FOREGROUND);
    EscapeSequences::write(" ■ ");
    EscapeSequences::setHomePosition(_currentPage->getName().length()+14, 22);
    EscapeSequences::moveCursorHome();
    EscapeSequences::write("\n");
}



void Container::clearContent()
{
    EscapeSequences::moveCursor(0, 1);

    // Clear screen
    for(uint8_t line=1; line < 20; line++)
    {
        EscapeSequences::erasesEntireCurrentLine();
        EscapeSequences::write("║");
        EscapeSequences::moveCursor(79, line);
        EscapeSequences::write("║\r\n");
    }
}

void Container::pushKey(uint8_t key)
{
    if(_state == updatePage || _state == readKey)
    {
        _inputKey.lock();
        if(!_inputKey.isFull())
        {
            _inputKey.push(key);
        }
        _inputKey.unlock();
    }
}


/*

XTRUITES& XTRUITES::quit()
{
    page->unload();
    clearContent();
    EscapeSequences::resetAttributes();
    EscapeSequences::clearScreen();
    EscapeSequences::scrollScreen(0, 22);
    EscapeSequences::moveCursor(60,23);
    EscapeSequences::write("▫ ^T Open XTRUITE ▫");
    EscapeSequences::moveCursor(0,0);
    EscapeSequences::write("\r\n");

    XTRUITES::enable= false;

    return *this;
}
*/

/*EoF*/
