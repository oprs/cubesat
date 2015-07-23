/**
 *  @file     FlashPage.cpp
 *  @brief    Page testant les méthode d'écriture, de lecture et d'effacement sur la RAM (Source)
 *  @author   Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version  1.0
 *  @date     08/07/2015
 */

#include "FlashPage.h"
#include "FlashWatch.h"

using namespace std;
using namespace qb50::XTRUITES;

FlashPage::FlashPage() : Page()
{
  // Crée dans le constructeur pour ne pas refaire les tests
  // à chaque chargement de page

  FlashWatch* watch1= new FlashWatch();
  watch1->setLocation(Point(1,1));

  FlashWatch* watch2= new FlashWatch();
  watch2->setLocation(Point(1,20));

  addComponent(watch1);
  addComponent(watch2);
}

/*EoF*/
