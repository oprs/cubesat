/**
 *  @file     textBlock.cpp
 *  @brief    Contrôle textBlock (Source)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.6
 *  @date     11/05/2015 - 12/06/2015
 */


#include "TextBlock.h"
#include "Page.h"

#include "../../Container.h"
#include "../../Component/ComponentCollection.h"
#include "../../PageRepertory/PageRepertory.h"
#include "../../XTRUITES.h"
#include "../../EscapeSequences.h"

using namespace qb50::XTRUITES;

void TextBlock::onLoad( void )
{
  unsigned char locationX= getLocation().getX();
  unsigned char locationY= getLocation().getY();
  unsigned char height= getSize().getHeight();
  unsigned char width= getSize().getWidth();

  unsigned char lineWidth=0;
  unsigned char currentHeight=0;
  unsigned char lastWriteLineWidth=0;
  unsigned char lastWriteCurrentHeight=0;
  unsigned char maxWidth=0;

  unsigned char limitX;
  unsigned char limitY;

  if(mode == Mode::adaptiveSizeMode)
  {
    limitX= XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-1;
    limitY= XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH -1;
  }
  else if(mode == Mode::linePaddingAdaptiveHeightMode)
  {
    limitX= (width +locationX < XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT) ? width+locationX-1  : XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-1;
    limitY= XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH -1;
  }
  else
  {
    // calculate limit, maximum allowed is XTRUITES_DEFAULT_SCREEN_LIMIT - 1
    limitX= (width +locationX < XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT) ? width+locationX-1  : XTRUITES_SCREEN_TEXT_RESOLUTION_HEIGHT-1;
    limitY= (height+locationY < XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH ) ? height+locationY-1 : XTRUITES_SCREEN_TEXT_RESOLUTION_WIDTH -1;
  }

  // Text Out of Bounds
  if(locationX > limitX && locationY > limitY)
  {
    return;
  }

  EscapeSequences::moveCursor(locationX+lineWidth, locationY+currentHeight);
  EscapeSequences::setColor(getColor());

  for(char& c : text)
  {

    // Line return
    if(locationX+lineWidth > limitX)
    {
      ++currentHeight;
      lineWidth=0;
      if(locationY+currentHeight > limitY)
      {
        // last line is write
        break;
      }
      EscapeSequences::write("\r\n");
      EscapeSequences::moveCursor(locationX, locationY+currentHeight);
    }

    // Write printable chars and special chars support (CR and LF)
    switch(c)
    {
      case '\r': // Carriage Return
        lineWidth=0;
        EscapeSequences::moveCursor(locationX+lineWidth, locationY+currentHeight);
        break;

      case '\n': // Line Feed
        ++currentHeight;
        EscapeSequences::moveCursor(locationX+lineWidth, locationY+currentHeight);
        break;

      default:

        // Write padding (If last char is CR or LF)
        if(mode == Mode::paddingMode || mode == Mode::linePaddingAdaptiveHeightMode)
        {
          writePadding(
            locationX+lastWriteLineWidth, locationY+lastWriteCurrentHeight,
            locationX+lineWidth     , locationY+currentHeight,
            locationX, limitX);
        }

        // Write printable character
        if(c >= 0x20 && c <= 0x7E)
        {
          EscapeSequences::write("%c", c);
        }
        else
        {
          EscapeSequences::write(" ");
        }

        ++lineWidth;
        lastWriteLineWidth=lineWidth;
        lastWriteCurrentHeight= currentHeight;

    } /* End for */

    if(lineWidth > maxWidth)
    {
      maxWidth= lineWidth;
    }
  }

  if(mode == Mode::paddingMode)
  {
    // end padding
    writePadding(locationX+lastWriteLineWidth, locationY+lastWriteCurrentHeight, limitX+1, limitY, locationX, limitX);
  }
  else if(mode == Mode::adaptiveSizeMode)
  {
    getSize().height= currentHeight+1;
    getSize().width= maxWidth;
  }
  else if(mode == Mode::linePaddingAdaptiveHeightMode)
  {
    // Padding current line
    writePadding(locationX+lastWriteLineWidth, locationY+lastWriteCurrentHeight, limitX+1, locationY+lastWriteCurrentHeight, locationX, limitX);
    getSize().height= currentHeight+1;
  }
}

Point qb50::XTRUITES::writePadding(unsigned char beginX, unsigned char  beginY, unsigned char  endX, unsigned char  endY, unsigned char offset, unsigned char maximum)
{
  return writePadding(Point(beginX, beginY), Point(endX, endY), offset, maximum);
}

Point qb50::XTRUITES::writePadding(Point beginP, Point endP, unsigned char offset, unsigned char maximum)
{
  EscapeSequences::moveCursor(beginP);

  Point cursor(beginP.getX(), beginP.getY());

  while(cursor.getY() < endP.getY()  || (cursor.getY() == endP.getY() && cursor.getX() < endP.getX() ))
  {
    if(cursor.getX() > maximum)
    {
      cursor.y++;
      cursor.x = offset;

      EscapeSequences::moveCursor(cursor);
      if(cursor.getX() >= endP.getX() && cursor.getY() >= endP.getY())
      {
        return cursor;
      }
    }
    else
    {
      EscapeSequences::write(" ");
      cursor.x++;
    }
  }
  return cursor;
}

TextBlock& TextBlock::setText(std::string textVal)
{
  text = textVal;
  return *this;
}

std::string TextBlock::getText()
{
  return text;
}


/*EoF*/
