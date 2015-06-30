/**
 *  @file       config.cpp
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       23/06/2015
 */

#include "config.h"
#include <sys/types.h>
#include "system/qb50.h"




using namespace std;
using namespace qb50::XTRUITES;

ssize_t UART3_syscalls::ch_write(const void *x, size_t len)
{
    return qb50::UART3.write( x, len );
}



ssize_t UART3_XTRUITES::ch_write(const void *x, size_t len)
{
    return qb50::UART3.write( x, len );
}
