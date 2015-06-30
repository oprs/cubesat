/**
 *  @file       textBlock.cpp
 *  @brief      Contrôle textBlock (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.6
 *  @date       11/05/2015 - 12/06/2015
 */


#include "TextBlock.h"
#include "Page.h"
#include "ListView.h"
#include "../../Container.h"
#include "../../Component/ComponentCollection.h"
#include "../../PageRepertory/PageRepertory.h"
#include "../../XTRUITES.h"
#include "../../EscapeSequences.h"
#include "../../Component/Component.h"
#include <string>
#include <map>

using namespace std;
using namespace qb50::XTRUITES;


void ListView::onLoad( void )
{
    unsigned char ylocation= getRegion()->getLocation()->getY();

    for (component_children_map_t::iterator it = _childrenCollection.begin(); it != _childrenCollection.end(); ++it)
    {
        it->second->getRegion()->getLocation()->y= ylocation;
        ylocation += it->second->getRegion()->getSize()->getHeight();
        it->second->onLoad();
    }
}

void ListView::onUpdate( void )
{

}

void ListView::onUnload( void )
{

}

void ListView::onKeyPress( unsigned char key )
{

}

/*EoF*/
