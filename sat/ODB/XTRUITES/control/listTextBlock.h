/**
 *  listTextBlock.h
 *  20/05/2015
 */


#ifndef _QB50_LIST_TEXTBLOCK_H_
#define _QB50_LIST_TEXTBLOCK_H_


#include "../textualInterface.h"


namespace qb50
{


    class XTRUITES;
    class XTRUITESInputHandler;


    class XTRUITESListTextBlockItem
    {


        public:

            std::string             label;
            uint8_t                 rowSpan;
            XTRUITESInputHandler*   inputHandler;


            XTRUITESListTextBlockItem(std::string labelVal, XTRUITESInputHandler* inputHandlerVal, uint8_t rowSpanVal=1);


            std::string                     getLabel();
            uint8_t                         getRowSpan();
            XTRUITESInputHandler*           getInputHandler();
            XTRUITESListTextBlockItem&      setLabel(std::string labelVal);
            XTRUITESListTextBlockItem&      setRowSpan(uint8_t rowSpanVal);
            XTRUITESListTextBlockItem&      setInputHandler(XTRUITESInputHandler* inputHandlerVal);


    };


    /**
     *
     *  @author     Jérôme Skoda    <jerome.skoda@hotmail.fr>
     *  @version    1.0             (20/05/2015)
     */
    class XTRUITESListTextBlock
    {
        public:
            std::vector<XTRUITESListTextBlockItem*>     items;

            uint8_t     height;
            uint8_t     width;
            uint8_t     heightItem;
            uint8_t     widthItem;


            uint8_t     locationX;
            uint8_t     locationY;

            uint8_t     background= 0;
            uint8_t     foreground= 1;

            XTRUITESListTextBlock&      setLocationX(uint8_t locationXVal);
            uint8_t                     getLocationX();

            XTRUITESListTextBlock&      setLocationY(uint8_t locationYVal);
            uint8_t                     getLocationY();

            XTRUITESListTextBlock&      setHeight(uint8_t heightVal);
            uint8_t                     getHeight();

            XTRUITESListTextBlock&      setWidthItem(uint8_t widthItemVal);
            uint8_t                     getWidthItem();

            XTRUITESListTextBlock&      setHeightItem(uint8_t heightItemVal);
            uint8_t                     getHeightItem();

            XTRUITESListTextBlock&      setWidth(uint8_t widthVal);
            uint8_t                     getWidth();
            XTRUITESListTextBlock&      addItem(XTRUITESListTextBlockItem*);

            XTRUITESListTextBlock&      populateInterface(XTRUITES* interface);

            uint8_t                     keyPress(uint8_t key);
    };


} /* namespace: qb50 */


#endif /* _QB50_LIST_TEXTBLOCK_H_ */


/*EoF*/
