/**
 *  @file       Point.h
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */


#ifndef _QB50_XTRUITES_POINT_H_
#define _QB50_XTRUITES_POINT_H_

#include "XTRUITES.h"

namespace qb50
{

    namespace XTRUITES
    {

        class Point
        {

            public:

                Point(unsigned char xVal=XTRUITES_DEFAULT_LOCATION_X, unsigned char yVal= XTRUITES_DEFAULT_LOCATION_Y);

                unsigned char x;
                unsigned char y;

                unsigned char getX( void ) const ;

                unsigned char getY( void ) const ;
        };

    } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_POINT_H_ */

/*EoF*/
