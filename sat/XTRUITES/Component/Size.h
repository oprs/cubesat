/**
 *  @file       Size.h
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */


#ifndef _QB50_XTRUITES_SIZE_H_
#define _QB50_XTRUITES_SIZE_H_

#include "XTRUITES.h"

namespace qb50
{

    namespace XTRUITES
    {

        class Size
        {

            public:

                Size(unsigned char widthVal= XTRUITES_DEFAULT_WIDTH, unsigned char heightVal = XTRUITES_DEFAULT_HEIGHT);

                unsigned char width;
                unsigned char height;

                unsigned char getHeight( void );
                unsigned char getWidth( void );

        };

    } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_SIZE_H_ */

/*EoF*/




