/**
 *  @file       FIFO_InputKey.h
 *  @brief      Model de page pour XTRUITES (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */

#ifndef _QB50_XTRUITES_FIFO_INPUT_KEY_H_
#define _QB50_XTRUITES_FIFO_INPUT_KEY_H_



#include "inc/FIFO.hpp"
#include "inc/UserLock.h"


namespace qb50
{
    namespace XTRUITES
    {

        class FIFO_InputKey : public qb50::FIFO<unsigned char>
        {

            public:
                FIFO_InputKey(unsigned depth) : FIFO<unsigned char>(depth)
                {
                }

                void lock( void )
                {
                    _userLock.acquire();
                }

                void unlock( void )
                {
                    _userLock.release();
                }

            private:

                qb50::UserLock _userLock;

        };

    }

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_FIFO_INPUT_KEY_H_ */


/*EoF*/
