/**
 *  textBlock.h
 *  11/05/2015
 */


#ifndef _QB50_TEXTBLOCK_H_
#define _QB50_TEXTBLOCK_H_


#include "../textualInterface.h"


namespace qb50
{

    /**
     *
     *  @author     Jérôme Skoda    <jerome.skoda@hotmail.fr>
     *  @version    1.0             (11/05/2015)
     */
    class XTRUITESTextBlock
    {
        public:
            uint8_t     height;
            uint8_t     width;
            uint8_t     locationX;
            uint8_t     locationY;
            std::string text;

            uint8_t     background= XTRUITES_DEFAULT_BACKGROUND;
            uint8_t     foreground= XTRUITES_DEFAULT_FOREGROUND;

            bool        padding= true;

            XTRUITESTextBlock&  setBackground(uint8_t backgroundVal);
            uint8_t             getBackground();

            XTRUITESTextBlock&  setForeground(uint8_t foregroundVal);
            uint8_t             getForeground();

            XTRUITESTextBlock&  setLocationX(uint8_t locationXVal);
            uint8_t             getLocationX();

            XTRUITESTextBlock&  setLocationY(uint8_t locationYVal);
            uint8_t             getLocationY();

            XTRUITESTextBlock&  setHeight(uint8_t heightVal);
            uint8_t             getHeight();

            XTRUITESTextBlock&  setWidth(uint8_t widthVal);
            uint8_t             getWidth();

            XTRUITESTextBlock&  setText(std::string textVal);
            std::string         getText();

            XTRUITESTextBlock&  display();

            XTRUITESTextBlock&  reversesColors();
    };


} /* namespace: qb50 */


#endif /* _QB50_TEXTBLOCK_H_ */


/*EoF*/
