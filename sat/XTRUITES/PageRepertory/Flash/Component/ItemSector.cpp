/**
 *  @file     ItemSector.cpp
 *  @brief    Component permetant de visualiser les résultats des test sur chaque secteur (Source)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#include "../../Container.h"
#include "../../EscapeSequences.h"
#include "../../Component/Color.h"
#include "LabelSector.h"
#include "ItemSector.h"

using namespace qb50::XTRUITES;

const unsigned char ItemSector::greenToRedGradient[6]{
  46, // Vert
  76,
  106,
  136,
  166,
  196 // Rouge
};

ItemSector::ItemSector(LabelBlock* labelBlockVal, LabelSector* labelSectorVal)
  : _labelBlock(labelBlockVal), _labelSector(labelSectorVal)
{
  for(unsigned char sector=0; sector < XTRUITES_RAM_TEST_SECTOR_SIZE; sector++)
  {
    for(unsigned char block=0; block < XTRUITES_RAM_TEST_BLOCK_SIZE; block++)
    {
      resultList[ block ][ sector ] = 0;
    }
  }
}



void ItemSector::onLoad( void )
{
  for(unsigned char block=0; block < XTRUITES_RAM_TEST_BLOCK_SIZE; block++)
  {
    for(unsigned char sector=0; sector < XTRUITES_RAM_TEST_SECTOR_SIZE; sector++)
    {
      writeSector(block, sector);
    }
  }
}

void ItemSector::addResult(unsigned char _cursorBlock, unsigned char _cursorSector, bool result)
{
  _labelBlock->select(_cursorBlock);
  _labelSector->select(_cursorSector);

  resultList[ _cursorBlock ][ _cursorSector ]+= !result;

  if(resultList[ _cursorBlock ][ _cursorSector ] > 5)
  {
    resultList[ _cursorBlock ][ _cursorSector ] = 5;
  }

  writeSector(_cursorBlock, _cursorSector);
}

void ItemSector::writeSector(unsigned char _cursorBlock, unsigned char _cursorSector)
{
  Point cursor= Point(
    _labelBlock->getLocation().getX()+_cursorBlock,
    _labelSector->getLocation().getY()+_cursorSector
  );

  EscapeSequences::moveCursor(cursor);
  EscapeSequences::setBackground(greenToRedGradient[resultList[ _cursorBlock ][ _cursorSector ]]);
  EscapeSequences::setForeground(XTRUITES_RAM_TEST_FOREGROUND_ITEM_SECTOR);

  if( !((_cursorBlock+1)%4) || !((_cursorSector+1)%4))
  {
    EscapeSequences::write("·");
  }
  else
  {
    EscapeSequences::write(" ");
  }

}


void ItemSector::initializeResult( void )
{
  _labelBlock->select(0);
  _labelSector->select(0);

  for(unsigned char sector=0; sector < XTRUITES_RAM_TEST_SECTOR_SIZE; sector++)
  {
    for(unsigned char block=0; block < XTRUITES_RAM_TEST_BLOCK_SIZE; block++)
    {
      resultList[ block ][ sector ] = 0;
    }
  }
}
/*EoF*/
