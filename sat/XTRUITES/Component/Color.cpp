/**
 *  @file       Size.h
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */

#include "color.h"

using namespace qb50::XTRUITES;

Color::Color( unsigned char backgroundVal, unsigned char foregroundVal )
{
    background= backgroundVal;
    foreground= foregroundVal;
}



Color& Color::invert( void )
{
    unsigned char backgroundBegin= background;
    background= foreground;
    foreground= backgroundBegin;

    return *this;
}
