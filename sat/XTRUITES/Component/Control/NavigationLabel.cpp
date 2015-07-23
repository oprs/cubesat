/**
 *  @file       textBlock.cpp
 *  @brief      Contrôle textBlock (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.6
 *  @date       11/05/2015 - 12/06/2015
 */

#include <cstring>
#include "NavigationLabel.h"
#include "../../Component/Component.h"
#include "../../PageRepertory/Page.h"
#include "../../EscapeSequences.h"
#include "../../PageRepertory/PageRepertory.h"

using namespace std;
using namespace qb50::XTRUITES;


NavigationLabel::NavigationLabel(char const * nameVal, Page * page, unsigned char key, char const * labelVal)
  : name(nameVal), keyTarget(key)
{
  initialize(page, labelVal);
}


NavigationLabel::NavigationLabel(char const * nameVal, char const * page, unsigned char key, char const * labelVal)
  : name(nameVal), keyTarget(key)
{
  initialize(getCollection().getPage().getRepertory().getPageByName(page), labelVal);
}

void NavigationLabel::initialize( Page * page, char const * labelVal)
{
  keyColor= new Color(XTRUITES_DEFAULT_COLOR_KEY_BACKGROUND, XTRUITES_DEFAULT_COLOR_KEY_FOREGROUND);
  pageTarget= page;

  label= new char[3];

  if(labelVal != nullptr)
  {
    memcpy(label, labelVal, 3);
  }
  else
  {
    label[0]= keyTarget;
    label[1]= '\0';
  }
}

NavigationLabel::~NavigationLabel()
{
  delete    keyColor;
  delete[]  label;
}

void NavigationLabel::onLoad( void )
{
  EscapeSequences::moveCursor(getLocation());

  EscapeSequences::setColor(*keyColor);
  EscapeSequences::write("%-2s ", label);

  EscapeSequences::setColor(getColor());
  EscapeSequences::write("%s", name);
}

void NavigationLabel::onKeyPress( uint8_t key )
{
  if(keyTarget == key)
  {
    getCollection().getPage().pageNavigate(pageTarget);
  }
}
/*EoF*/
