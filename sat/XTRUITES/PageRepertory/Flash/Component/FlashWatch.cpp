/**
 *  @file     FlashWatch.cpp
 *  @brief    Component permetant d'effectuer et de visualiser les tests sur une RAM (Source)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#include "system/qb50.h"
#include "Page.h"

#include "../../Container.h"
#include "../../Component/ComponentCollection.h"
#include "../../PageRepertory/PageRepertory.h"
#include "../../XTRUITES.h"
#include "../../EscapeSequences.h"
#include "FlashWatch.h"
#include "LabelSector.h"
#include "LabelBlock.h"

using namespace qb50::XTRUITES;
using namespace std;

FlashWatch::FlashWatch() : _labelBlock() , _labelSector(), _itemSector(&_labelBlock,&_labelSector)
{
    addChildren( &_labelBlock );
    addChildren( &_labelSector );
    addChildren( &_itemSector );
}

void FlashWatch::onLoad( void )
{
  unsigned char xLocation= getLocation().getX();
  unsigned char yLocation= getLocation().getY();

  _sectorTitle(xLocation, yLocation+3);
  _blockTitle(xLocation+4, yLocation);

  _labelBlock .setLocation(Point(xLocation+4, yLocation+1))
              .setColor(Color(XTRUITES_RAM_TEST_BACKGROUND_BLOCK_LABEL , XTRUITES_RAM_TEST_FOREGROUND_BLOCK_LABEL));
  _labelSector.setLocation(Point(xLocation+2, yLocation+3))
              .setColor(Color(XTRUITES_RAM_TEST_BACKGROUND_SECTOR_LABEL , XTRUITES_RAM_TEST_FOREGROUND_SECTOR_LABEL));
  _itemSector .setLocation(Point(xLocation+4, yLocation+3));

  onLoadChildren();
}


void FlashWatch::onUpdate( void )
{
  bool result=  false;

  switch(_state)
  {
    case initialize:
      _state= test;
      _stepTest=1;
    break;


    case test:
      result= runTestSequence();
      _itemSector.addResult(_cursorBlock, _cursorSector, result );

      _cursorSector++;

      if(_cursorSector < XTRUITES_RAM_TEST_SECTOR_SIZE) return;
      _cursorSector= 0;
      _cursorBlock++;

      if(_cursorBlock < XTRUITES_RAM_TEST_BLOCK_SIZE) return;
      _cursorBlock= 0;
      _stepTest++;

      if(_stepTest < 6) return;
      _state= wait;

    break;


    case wait:
      _labelBlock.deselect();
      _labelSector.deselect();
    break;
  }
}



bool FlashWatch::runTestSequence( void )
{

  switch(_stepTest)
  {
    case 1:
      // Test sector erase
      // - Write 0x00 in previous, target, next sector
      // - Read previous (0x00), target (0xFF), next (0x00)
      return false;
    break;
    case 2:
      // Test single write
      // - Write 0xA5
      // - Read (expected value 0xA5)
      return false;
    break;
    case 3:
      // Test block erase
      // - Write 0x00 in previous, target, next block
      // - Read previous (0x00), target (0xFF), next (0x00)
      return false;
    break;
    case 4:
      // Test write consecutive
      // - Write                  0xF5    0b11110101
      // - Write                  0xEA    0b11101010
      // - Write                  0x1F    0b00011111
      // - Read (expected value   0x00    0b00000000)
      return false;
    break;
    case 5:
      // Test chip erase
      // - Read all (expected value 0xFF)
      return false;
    break;

    default:
      return false;
    break;
  }
}

void FlashWatch::_sectorTitle( unsigned char xLocation, unsigned char yLocation )
{
  EscapeSequences::setColor(Color(XTRUITES_RAM_TEST_BACKGROUND_SECTOR_TITLE, XTRUITES_RAM_TEST_FOREGROUND_SECTOR_TITLE));
  // Write space for background
  for(unsigned char i=0; i<XTRUITES_RAM_TEST_SECTOR_SIZE; i++)
  {
    EscapeSequences::moveCursor(xLocation , yLocation+i);
    EscapeSequences::write("  ");
  }
  // Write sector title
  const char titleLabelSector[]= "S E C T O R";
  Point sectorTitleLocation(xLocation, yLocation + (XTRUITES_RAM_TEST_SECTOR_SIZE - 11) / 2 );
  for(unsigned char i= 0; i < 11; i++)
  {
    EscapeSequences::moveCursor(sectorTitleLocation);
    EscapeSequences::write("%c", titleLabelSector[i]);
    sectorTitleLocation.y++;
  }
}

void FlashWatch::_blockTitle( unsigned char xLocation, unsigned char yLocation )
{

  EscapeSequences::setColor(Color(XTRUITES_RAM_TEST_BACKGROUND_BLOCK_TITLE, XTRUITES_RAM_TEST_FOREGROUND_BLOCK_TITLE));
  EscapeSequences::moveCursor(xLocation , yLocation);
  // Write space for background
  for(unsigned char i=0; i<XTRUITES_RAM_TEST_BLOCK_SIZE; i++)
  {
    EscapeSequences::write(" ");
  }
  // Write block title
  EscapeSequences::moveCursor(xLocation + (XTRUITES_RAM_TEST_BLOCK_SIZE - 13) / 2 , yLocation);
  EscapeSequences::write("B  L  O  C  K");
}
/*EoF*/
