/**
 *  textBlock.cpp
 *  11/05/2015
 */


#include "textBlock.h"


using namespace qb50;
using namespace std;

void writePadding(uint8_t beginX, uint8_t beginY, uint8_t endX, uint8_t endY, uint8_t offset, uint8_t maximum)
{
    escapeSequences::moveCursor(beginX, beginY);

    while(beginY < endY  || (beginY == endY && beginX < endX))
    {
        if(beginX > maximum)
        {
            beginY++;
            beginX=offset;
            escapeSequences::moveCursor(beginX, beginY);
            if(beginX >= endX && beginY >= endY)
            {
                return;
            }
        }
        else
        {
            escapeSequences::write(" ");
            beginX++;
        }
    }
    return;
}

/**
*
*
*
*/
XTRUITESTextBlock&  XTRUITESTextBlock::setText(string textVal)
{
    text = textVal;
    return *this;
}

XTRUITESTextBlock&  XTRUITESTextBlock::display()
{
    // Text size null
    if(width == 0 || height == 0)
    {
        return *this;
    }

    uint8_t lineWidth=0;
    uint8_t currentHeight=0;
    uint8_t lastWriteLineWidth=0;
    uint8_t lastWriteCurrentHeight=0;

    // calculate limit, maximum allowed is XTRUITES_DEFAULT_SCREEN_LIMIT - 1
    uint8_t limitX= (width +locationX < XTRUITES_DEFAULT_SCREEN_LIMIT_X) ? width+locationX-1  : XTRUITES_DEFAULT_SCREEN_LIMIT_X-1;
    uint8_t limitY= (height+locationY < XTRUITES_DEFAULT_SCREEN_LIMIT_Y) ? height+locationY-1 : XTRUITES_DEFAULT_SCREEN_LIMIT_Y-1;

    // Text Out of Bounds
    if(locationX > limitX && locationY > limitY)
    {
        return *this;
    }

    escapeSequences::setBackground(background);
    escapeSequences::setForeground(foreground);
    escapeSequences::moveCursor(locationX, locationY);

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
            escapeSequences::write("\r\n");
            escapeSequences::moveCursor(locationX, locationY+currentHeight);
        }

        // Write printable chars and special chars support (CR and LF)
        switch(c)
        {
            case '\r': // Carriage Return
                lineWidth=0;
                escapeSequences::moveCursor(locationX+lineWidth, locationY+currentHeight);
                break;

            case '\n': // Line Feed
                ++currentHeight;
                escapeSequences::moveCursor(locationX+lineWidth, locationY+currentHeight);
                break;

            default:

                // Write padding (If last char is CR or LF)
                if(padding)
                {
                    writePadding(
                               locationX+lastWriteLineWidth, locationY+lastWriteCurrentHeight,
                               locationX+lineWidth         , locationY+currentHeight,
                               locationX, limitX);
                }

                // Write printable character
                if(c >= 0x20 && c <= 0x7E)
                {
                    escapeSequences::write("%c", c);
                }
                else
                {
                    escapeSequences::write(" ");
                }

                ++lineWidth;
                lastWriteLineWidth=lineWidth;
                lastWriteCurrentHeight= currentHeight;

        } /* End for */
    }

    // Write end padding
    if(padding)
    {
        writePadding(locationX+lastWriteLineWidth, locationY+lastWriteCurrentHeight, limitX+1, limitY, locationX, limitX);
    }

    escapeSequences::moveCursorHome();
    escapeSequences::write("\n");

    return *this;
}




XTRUITESTextBlock&  XTRUITESTextBlock::setBackground(uint8_t backgroundVal)
{
    background = backgroundVal;
    return *this;
}
uint8_t             XTRUITESTextBlock::getBackground()
{
    return background;
}

XTRUITESTextBlock&  XTRUITESTextBlock::setForeground(uint8_t foregroundVal)
{
    foreground = foregroundVal;
    return *this;
}
uint8_t             XTRUITESTextBlock::getForeground()
{
    return foreground;
}




string XTRUITESTextBlock::getText()
{
  return text;
}

XTRUITESTextBlock&  XTRUITESTextBlock::setLocationX(uint8_t locationXVal)
{
    locationX = locationXVal;
    return *this;
}

uint8_t XTRUITESTextBlock::getLocationX()
{
  return locationX;
}

XTRUITESTextBlock&  XTRUITESTextBlock::setLocationY(uint8_t locationYVal)
{
    locationY= locationYVal;
    return *this;
}

uint8_t XTRUITESTextBlock::getLocationY()
{
  return locationY;
}


XTRUITESTextBlock& XTRUITESTextBlock::setHeight(uint8_t heightVal)
{
    height = heightVal;
    return *this;
}
uint8_t XTRUITESTextBlock::getHeight()
{
  return height;
}


XTRUITESTextBlock& XTRUITESTextBlock::setWidth(uint8_t widthVal)
{
    width = widthVal;
    return *this;
}
uint8_t XTRUITESTextBlock::getWidth()
{
  return width;
}



XTRUITESTextBlock& XTRUITESTextBlock::reversesColors()
{
    uint8_t backgroundBegin= background;
    background= foreground;
    foreground= backgroundBegin;
    return *this;
}




/*EoF*/
