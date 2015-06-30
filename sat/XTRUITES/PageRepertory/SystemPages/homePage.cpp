/**
 *  @file       homePage.cpp
 *  @brief      Page d'accueil (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       28/05/2015
 */


#include "homePage.h"

#include <string.h>
#include "../Component/Component.h"
#include "../Component/ComponentCollection.h"
#include "../Component/Control/TextBlock.h"
#include "../Component/Control/ListView.h"


using namespace std;
using namespace qb50::XTRUITES;

homePage::homePage(PageRepertory* pageRepertoryVal) : Page(pageRepertoryVal)
{
    TextBlock* testtt= new TextBlock();
    testtt->setText("Bonjour").setColor(12, 15).setRegion(12,12,12,12);

    _componentCollection->add(component_collection_pair_t("test", testtt));

    ListView* test2= new ListView();
    test2->setRegion(1,1,1,1);

    TextBlock* item1= new TextBlock();
    item1->setText("Bonjour").setColor(12, 15).setRegion(0,0,10,1);
    test2->addChildren(component_children_pair_t("tt", item1));

    TextBlock* item2= new TextBlock();
    item2->setText("Bonjour").setColor(12, 15).setRegion(0,0,10,1);
    test2->addChildren(component_children_pair_t("ttt", item2));

    TextBlock* item3= new TextBlock();
    item3->setText("Bonjour").setColor(12, 15).setRegion(0,0,10,1);
    test2->addChildren(component_children_pair_t("tt", item3));

    _componentCollection->add(component_collection_pair_t("test3", test2));

}

/*
void homePage::onLoad( void )
{
}

void homePage::onUpdate( void )
{
}

void homePage::onUnload( void )
{
}

void homePage::onKeyPress( uint8_t key )
{
}

*/



/*
// Write location
XTRUITEShomePage::XTRUITEShomePage(XTRUITES& _XTRUITESInterfaceVal)
    : XTRUITESPage(_XTRUITESInterfaceVal, "Home") { }


void XTRUITEShomePage::load(void)
{

    getInterface().clearContent();

	menuList = new XTRUITESListTextBlock();
	menuList->setHeight(16)
        .setWidth(76)
        .setLocationX(2)
        .setLocationY(2)
        .setWidthItem(76/3)
        .setHeightItem(1);

    // Define menu                                  label                                            key    instructions (lambda function)                                                              Row span
    menuList->addItem(new XTRUITESListTextBlockItem("ADC Value",            new XTRUITESInputHandler('a',   [&](){ (&getInterface())->loadPage(new XTRUITESADC_TestPage ( getInterface() )); } )        , 1     ))
             .addItem(new XTRUITESListTextBlockItem("Color Palette",        new XTRUITESInputHandler('b',   [&](){ (&getInterface())->loadPage(new XTRUITEScolorPalette ( getInterface() )); } )        , 1     ))
             .addItem(new XTRUITESListTextBlockItem("Refresh",              new XTRUITESInputHandler('c',   [&](){ (&getInterface())->loadPage(new XTRUITEShomePage     ( getInterface() )); } )        , 1     ));

    menuList->display();
}

void XTRUITEShomePage::unload(void)
{
}

uint8_t  XTRUITEShomePage::keypress(uint8_t key)
{
    menuList->keyPress(key);
    return 0 ;
}
*/
