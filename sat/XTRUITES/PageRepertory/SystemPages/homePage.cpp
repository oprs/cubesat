/**
 *  @file       homePage.cpp
 *  @brief      Page d'accueil (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       28/05/2015
 */

#include "homePage.h"
#include "../Component/Control/NavigationMenu.h"

using namespace qb50::XTRUITES;

void homePage::onLoad( void )
{
  menu= new NavigationMenu();
  menu->setLocation(Point(4,4));

  addComponent(menu);

  //            Nom                                       Page cible                    Touche
  menu->addItem("ADC (Power 1/2, ODB et Alim Fipex)"    , "Test ADC"                    ,'a'  );
  menu->addItem("Flash"                                 , "Test Flash"                        );
  menu->addItem("Palette de couleurs escape sequences"  , "Palette de couleurs"               );

  getCollection().loadAllComponents();
}

void homePage::unLoad( void )
{
  getCollection().unloadAllComponents();
  eraseComponent(menu);
  delete menu;
}
