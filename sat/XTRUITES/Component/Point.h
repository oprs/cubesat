/**
 *  @file       Point.h
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */


#ifndef _QB50_XTRUITES_POINT_H_
#define _QB50_XTRUITES_POINT_H_

namespace qb50
{

    namespace XTRUITES
    {

        class Point
        {

            public:

                Point(unsigned char xVal, unsigned char yVal);

                unsigned char x;
                unsigned char y;

                unsigned char getX( void );

                unsigned char getY( void );
        };

    } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_POINT_H_ */

/*EoF*/
