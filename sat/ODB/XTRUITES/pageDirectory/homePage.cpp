/**
 *  @file       homePage.cpp
 *  @brief      Page d'accueil (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       28/05/2015
 */
#include "homePage.h"
#include <functional>

using namespace qb50;
using namespace std;

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
