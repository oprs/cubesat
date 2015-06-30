/**
 *  @file       homePage.cpp
 *  @brief      Page d'accueil (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       28/05/2015
 */

#include "Rectangle.h"
#include "Point.h"
#include "Size.h"

using namespace qb50::XTRUITES;

Rectangle::Rectangle( Point* locationVal, Size* sizeVal )
{
    location= locationVal;
    size= sizeVal;
}

Rectangle::Rectangle( unsigned char xVal, unsigned char yVal, unsigned char widthVal, unsigned char heightVal)
{
    location= new Point(xVal, yVal);
    size= new Size(widthVal, heightVal);
}

Point* Rectangle::getLocation( void )
{
    return location;
}

Size* Rectangle::getSize( void )
{
    return size;
}
