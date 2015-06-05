
#include "device/FIFO.h"
#include "device/AX25Out.h"

using namespace qb50;


FIFO::FIFO()
{

}

FIFO::~FIFO()
{

}

void FIFO::push( Sample bit)
{
    (void)printf("%d", bit);
}
