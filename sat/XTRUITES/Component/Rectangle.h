/**
 *  @file       Size.h
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */

#ifndef _QB50_XTRUITES_RECTANGLE_H_
#define _QB50_XTRUITES_RECTANGLE_H_

#include "Point.h"
#include "Size.h"
#include "XTRUITES.h"

namespace qb50
{

    namespace XTRUITES
    {

        class Rectangle
        {

            public:

                Rectangle( unsigned char xVal= XTRUITES_DEFAULT_LOCATION_X, unsigned char yVal= XTRUITES_DEFAULT_LOCATION_Y,
                           unsigned char widthVal= XTRUITES_DEFAULT_WIDTH, unsigned char heightVal= XTRUITES_DEFAULT_HEIGHT);

                Point& getLocation( void );
                Rectangle& setLocation( const Point& locationVal);
                Size& getSize( void );
                Rectangle& setSize( const Size& sizeVal);

                Point _location;
                Size _size;
        };

    } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_RECTANGLE_H_ */

/*EoF*/





