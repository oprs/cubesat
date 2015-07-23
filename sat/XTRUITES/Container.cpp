/**
 *  @file       textualInterface.cpp
 *  @brief      Gestion comportemental de l'interface (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.9
 *  @date       11/05/2015 - 12/06/2015
 */

#include "Container.h"
#include "XTRUITES.h"
#include "EscapeSequences.h"
#include "PageRepertory/Page.h"
#include "PageRepertory/PageRepertory.h"
#include "OutputStream/OutputStreamChannel.h"
#include "OutputStream/OutputStream.h"
#include "FIFO_inputKey.hpp"
#include "OutputStream/OutputStreamChannel.h"

using namespace qb50::XTRUITES;

Container::Container(OutputStreamChannel& streamChannel, FIFO_InputKey& inputKey)
  : _streamChannel(streamChannel), _inputKey(inputKey)
{
  _pageRepertory= new PageRepertory();
  _pageRepertory->setContainer(this);

  _state= initialize;
  _currentPage= nullptr;
  _nextPage= _pageRepertory->getPageByName("Home");
}
Container::~Container()
{
  delete _pageRepertory;
}

PageRepertory& Container::getRepertory( void )
{
    return *_pageRepertory;
}

Container_state_t Container::getState()
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
    _streamChannel.getOutputStream()->off();
    _streamChannel.on();

    // Définition des attribus
    EscapeSequences::resetAttributes();
    EscapeSequences::setBackground(XTRUITES_DEFAULT_COLOR_BACKGROUND, true);
    EscapeSequences::setForeground(XTRUITES_DEFAULT_COLOR_FOREGROUND, true);
    EscapeSequences::clearScreen();
    EscapeSequences::scrollScreen(1, XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT);

    // Ecriture du cadre
    EscapeSequences::moveCursor(0,0);
    writeBoxing();
    writeTitle(XTRUITES_TITLE_STR);

    EscapeSequences::moveCursor(2,XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-2);
    EscapeSequences::write("00:00:00");

    writeSeparator(11);

    writeSeparator(XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH-34);
    writeShortcutKeys(XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH-32, XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-2);
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
            _initialize();
            _nextPage= _pageRepertory->getPageByName("Home");
        }
        return; // Disable default actions
    }

    // Display last key
    #if XTRUITES_DEBUG_ENABLED
        EscapeSequences::setBackground(XTRUITES_DEFAULT_COLOR_BACKGROUND);
        EscapeSequences::setForeground(XTRUITES_DEFAULT_COLOR_FOREGROUND);

        writeSeparator(XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH-34-12-3);

        EscapeSequences::moveCursor(XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH-34-12-1, XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-2);
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
    unsigned char xlocation= 13;
    unsigned char ylocation= XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-2;

    EscapeSequences::setBackground(XTRUITES_DEFAULT_COLOR_BACKGROUND);

    // clear location
    EscapeSequences::moveCursor(xlocation + _currentPage->getName().length(), ylocation);

    for(unsigned char row=0; row < 69-_currentPage->getName().length(); row++)
    {
    EscapeSequences::write(" ");

    }

    EscapeSequences::moveCursor(xlocation, ylocation);

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

    EscapeSequences::setForeground(XTRUITES_DEFAULT_COLOR_FOREGROUND);
    EscapeSequences::write(" » ");
    EscapeSequences::setHomePosition(_currentPage->getName().length()+ xlocation + 4, ylocation);
    EscapeSequences::moveCursorHome();
    EscapeSequences::write("\n");
}



void Container::clearContent()
{
    EscapeSequences::moveCursor(0, 1);

    // Clear screen
    for(uint8_t line=1; line < XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-3; line++)
    {
        EscapeSequences::erasesEntireCurrentLine();
        EscapeSequences::write("║");
        EscapeSequences::moveCursor(XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH-1, line);
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


void Container::setNextPage(Page* nextPageVal)
{
    _nextPage= nextPageVal;
}


void Container::writeSeparator(unsigned char line)
{
    EscapeSequences::setBackground(XTRUITES_DEFAULT_COLOR_BACKGROUND);
    EscapeSequences::setForeground(XTRUITES_DEFAULT_COLOR_FOREGROUND);

    EscapeSequences::moveCursor(line, XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-3);
    EscapeSequences::write("┬");
    EscapeSequences::moveCursor(line-1, XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-2);
    EscapeSequences::write(" │ ");
    EscapeSequences::moveCursor(line, XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-1);
    EscapeSequences::write("╧");
}


void Container::writeTitle(const char* title)
{
    EscapeSequences::moveCursor((XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH-XTRUITES_TITLE_WIDTH)/2 -2, 0 );
    EscapeSequences::write("╡");
    EscapeSequences::reversesColors();
    EscapeSequences::write(" ");
    EscapeSequences::write("%s", title);
    EscapeSequences::write(" ");
    EscapeSequences::reversesColors();
    EscapeSequences::write("╞");
}


void Container::writeBoxing()
{
    EscapeSequences::write("╔");
    for(unsigned char line=1; line<XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH-1; line++)
    {
        EscapeSequences::write("═");
    }
    EscapeSequences::write("╗");


    for(unsigned char line=1; line<XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-3; line++)
    {
        EscapeSequences::moveCursor(0,line);
        EscapeSequences::write("║");
        EscapeSequences::moveCursor(XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH-1, line);
        EscapeSequences::write("║");
    }


    EscapeSequences::moveCursor(0,XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-3);
    EscapeSequences::write("╟");
    for(unsigned char row=1; row<XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH-1; row++)
    {
        EscapeSequences::write("─");
    }
    EscapeSequences::write("╢");

    EscapeSequences::moveCursor(0,XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-2);
    EscapeSequences::write("║ ");
    EscapeSequences::moveCursor(XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH-2,XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-2);
    EscapeSequences::write(" ║");

    EscapeSequences::moveCursor(0,XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-1);
    EscapeSequences::write("╚");
    for(unsigned char row=1; row<XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH-1; row++)
    {
        EscapeSequences::write("═");
    }
    EscapeSequences::write("╝");
}

void Container::writeShortcutKeys(unsigned char x, unsigned char y)
{
  EscapeSequences::moveCursor(x,y);
  EscapeSequences::setForeground(XTRUITES_DEFAULT_COLOR_KEY_FOREGROUND);
  EscapeSequences::write( "^H"                            );
  EscapeSequences::setForeground(XTRUITES_DEFAULT_COLOR_FOREGROUND);
  EscapeSequences::write(   " Home ▫ "                    );
  EscapeSequences::setForeground(XTRUITES_DEFAULT_COLOR_KEY_FOREGROUND);
  EscapeSequences::write(           "^R"                  );
  EscapeSequences::setForeground(XTRUITES_DEFAULT_COLOR_FOREGROUND);
  EscapeSequences::write(             " Refresh ▫ "       );
  EscapeSequences::setForeground(XTRUITES_DEFAULT_COLOR_KEY_FOREGROUND);
  EscapeSequences::write(                        "^Q"     );
  EscapeSequences::setForeground(XTRUITES_DEFAULT_COLOR_FOREGROUND);
  EscapeSequences::write(                          " Quit") ;
}

OutputStreamChannel& Container::getStreamChannel( void )
{
  return _streamChannel;
}

/*EoF*/
