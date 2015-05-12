/**
 *  CRC16_CCITT.h
 *  27/04/2015
 */


#ifndef _QB50_CRC16_H_
#define _QB50_CRC16_H_


#include "system/qb50.h"


namespace qb50
{


    /**
     * crc16_ccitt
     *
     * CRC-16-CCITT calculator
     *
     * From: http://www.menie.org/georges/embedded/crc16.html
     * On-line calculator: http://www.lammertbies.nl/comm/info/crc-calculation.html
     */
    extern uint16_t crc16_ccitt( const uint8_t *buf, size_t len );


}; /* namespace: qb50 */


#endif /* _QB50_CRC16_H_ */


/*EoF*/
