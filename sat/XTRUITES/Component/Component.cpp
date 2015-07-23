/**
 *  @file       Component.cpp
 *  @brief      Model de page pour XTRUITES (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */

#include "Component.h"
#include "ComponentCollection.h"

using namespace std;
using namespace qb50::XTRUITES;


Component::Component()
  : _region(), _color()
{
}

Component::~Component()
{
}

ComponentCollection& Component::getCollection()
{
  return *_componentCollection;
}

Component& Component::setCollection(ComponentCollection* collection)
{
  _componentCollection= collection;
  return *this;
}
Component& Component::setParent(Component* parentVal)
{
    _parent= parentVal;
    return *this;
}

Component& Component::getParent( void )
{
    return *_parent;
}

bool Component::hasParent( void )
{
    return (_parent != nullptr);
}


Component& Component::addChildren(Component* componentVal)
{
    _childrenCollection.push_back(componentVal);
    componentVal->setParent(this);
    componentVal->setCollection(_componentCollection);
    return *this;
}


bool Component::hasChildren( void )
{
    return !_childrenCollection.empty();
}


Rectangle& Component::getRegion( void )
{
    return _region;
}

Point& Component::getLocation( void )
{
    return _region.getLocation();
}

Color& Component::getColor( void )
{
    return _color;
}

Size& Component::getSize( void )
{
    return _region.getSize();
}

Component& Component::setSize( const Size& sizeVal)
{
  _region.setSize(sizeVal);
  return *this;
}

void Component::onLoad( void )
{
  onLoadChildren();
}
void Component::onUpdate( void )
{
  onUpdateChildren();
}
void Component::onUnload( void )
{
  onUnloadChildren();
}
void Component::onKeyPress( uint8_t key )
{
  onKeyPressChildren(key);
}

Component& Component::setLocation( const Point& locationVal)
{
    _region.setLocation(locationVal);
    return *this;
}

Component& Component::setColor( const Color& colorVal)
{
    _color= colorVal;
    return *this;
}

Component& Component::setRegion( const Rectangle& regionVal)
{
  _region= regionVal;
  return *this;
}
void Component::onLoadChildren( void )
{
  for (auto & element : _childrenCollection)
  {
    element->onLoad();
  }
}

void Component::onUpdateChildren( void )
{
  for (auto & element : _childrenCollection)
  {
    element->onUpdate();
  }
}

void Component::onUnloadChildren( void )
{
  for (auto & element : _childrenCollection)
  {
    element->onUnload();
  }
}

void Component::onKeyPressChildren( uint8_t key )
{
  for (auto & element : _childrenCollection)
  {
    element->onKeyPress(key);
  }
}

std::vector<Component*> Component::getChildrenCollection( void )
{
  return _childrenCollection;
}

/*EoF*/
