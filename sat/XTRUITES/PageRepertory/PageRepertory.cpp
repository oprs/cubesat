/**
 *  @file       PageRepertory.cpp
 *  @brief      Model de page pour XTRUITES (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */


#include "PageRepertory.h"
#include "Page.h"
#include "SystemPages/SystemPages.h"


using namespace qb50::XTRUITES;


PageRepertory::PageRepertory(Container* containerVal)
{
    _container= containerVal;

    //  Ajoutez ici les pages
    //                          Nom             Instance de la page
    add(page_repertory_item_t(  "Home",         new homePage(this)                      ));
}

PageRepertory::~PageRepertory()
{
    for (page_repertory_map_t::iterator it = _repertory.begin(); it != _repertory.end(); ++it)
    {
        delete it->second;
    }
}

PageRepertory& PageRepertory::add(page_repertory_item_t item)
{
    _repertory.insert(item);
    item.second->
         setName(item.first)
        .setRepertory(this);
    return *this;
}

Page* PageRepertory::getPageByName(std::string namePage)
{
	return _repertory[namePage];
}

PageRepertory& PageRepertory::setContainer(Container* containerVal)
{
    _container= containerVal;
    return *this;
}

Container* PageRepertory::getContainer()
{
	return _container;
}


/*EoF*/
