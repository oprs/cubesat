/**
 *  @file       quitPage.cpp
 *  @brief      Page d'accueil (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       28/05/2015
 */

#include "quitPage.h"
#include "../PageRepertory.h"
#include "../../EscapeSequences.h"

using namespace qb50::XTRUITES;

void quitPage::onLoad( void )
{
    getRepertory().getContainer().getStreamChannel().getOutputStream()->on();

    EscapeSequences::resetAttributes();
    EscapeSequences::clearScreen();
    EscapeSequences::scrollScreen(0, XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-1);
    EscapeSequences::moveCursor(XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH-20,XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-1);
    EscapeSequences::write("▫ ^T Open XTRUITE ▫");
    EscapeSequences::moveCursor(0,0);
    EscapeSequences::write("\r\n");
}

void quitPage::onUnload( void )
{
  getRepertory().getContainer().getStreamChannel().getOutputStream()->off();
  getRepertory().getContainer().getStreamChannel().on();
}
