/**
 *  @file       textBlock.cpp
 *  @brief      Contrôle textBlock (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.6
 *  @date       11/05/2015 - 12/06/2015
 */


#include "ListView.h"
#include "../../Component/Component.h"

using namespace std;
using namespace qb50::XTRUITES;

void ListView::onLoad( void )
{
  unsigned char ylocation= getLocation().getY();
  unsigned char xlocation= getLocation().getX();
  unsigned char heightAvailable= getSize().getHeight();

  for (auto &child : getChildrenCollection())
  {
    child->getLocation().y= ylocation;
    child->getLocation().x= xlocation;
    child->getRegion()._size= Size(getSize().getWidth(), heightAvailable);

    child->onLoad();

    unsigned char childHeight= child->getSize().getHeight();

    ylocation += childHeight;
    heightAvailable -= childHeight;
  }
}



/*EoF*/
