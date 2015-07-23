/**
 *  @file       textualInterface.cpp
 *  @brief      Gestion comportemental de l'interface (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.9
 *  @date       11/05/2015 - 12/06/2015
 */

#include "ADCWatch.h"
#include "XTRUITES.h"
#include <stdio.h>
#include <string.h>
#include "system/qb50.h"
#include "../../EscapeSequences.h"
#include "TestADCChip.h"
#include "TestADCChannel.h"
#include "ADCChannelWatch.h"

using namespace qb50;
using namespace qb50::XTRUITES;

ADCWatch::ADCWatch(TestADCChip* chip)
  : _chip(chip)
{
}

void ADCWatch::onLoad( void )
{
  Point p= getLocation();

  EscapeSequences::moveCursor(p.getX()+(64-strlen(_chip->name))/2,p.getY());
  EscapeSequences::write("%s", _chip->name);

  p.y+=2;
  p.x+=6;
  EscapeSequences::moveCursor(p);
  EscapeSequences::write(      "┌────────────┬─────────────┬──────┬──────────────────────┐");

  p.y++;
  EscapeSequences::moveCursor(p);
  EscapeSequences::write(      "│    NAME    │     HEX     │  VAL │                      │");

  p.y++;p.x-=6;
  EscapeSequences::moveCursor(p);
  EscapeSequences::write("┌─────┼────────────┼─────────────┼──────┼──────────────────────┤");
  p.y++;
  for (uint8_t channel = 0; channel < 8; channel++)
  {
    if(!_chip->channel[channel]) continue;
    ADCChannelWatch* channelWatch= new ADCChannelWatch(_chip->channel[channel]);
    channelWatch->setLocation(p);
    addChildren(channelWatch);
    p.y++;
  }
  EscapeSequences::moveCursor(p);
  EscapeSequences::write("└─────┴────────────┴─────────────┴──────┴──────────────────────┘");

  onLoadChildren();
}

void ADCWatch::onUpdate( void )
{
  onUpdateChildren();
}

/*EoF*/
