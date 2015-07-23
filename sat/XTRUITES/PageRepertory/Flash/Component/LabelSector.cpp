/**
 *  @file     LabelSector.cpp
 *  @brief    Component permetant l'affichage des numéros de Sector (Source)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#include "../../EscapeSequences.h"
#include "LabelSector.h"
#include "FlashPage.h"

using namespace qb50::XTRUITES;

LabelSector::LabelSector() : FlashLabel(XTRUITES_RAM_TEST_SECTOR_SIZE)
{
}

void LabelSector::writeLabel( uint8_t number, Color color)
{
    Point cursor= getLocation();
    cursor.y+= number;
    EscapeSequences::setColor(color);
    EscapeSequences::moveCursor(cursor);
    EscapeSequences::write("%02X", number);
}

/*EoF*/
