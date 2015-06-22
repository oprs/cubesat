
#include "device/NRZI.h"

using namespace qb50;


NRZI::NRZI()
{ _backValue = 0; }


NRZI::~NRZI()
{ ; }


bool NRZI::push(bool current)
{
   _backValue = !(_backValue ^ current);
   return _backValue;
}

