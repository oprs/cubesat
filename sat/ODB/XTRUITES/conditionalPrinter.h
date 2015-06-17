/**
 *  @file       conditionalPrinter.h
 *  @brief      Ecriture conditionnelle (En-tête)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       20/05/2015
 */


#ifndef _QB50_CONDITIONAL_PRINTER_H_
#define _QB50_CONDITIONAL_PRINTER_H_


#include "textualInterface.h"


namespace qb50
{


    /// @brief  Conditional printf, écrit si XTRUITE n'est pas actif
    extern  int     cpprintf    (const char *format , ...);

    /// @brief  Conditional hexdump, écrit si XTRUITE n'est pas actif
    extern  void    cphexdump   (const void *addr   , unsigned len);


}; /* namespace: qb50 */


#define  printf     cpprintf
#define  hexdump    cphexdump


#endif /* _QB50_CRC16_H_ */


/*EoF*/
