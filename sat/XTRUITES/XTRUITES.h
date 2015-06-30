/**
 *  @file
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version
 *  @date
 */

#ifndef _QB50_XTRUITES_H_
#define _QB50_XTRUITES_H_


#include "Container.h"
#include "OutputStream/OutputStream.h"
#include "OutputStream/OutputStreamChannel.h"



// color definition
#define XTRUITES_KEY_FOREGROUND             41
#define XTRUITES_DEFAULT_BACKGROUND         23
#define XTRUITES_DEFAULT_FOREGROUND         253

#define XTRUITES_LOCATION_FOREGROUND        214

#define XTRUITES_LIST_TEXTBLOCK_KEY_FOREGROUND      41
#define XTRUITES_LIST_TEXTBLOCK_DEFAULT_BACKGROUND  23
#define XTRUITES_LIST_TEXTBLOCK_DEFAULT_FOREGROUND  253

// Power of 2
#define XTRUITES_FIFO_DEPTH 8

// print last key pressed
#define XTRUITES_DEBUG_ENABLED              true
// windows size
#define XTRUITES_SCREEN_SIZE_HEIGHT        24



#define XTRUITES_DEFAULT_SCREEN_LIMIT_X     80
#define XTRUITES_DEFAULT_SCREEN_LIMIT_Y     24
// frame size (in window)
#define  XTRUITES_FRAME_LIMIT_X_MIN         2
#define  XTRUITES_FRAME_LIMIT_X_MAX         78
#define  XTRUITES_FRAME_LIMIT_Y_MIN         2
#define  XTRUITES_FRAME_LIMIT_Y_MAX         20

namespace qb50
{

    namespace XTRUITES
    {

        extern qb50::XTRUITES::Container    XTRUITESContainer;
        extern qb50::XTRUITES::OutputStream OutputStreamUART3;

    } /* namespace: XTRUITES */

} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_H_ */


/*EoF*/
