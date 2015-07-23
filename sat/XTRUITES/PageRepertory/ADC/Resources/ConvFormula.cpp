#include "ConvFormula.h"

using namespace qb50::XTRUITES;

ConvFormula::ConvFormula(char const * unitVal, float coefficientVal, float offsetVal)
  : unit( unitVal ), coefficient( coefficientVal ), offset( offsetVal )
{ ; }

ConvFormula::~ConvFormula()
{ ; }

float ConvFormula::conv(unsigned char digitalValue)
{
  return coefficient*digitalValue+offset;
}

/*EoF*/
