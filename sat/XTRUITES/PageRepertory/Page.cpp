/**
 *  @file     Page.cpp
 *  @brief    Model de page (Source)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  2.1
 *  @date     13/05/2015 - 24/07/2015
 */

#include "Page.h"
#include "PageRepertory.h"
#include "../Component/Component.h"
#include "../Component/ComponentCollection.h"

using namespace qb50::XTRUITES;

Page::Page()
{
  _componentCollection= new ComponentCollection(this);
}

Page::~Page()
{
  delete _componentCollection;
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

PageRepertory& Page::getRepertory()
{
    return *_pageRepertory;
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


Page& Page::setRepertory(PageRepertory* pageRepertory)
{
  _pageRepertory= pageRepertory;
  return *this;
}

ComponentCollection& Page::getCollection( void )
{
    return *_componentCollection;
}


void Page::pageNavigate( std::string name)
{
  Page* nextPage= getRepertory().getPageByName(name);
  getRepertory().getContainer().setNextPage(nextPage);
}

void Page::pageNavigate( Page* page)
{
  getRepertory().getContainer().setNextPage(page);
}

void Page::addComponent( Component* compenent)
{
    _componentCollection->addComponent(compenent);
}

void Page::eraseComponent( Component* compenent)
{
    _componentCollection->eraseComponent(compenent);
}

/*EoF*/
