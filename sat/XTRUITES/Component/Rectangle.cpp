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


Rectangle::Rectangle( unsigned char xVal, unsigned char yVal, unsigned char widthVal, unsigned char heightVal )
	: _location( xVal, yVal ), _size(widthVal, heightVal)
{ ; }

Point& Rectangle::getLocation( void )
{
    return _location;
}

Size& Rectangle::getSize( void )
{
    return _size;
}

Rectangle& Rectangle::setLocation( const Point& locationVal)
{
    _location= locationVal;
    return *this;
}

Rectangle& Rectangle::setSize( const Size& sizeVal)
{
    _size= sizeVal;
    return *this;
}
