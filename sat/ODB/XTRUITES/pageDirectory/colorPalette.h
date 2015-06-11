/**
 *  colorPalette.h
 *  28/25/2015
 */


#ifndef _QB50_XTRUITES_COLOR_PAGE_H_
#define _QB50_XTRUITES_COLOR_PAGE_H_


#include "../textualInterface.h"


namespace qb50
{


    class XTRUITESListTextBlock;

    class XTRUITEScolorPalette : public XTRUITESPage
    {


        public:
            XTRUITEScolorPalette(XTRUITES& _XTRUITESInterfaceVal);

            void load(void);
            void unload(void);
            uint8_t  keypress(uint8_t key);
    };


    extern void writeColorPaletteItem(XTRUITES& interface, uint8_t x, uint8_t y, uint8_t color);


} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_COLOR_PAGE_H_ */


/*EoF*/
