/**
 *  @file       Color.h
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */


#ifndef _QB50_XTRUITES_COLOR_H_
#define _QB50_XTRUITES_COLOR_H_

#include "../../XTRUITES.h"

namespace qb50
{

    namespace XTRUITES
    {

        class Color
        {

            public:

                unsigned char background;
                unsigned char foreground;


                Color( unsigned char backgroundVal= XTRUITES_DEFAULT_COLOR_BACKGROUND, unsigned char foregroundVal= XTRUITES_DEFAULT_COLOR_FOREGROUND);

                Color& invert( void );
        };

    } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_COLOR_H_ */

/*EoF*/
