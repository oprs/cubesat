
#include "Point.h"

using namespace qb50::XTRUITES;

Point::Point(unsigned char xVal, unsigned char yVal)
{
    x= xVal;
    y= yVal;
}

unsigned char Point::getX( void )
{
    return x;
}

unsigned char Point::getY( void )
{
    return y;
}
