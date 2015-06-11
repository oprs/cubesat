/**
 *  conditionalPrinter.h
 *  20/05/2015
 */


#ifndef _QB50_CONDITIONAL_PRINTER_H_
#define _QB50_CONDITIONAL_PRINTER_H_


#include "textualInterface.h"


namespace qb50
{


    /**
     *  Conditional printf, enable printf if XTRUITE is currently disable
     */
    extern  int     cpprintf    (const char *format , ...);


    /**
     *  Conditional hexdump, enable hexdump if XTRUITE is currently disable
     */
    extern  void    cphexdump   (const void *addr   , unsigned len);


}; /* namespace: qb50 */


#define  printf     cpprintf
#define  hexdump    cphexdump


#endif /* _QB50_CRC16_H_ */


/*EoF*/
