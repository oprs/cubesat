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

namespace qb50
{

    namespace XTRUITES
    {

        class Rectangle
        {

            public:

                Rectangle( Point* locationVal, Size* sizeVal );
                Rectangle( unsigned char xVal, unsigned char yVal, unsigned char widthVal, unsigned char heightVal);

                Point* location= nullptr;
                Size* size= nullptr;

                Point* getLocation( void );
                Size* getSize( void );

        };

    } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_RECTANGLE_H_ */

/*EoF*/





