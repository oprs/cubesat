#include "TestADCChannel.h"
#include "TestADCChip.h"

using namespace qb50::XTRUITES;

TestADCChannel::TestADCChannel(TestADCChip* ADCVal, qb50::MAX111x::Channel chNumberVal, char const * nameVal, ConvFormula* convFormulaVal)
  : ADC(ADCVal), convFormula(convFormulaVal)
{
  name= nameVal;
  chNumber= chNumberVal;
}

/*EoF*/
