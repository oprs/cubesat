/**
 *  @file       Size.h
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */

#include "Size.h"

using namespace qb50::XTRUITES;

Size::Size(unsigned char widthVal, unsigned char heightVal)
{
    width= widthVal;
    height= heightVal;
}


unsigned char Size::getHeight( void )
{
    return height;
}

unsigned char Size::getWidth( void )
{
    return width;
}
