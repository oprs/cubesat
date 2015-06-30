
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


using namespace qb50::XTRUITES;


ComponentCollection::ComponentCollection(Page* pageVal)
{
    _page= pageVal;
}

ComponentCollection::~ComponentCollection()
{
    for (component_collection_map_t::iterator it = _collection.begin(); it != _collection.end(); ++it)
    {
        delete it->second;
    }
}

ComponentCollection& ComponentCollection::add(component_collection_pair_t item)
{
    _collection.insert(item);
    item.second->
         setName(item.first)
        .setCollection(this);
    return *this;
}

Component* ComponentCollection::getComponentByName(std::string nameComponent)
{
	return _collection[nameComponent];
}

ComponentCollection& ComponentCollection::setPage(Page* pageVal)
{
    _page= pageVal;
    return *this;
}

Page* ComponentCollection::getPage()
{
	return _page;
}

void ComponentCollection::loadAllComponents()
{
    for (component_collection_map_t::iterator it = _collection.begin(); it != _collection.end(); ++it)
    {
        it->second->onLoad();
    }
}


void ComponentCollection::updateAllComponents()
{

    for (component_collection_map_t::iterator it = _collection.begin(); it != _collection.end(); ++it)
    {
        it->second->onUpdate();
    }
}
void ComponentCollection::unloadAllComponents()
{

    for (component_collection_map_t::iterator it = _collection.begin(); it != _collection.end(); ++it)
    {
        it->second->onUnload();
    }
}

void ComponentCollection::keyPressAllComponents( unsigned char key )
{

    for (component_collection_map_t::iterator it = _collection.begin(); it != _collection.end(); ++it)
    {
        it->second->onKeyPress( key );
    }
}

/*EoF*/
