/**
 * @file    colorPalette.cpp
 * @brief   Page affichant une palette de 256 couleurs (Source).
 * @author  Jérôme skoda <jerome.skoda@hotmail.fr>
 * @version 1.4
 * @date    28/05/2015 - 12/06/2015
 */


#include "colorPalette.h"


using namespace qb50;
using namespace std;


void qb50::writeColorPaletteItem(XTRUITES& interface, uint8_t x, uint8_t y, uint8_t color)
{
    stringstream ss;//create a stringstream
    ss << (int16_t)color;


   string text= ss.str();


    XTRUITESTextBlock *colorDisplay= new XTRUITESTextBlock();
        colorDisplay->
             setLocationX(x)    .setLocationY(y)
            .setWidth(1)        .setHeight(1)
            .setText(" ");

    colorDisplay->background= color;
    colorDisplay->display();

    XTRUITESTextBlock *colorNumber= new XTRUITESTextBlock();
        colorNumber->
             setLocationX(x+1)  .setLocationY(y)
            .setWidth(3)        .setHeight(1)
            .setText(text).display();
}


// Write location
XTRUITEScolorPalette::XTRUITEScolorPalette(XTRUITES& _XTRUITESInterfaceVal)
    : XTRUITESPage(_XTRUITESInterfaceVal, "Home") { }


void XTRUITEScolorPalette::load(void)
{
    getInterface().clearContent();

    for(uint8_t color=0; color< 16; color++)
    {
        writeColorPaletteItem(getInterface(), 1+color*4, 2, color);
    }
    for(uint8_t line=0; line< 6; line++)
    {

        for(uint8_t colorRow=0; colorRow< 18; colorRow++)
        {
            uint8_t color= line*36 + 16 + colorRow;
            writeColorPaletteItem(getInterface(), (1+colorRow*4 + ((colorRow/6)*3)) , 4+line, color);
        }
    }
    for(uint8_t line=0; line< 6; line++)
    {

        for(uint8_t colorRow=18; colorRow< 36; colorRow++)
        {
            uint8_t color= line*36 + 16 + colorRow;
            uint8_t xLocation= (1+(colorRow-18)*4 + (((colorRow-18)/6)*3));
            uint8_t yLocation= 11+line;

            writeColorPaletteItem(getInterface(), xLocation ,yLocation , color);
        }
    }
    for(uint8_t color=232, yLocation=18, xLocation=0; color != 0; color++)
    {
        xLocation= 1+(color-232)*4;
        if(color >= 251)
        {
            yLocation= 19;
            xLocation= 1+(color-251)*4;
        }
        writeColorPaletteItem(getInterface(), xLocation, yLocation, color);
    }
}


void XTRUITEScolorPalette::unload(void)
{
}

uint8_t  XTRUITEScolorPalette::keypress(uint8_t key)
{

    return 0;
}
