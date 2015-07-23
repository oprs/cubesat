/**
 *  @file       homePage.cpp
 *  @brief      Page d'accueil (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       28/05/2015
 */

#include "ColorPalette.h"

#include "../../EscapeSequences.h"

using namespace qb50::XTRUITES;

void colorPalettePage::writeColorPaletteItem(uint8_t x, uint8_t y, uint8_t color)
{
  EscapeSequences::moveCursor(x, y);
  EscapeSequences::setBackground(color);
  EscapeSequences::write(" ");
  EscapeSequences::setBackground(XTRUITES_DEFAULT_COLOR_BACKGROUND);
  EscapeSequences::write("%3d", color);
}


void colorPalettePage::onLoad( void )
{


  for(uint8_t color=0; color< 16; color++)
  {
    writeColorPaletteItem( 1+color*4, 2, color);
  }



  for(uint8_t line=0; line< 6; line++)
  {
    for(uint8_t colorRow=0; colorRow< 18; colorRow++)
    {
      uint8_t color= line*36 + 16 + colorRow;
      writeColorPaletteItem( (1+colorRow*4 + ((colorRow/6)*3)) , 4+line, color);
    }
  }



  for(uint8_t line=0; line< 6; line++)
  {
    for(uint8_t colorRow=18; colorRow< 36; colorRow++)
    {
      uint8_t color= line*36 + 16 + colorRow;
      uint8_t xLocation= (1+(colorRow-18)*4 + (((colorRow-18)/6)*3));
      uint8_t yLocation= 11+line;
      writeColorPaletteItem(xLocation ,yLocation , color);
    }
  }



  for(uint8_t color=232, yLocation=18, xLocation=0; color != 0; color++)
  {
    xLocation= 1+(color-232)*4;
    if(color >= 251)
    {
      yLocation= 19;
      xLocation= 1+(color-251)*4;
    }
    writeColorPaletteItem(xLocation, yLocation, color);
  }


}
