/**
 *  escapeSequences.h
 *  11/05/2015
 */


#ifndef _QB50_ESCAPE_SEQUENCES_H_
#define _QB50_ESCAPE_SEQUENCES_H_


// color definition
#define XTRUITES_DEFAULT_BACKGROUND         23
#define XTRUITES_DEFAULT_FOREGROUND         253
#define XTRUITES_KEY_FOREGROUND             41
#define XTRUITES_LOCATION_FOREGROUND        214
// print last key pressed
#define XTRUITES_DEBUG_ENABLED              true
// windows size
#define XTRUITES_DEFAULT_SCREEN_LIMIT_X     80
#define XTRUITES_DEFAULT_SCREEN_LIMIT_Y     24
// frame size (in window)
#define  XTRUITES_FRAME_LIMIT_X_MIN         2
#define  XTRUITES_FRAME_LIMIT_X_MAX         78
#define  XTRUITES_FRAME_LIMIT_Y_MIN         2
#define  XTRUITES_FRAME_LIMIT_Y_MAX         20


#include "textualInterface.h"


namespace qb50
{


    /**
     *
     *  @author     Jérôme Skoda    <jerome.skoda@hotmail.fr>
     *  @version    1.0             (11/05/2015)
     */
    class escapeSequences
    {


        public:


            static void moveCursor(uint8_t x, uint8_t y);
            static void clearScreen();
            static void setBackground(uint8_t color, bool force= false);
            static void setForeground(uint8_t color, bool force= false);
            static void reversesColors();
            static void erasesEntireCurrentLine();
            static void setHomePosition(uint8_t x, uint8_t y);
            static void moveCursorHome();
            static void resetAttributes();
            static void scrollScreen(uint8_t startRow, uint8_t endRow);
            static int write(const char *format , ...);


            static uint8_t xHome;
            static uint8_t yHome;

            static uint8_t currentBackground;
            static uint8_t currentForeground;


    };


} /* namespace: qb50 */


#endif /* _QB50_ESCAPE_SEQUENCES_H_ */


/*EoF*/
