
/**
 *  @file       PageRepertory.cpp
 *  @brief      Model de page pour XTRUITES (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */

#include "../PageRepertory/Page.h"
#include "Component.h"
#include "ComponentCollection.h"
#include <algorithm>

using namespace qb50::XTRUITES;


ComponentCollection::ComponentCollection(Page* pageVal)
{
    _page= pageVal;
}

ComponentCollection::~ComponentCollection()
{
  for (auto &item : _collection) // access by reference to avoid copying
  {
    delete item;
  }
}

ComponentCollection& ComponentCollection::addComponent(Component* component)
{
    _collection.push_back(component);
    component->setCollection(this);
    return *this;
}


ComponentCollection& ComponentCollection::setPage(Page* pageVal)
{
    _page= pageVal;
    return *this;
}

Page& ComponentCollection::getPage()
{
	return *_page;
}

void ComponentCollection::loadAllComponents()
{
  for (auto &item : _collection) // access by reference to avoid copying
  {
    item->onLoad();
  }
}


void ComponentCollection::updateAllComponents()
{
  for (auto &item : _collection) // access by reference to avoid copying
  {
    item->onUpdate();
  }
}
void ComponentCollection::unloadAllComponents()
{
  for (auto &item : _collection) // access by reference to avoid copying
  {
    item->onUnload();
  }
}

void ComponentCollection::keyPressAllComponents( unsigned char key )
{
  for (auto &item : _collection) // access by reference to avoid copying
  {
    item->onKeyPress( key );
  }
}


ComponentCollection& ComponentCollection::eraseComponent(Component* component)
{
  _collection.erase(std::remove(_collection.begin(), _collection.end(), component), _collection.end());
  return *this;
}

/*EoF*/
