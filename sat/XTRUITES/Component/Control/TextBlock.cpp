/**
 *  @file       textBlock.cpp
 *  @brief      Contrôle textBlock (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.6
 *  @date       11/05/2015 - 12/06/2015
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
    unsigned char locationX= this->getRegion()->getLocation()->getX();
    unsigned char locationY= this->getRegion()->getLocation()->getY();
    unsigned char height= this->getRegion()->getSize()->getHeight();
    unsigned char width= this->getRegion()->getSize()->getWidth();

    unsigned char lineWidth=0;
    unsigned char currentHeight=0;
    unsigned char lastWriteLineWidth=0;
    unsigned char lastWriteCurrentHeight=0;

    // calculate limit, maximum allowed is XTRUITES_DEFAULT_SCREEN_LIMIT - 1
    unsigned char limitX= (width +locationX < XTRUITES_DEFAULT_SCREEN_LIMIT_X) ? width+locationX-1  : XTRUITES_DEFAULT_SCREEN_LIMIT_X-1;
    unsigned char limitY= (height+locationY < XTRUITES_DEFAULT_SCREEN_LIMIT_Y) ? height+locationY-1 : XTRUITES_DEFAULT_SCREEN_LIMIT_Y-1;

    // Text Out of Bounds
    if(locationX > limitX && locationY > limitY)
    {
        return;
    }

    EscapeSequences::setColor(this->getColor());

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
    }

    // Write end padding
    if(padding)
    {
        writePadding(locationX+lastWriteLineWidth, locationY+lastWriteCurrentHeight, limitX+1, limitY, locationX, limitX);
    }

    EscapeSequences::moveCursorHome();
    EscapeSequences::write("\n");
}


void TextBlock::onUpdate( void )
{
}

void TextBlock::onUnload( void )
{
}


void TextBlock::onKeyPress( unsigned char key )
{
}

Point* qb50::XTRUITES::writePadding(unsigned char beginX, unsigned char  beginY, unsigned char  endX, unsigned char  endY, unsigned char offset, unsigned char maximum)
{
    return writePadding(new Point(beginX, beginY), new Point(endX, endY), offset, maximum);
}

Point* qb50::XTRUITES::writePadding(Point* beginP, Point* endP, unsigned char offset, unsigned char maximum)
{
    EscapeSequences::moveCursor(beginP);

    Point* cursor= new Point(beginP->getX(), beginP->getY());

    while(cursor->getY() < endP->getY()  || (cursor->getY() == endP->getY() && cursor->getX() < endP->getX() ))
    {
        if(cursor->getX() > maximum)
        {
            cursor->y++;
            cursor->x = offset;

            EscapeSequences::moveCursor(cursor);
            if(cursor->getX() >= endP->getX() && cursor->getY() >= endP->getY())
            {
                return cursor;
            }
        }
        else
        {
            EscapeSequences::write(" ");
            cursor->x++;
        }
    }
    return cursor;
}

TextBlock&  TextBlock::setText(std::string textVal)
{
    text = textVal;
    return *this;
}

std::string TextBlock::getText()
{
  return text;
}


/*EoF*/
