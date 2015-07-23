#include "TestADCChip.h"
#include "TestADCChannel.h"

using namespace qb50;
using namespace qb50::XTRUITES;

TestADCChip::TestADCChip(MAX111x& chipVal, char const * nameVal)
  : chip(chipVal)
{
  name= nameVal;
}

TestADCChip& TestADCChip::addChannel(qb50::MAX111x::Channel chNumber, char const * name, ConvFormula* convFormula)
{
  if(channel[chNumber] != nullptr)
  {
    delete channel[chNumber];
  }
  channel[chNumber]=  new TestADCChannel  ( this,   chNumber,     name,       convFormula);
  return *this;
}


TestADCChip::~TestADCChip()
{
  for (unsigned char i=0; i<XTRUITES_TEST_ADC_NUMBER_OF_CHANNEL; i++)
  {
    if(channel[i] != nullptr)
    {
      delete channel[i];
      channel[i]= nullptr;
    }
  }
}



/*EoF*/
