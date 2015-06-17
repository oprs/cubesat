/**
 *  @file       page.cpp
 *  @brief      Model de page pour XTRUITES (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */


#include "textualInterface.h"


using namespace qb50;
using namespace std;


XTRUITESPage::XTRUITESPage(XTRUITES& _XTRUITESInterfaceVal, std::string _nameVal)
    : _XTRUITESInterface(_XTRUITESInterfaceVal), _name(_nameVal) { }


std::string XTRUITESPage::getName(void)
{
    return _name;
}


XTRUITES& XTRUITESPage::getInterface(void)
{
    return _XTRUITESInterface;
}


/*EoF*/
