/**
 *  @file       textBlock.cpp
 *  @brief      Contrôle textBlock (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.6
 *  @date       11/05/2015 - 12/06/2015
 */

#include "NavigationMenu.h"
#include "NavigationLabel.h"
#include "../../PageRepertory/PageRepertory.h"
#include "../../PageRepertory/Page.h"

using namespace qb50::XTRUITES;


void NavigationMenu::addItem(char const * nameVal, Page * page, unsigned char key, char const * labelVal)
{
   static unsigned char lastKey= 0;

  if(key != 0)
  {
    lastKey= key;
  }
  else
  {
    lastKey++;
  }

  NavigationLabel* item= new NavigationLabel(nameVal, page, lastKey, labelVal);
  addChildren(item);
}

void NavigationMenu::addItem(char const * nameVal, char const * page, unsigned char key, char const * labelVal)
{
  Page* pageTarget= getCollection().getPage().getRepertory().getPageByName(std::string(page));
  addItem(nameVal, pageTarget, key, labelVal);
}


void NavigationMenu::onLoad( void )
{
  unsigned char ylocation= getLocation().getY();
  unsigned char xlocation= getLocation().getX();

  for (auto &child : getChildrenCollection())
  {
    child->getLocation().y= ylocation;
    child->getLocation().x= xlocation;
    child->onLoad();
    ylocation++;
  }
}



/*EoF*/
