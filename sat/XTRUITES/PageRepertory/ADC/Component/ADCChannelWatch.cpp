/**
 *  @file       textualInterface.cpp
 *  @brief      Gestion comportemental de l'interface (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.9
 *  @date       11/05/2015 - 12/06/2015
 */

#include "ADCChannelWatch.h"
#include "TestADCChannel.h"
#include "XTRUITES.h"
#include "TestADCChip.h"
#include "system/qb50.h"
#include "../../EscapeSequences.h"

#include "ConvFormula.h"

using namespace qb50;
using namespace qb50::XTRUITES;

ADCChannelWatch::ADCChannelWatch(TestADCChannel* channel)
  :  _channel(channel)
{
}

void ADCChannelWatch::onLoad( void )
{
  EscapeSequences::moveCursor(getLocation());
  EscapeSequences::write("│ CH%01d │ %-10s │ 00 00 00 00 │ 0000 │                      │", _channel->chNumber, _channel->name);
}



void ADCChannelWatch::onUpdate( void )
{
	MAX111x::ConvResp currentConv;
	_channel->ADC->chip.conv(_channel->chNumber, &currentConv);

  //currentConv.rb3=  _lastConv.rb3 + 1;
  //currentConv.rb4=  _lastConv.rb4 + 1;


  if(currentConv.rb1 != _lastConv.rb1 || currentConv.rb2 != _lastConv.rb2 || currentConv.rb3 != _lastConv.rb3 || currentConv.rb4 != _lastConv.rb4)
  {
      unsigned char valueNum = ((int)(currentConv.rb3 << 2) | (int)(currentConv.rb4 >> 6));

      EscapeSequences::moveCursor(Point(getLocation().getX()+21, getLocation().getY()));
			EscapeSequences::write("%02X %02X %02X %02X", currentConv.rb1, currentConv.rb2, currentConv.rb3, currentConv.rb4);

      EscapeSequences::moveCursor(Point(getLocation().getX()+35, getLocation().getY()));
			EscapeSequences::write("%4d", valueNum);

        EscapeSequences::moveCursor(Point(getLocation().getX()+42, getLocation().getY()));
      if(_channel->convFormula != nullptr)
      {
        EscapeSequences::write("%04.4f %-10s", _channel->convFormula->conv(valueNum), _channel->convFormula->unit);
      }
      else
      {
        EscapeSequences::write("convFormula undefined");
      }

      _lastConv= currentConv;
  }

}
