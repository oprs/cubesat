/**
 *  @file       page.cpp
 *  @brief      Model de page pour XTRUITES (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */

#include "Page.h"
#include "../Component/Component.h"
#include "../Component/ComponentCollection.h"


using namespace std;
using namespace qb50::XTRUITES;


Page::Page(PageRepertory* pageRepertoryVal)
{
   _pageRepertory =pageRepertoryVal;
   _componentCollection= new ComponentCollection(this);
}

Page::~Page()
{
}

Page& Page::setName(std::string nameVal)
{
    _name= nameVal;
    return *this;
}

std::string Page::getName()
{
    return _name;
}


Page& Page::setRepertory(PageRepertory* pageRepertoryVal)
{
    _pageRepertory= pageRepertoryVal;
    return *this;
}

PageRepertory* Page::getRepertory()
{
    return _pageRepertory;
}

void Page::onLoad( void )
{
    _componentCollection->loadAllComponents();
}

void Page::onUpdate( void )
{
    _componentCollection->updateAllComponents();
}

void Page::onUnload( void )
{
    _componentCollection->unloadAllComponents();
}

void Page::onKeyPress( unsigned char key )
{
    _componentCollection->keyPressAllComponents(key);
}



ComponentCollection* Page::getCollection( void )
{
    return _componentCollection;
}

/*EoF*/
