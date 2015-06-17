/**
 *  @file       listTextBlock.cpp
 *  @brief      Contrôle XTRUITES: listTextBlock (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.5
 *  @date       20/05/2015
 */


#include "listTextBlock.h"


using namespace qb50;
using namespace std;


XTRUITESListTextBlockItem::XTRUITESListTextBlockItem(std::string labelVal, XTRUITESInputHandler* inputHandlerVal, uint8_t rowSpanVal)
{
    label=labelVal;
    rowSpan=rowSpanVal;
    inputHandler= inputHandlerVal;
}


std::string                     XTRUITESListTextBlockItem::getLabel()
{
    return label;
}
uint8_t                         XTRUITESListTextBlockItem::getRowSpan()
{
    return rowSpan;
}
XTRUITESInputHandler*           XTRUITESListTextBlockItem::getInputHandler()
{
    return inputHandler;
}
XTRUITESListTextBlockItem&      XTRUITESListTextBlockItem::setLabel(std::string labelVal)
{
    label= labelVal;
    return *this;
}
XTRUITESListTextBlockItem&      XTRUITESListTextBlockItem::setRowSpan(uint8_t rowSpanVal)
{
    rowSpan= rowSpanVal;
    return *this;
}
XTRUITESListTextBlockItem&      XTRUITESListTextBlockItem::setInputHandler(XTRUITESInputHandler* inputHandlerVal)
{
    inputHandler= inputHandlerVal;
    return *this;
}












XTRUITESListTextBlock&  XTRUITESListTextBlock::setLocationX(uint8_t locationXVal)
{
    locationX = locationXVal;
    return *this;
}

uint8_t XTRUITESListTextBlock::getLocationX()
{
  return locationX;
}

XTRUITESListTextBlock&  XTRUITESListTextBlock::setLocationY(uint8_t locationYVal)
{
    locationY= locationYVal;
    return *this;
}

uint8_t XTRUITESListTextBlock::getLocationY()
{
  return locationY;
}


XTRUITESListTextBlock& XTRUITESListTextBlock::setHeight(uint8_t heightVal)
{
    height = heightVal;
    return *this;
}
uint8_t XTRUITESListTextBlock::getHeight()
{
  return height;
}


XTRUITESListTextBlock& XTRUITESListTextBlock::setWidth(uint8_t widthVal)
{
    width = widthVal;
    return *this;
}
uint8_t XTRUITESListTextBlock::getWidth()
{
  return width;
}

XTRUITESListTextBlock& XTRUITESListTextBlock::setHeightItem(uint8_t heightItemVal)
{
    heightItem = heightItemVal;
    return *this;
}
uint8_t XTRUITESListTextBlock::getHeightItem()
{
  return heightItem;
}


XTRUITESListTextBlock& XTRUITESListTextBlock::setWidthItem(uint8_t widthItemVal)
{
    widthItem = widthItemVal;
    return *this;
}
uint8_t XTRUITESListTextBlock::getWidthItem()
{
  return widthItem;
}

XTRUITESListTextBlock& XTRUITESListTextBlock::addItem(XTRUITESListTextBlockItem* listTextBlockItem)
{
    items.push_back(listTextBlockItem);
    return *this;
}


XTRUITESListTextBlock& XTRUITESListTextBlock::display()
{
    uint8_t itemNumber= 0;
    uint8_t itemlocationX = locationX;
    uint8_t itemlocationY = locationY;



    for (auto &item : items) // access by reference to avoid copying
    {
        uint8_t  keyItem = (item->getInputHandler()->getKey() == 0)?((itemNumber < 26)? itemNumber + 'a': '?'):item->getInputHandler()->getKey();

        string text(1, keyItem);

        XTRUITESTextBlock *keyLabel = new XTRUITESTextBlock();
        keyLabel->setLocationX(itemlocationX)
            .setLocationY(itemlocationY)
            .setWidth(2).setHeight( item->rowSpan*heightItem)
            .setText(text)
            .setBackground(background)
            .setForeground(XTRUITES_LIST_TEXTBLOCK_KEY_FOREGROUND).display();

        XTRUITESTextBlock *textLabel = new XTRUITESTextBlock();
        textLabel->setLocationX(itemlocationX+2)
            .setLocationY(itemlocationY)
            .setWidth(widthItem-2)
            .setHeight( item->rowSpan*heightItem)
            .setText(item->label)
            .setBackground(background)
            .setForeground(foreground).display();

        itemNumber++;

        itemlocationY+= item->rowSpan*heightItem;

        if(itemlocationY > height + locationY)
        {
            itemlocationY= locationY;
            itemlocationX+= widthItem;

            if(itemlocationX+widthItem > width + locationX)
            {
                break;
            }
        }
    }


    return *this;

}

uint8_t XTRUITESListTextBlock::keyPress(uint8_t key)
{
    uint8_t eventNumber= 0;

   for (auto &item : items)
   {
        if(item->getInputHandler()->getKey() == key)
        {
            item->getInputHandler()->launch();
            eventNumber++;
        }
   }
   return eventNumber;
}
