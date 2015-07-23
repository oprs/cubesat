/**
 *  @file       PageRepertory.cpp
 *  @brief      Répertoire de page (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    2.1
 *  @date       13/05/2015 - 24/07/2015
 */

#include "Page.h"
#include "../Container.h"

// Page
#include "SystemPages/homePage.h"
#include "SystemPages/quitPage.h"
#include "Flash/FlashPage.h"
#include "ADC/ADCPage.h"
#include "Utilities/ColorPalette.h"

using namespace qb50::XTRUITES;

PageRepertory::PageRepertory()
{
    //  Ajoutez ici les pages
    //      Nom                     Instance de la page
    addPage("Home",                 new homePage()                  );
    addPage("Quit",                 new quitPage()                  );
    addPage("Test Flash",           new FlashPage()                 );
    addPage("Test ADC",             new ADCPage()                   );
    addPage("Palette de couleurs",  new colorPalettePage()          );
}

PageRepertory::~PageRepertory()
{
    for (page_repertory_map_t::iterator it = _repertory.begin(); it != _repertory.end(); ++it)
    {
        delete it->second;
    }
}

PageRepertory& PageRepertory::addPage(std::string name, Page* page)
{
    if ( _repertory.find(name) != _repertory.end() )
    {
        throw "XTRUITES::PageRepertory - Redundant name of page";
    }

    _repertory.insert(page_repertory_item_t(name, page));
    page->setRepertory(this).setName(name);
    return *this;
}

Page* PageRepertory::getPageByName(std::string namePage)
{
	return _repertory[namePage];
}


Container& PageRepertory::getContainer()
{
	return *_container;
}

PageRepertory& PageRepertory::setContainer(Container* container)
{
  _container= container;
	return *this;
}

/*EoF*/
