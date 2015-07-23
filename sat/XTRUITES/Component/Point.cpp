
#include "Point.h"

using namespace qb50::XTRUITES;

Point::Point(unsigned char xVal, unsigned char yVal)
{
    x= xVal;
    y= yVal;
}

unsigned char Point::getX( void ) const
{
    return x;
}

unsigned char Point::getY( void ) const
{
    return y;
}
