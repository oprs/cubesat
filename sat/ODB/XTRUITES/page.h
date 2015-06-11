/**
 *  page.h
 *  13/05/2015
 */


#ifndef _QB50_XTRUITES_PAGE_H_
#define _QB50_XTRUITES_PAGE_H_


#include "textualInterface.h"


#include <string>
#include <map>


namespace qb50
{


    class XTRUITES;


    class XTRUITESPage
    {

        public:
            XTRUITESPage(XTRUITES& _XTRUITESInterfaceVal, std::string _nameVal);

            std::string  getName(void);
            XTRUITES&    getInterface(void);

            virtual void load(void)=0;
            virtual void unload(void)=0;
            virtual uint8_t  keypress(uint8_t /* key */)=0;


        private:
            XTRUITES&   _XTRUITESInterface;
            std::string _name;

    };


} /* namespace: qb50 */


#endif /* _QB50_XTRUITES_PAGE_H_ */


/*EoF*/
