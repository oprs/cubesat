
#include "device/NRZI.h"

using namespace qb50;


NRZI::NRZI()
{
    _backValue = LOW;
}


NRZI::~NRZI()
{

}


Sample NRZI::push(Sample current)
{
   _backValue = (Sample)(_backValue ^ current);
   return _backValue;
}
