/**
 *  @file     LabelBlock.cpp
 *  @brief    Component permetant l'affichage des numéros de Block (Source)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#include "../../EscapeSequences.h"
#include "LabelBlock.h"
#include "FlashPage.h"

using namespace qb50::XTRUITES;

LabelBlock::LabelBlock() : FlashLabel(XTRUITES_RAM_TEST_BLOCK_SIZE)
{
}

void LabelBlock::writeLabel( uint8_t number, Color color)
{
    Point cursor= getLocation();
    cursor.x+= number;
    EscapeSequences::setColor(color);
    EscapeSequences::moveCursor(cursor);
    EscapeSequences::write("%1X", number>>4);
    EscapeSequences::moveCursor(cursor.getX(), cursor.getY()+1);
    EscapeSequences::write("%1X", number&0x0F);
}

/*EoF*/
