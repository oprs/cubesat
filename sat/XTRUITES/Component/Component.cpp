/**
 *  @file       Component.cpp
 *  @brief      Model de page pour XTRUITES (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.3
 *  @date       13/05/2015 - 12/06/2015
 */

#include "Component.h"

using namespace std;
using namespace qb50::XTRUITES;


Component::Component()
{
}

Component::~Component()
{
}

Component& Component::setName(std::string nameVal)
{
    _name= nameVal;
    return *this;
}

std::string Component::getName()
{
    return _name;
}


Component& Component::setCollection(ComponentCollection* componentCollectionVal)
{
    _componentCollection= componentCollectionVal;
    return *this;
}

ComponentCollection* Component::getCollection()
{
    return _componentCollection;
}

Component& Component::setParent(Component* parentVal)
{
    _parent= parentVal;
    return *this;
}

Component* Component::getParent( void )
{
    return _parent;
}

bool Component::hasParent( void )
{
    return (_parent != nullptr);
}


Component& Component::addChildren(component_children_pair_t item)
{
    if ( _childrenCollection.find(item.first) != _childrenCollection.end() )
    {
        throw "XTRUITES::Component -> Redundant name of children";
    }

    _childrenCollection.insert(item);
    item.second->
         setName(item.first)
        .setParent(this);

    return *this;
}

Component& Component::addChildren(Component* childrenVal)
{
    if ( _childrenCollection.find(childrenVal->getName()) != _childrenCollection.end() )
    {
        throw "XTRUITES::Component -> Redundant name of children";
    }

    component_children_pair_t item(childrenVal->getName(), childrenVal);
    _childrenCollection.insert(item);
    item.second->setParent(this);

    return *this;
}


Component* Component::getChildrenByName( std::string nameChildren )
{
    return _childrenCollection[nameChildren];
}

bool Component::hasChildren( void )
{
    return !_childrenCollection.empty();
}

Rectangle* Component::getRegion()
{
    return region;
}

Component& Component::setRegion(Rectangle* regionVal)
{
    region= regionVal;
    return *this;
}

Component& Component::setRegion( Point* locationVal, Size* sizeVal )
{
    region= new Rectangle( locationVal, sizeVal);
    return *this;
}

Component& Component::setRegion( unsigned char xVal, unsigned char yVal, unsigned char widthVal, unsigned char heightVal )
{
    region= new Rectangle( xVal, yVal, widthVal, heightVal);
    return *this;
}

Color* Component::getColor( void )
{
    return color;
}
Component& Component::setColor( Color* colorVal )
{
    color= colorVal;
    return *this;

}
Component& Component::setColor( unsigned char background, unsigned char foreground )
{
    color= new Color( background, foreground );
    return *this;
}



/*EoF*/
