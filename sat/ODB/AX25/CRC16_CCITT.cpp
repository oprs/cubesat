/**
 *  CRC16_CCITT.cpp
 *  27/04/2015
 */

#include "CRC16_CCITT.h"

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
    uint16_t crc16_ccitt(uint8_t *buf, uint16_t len)
    {
        register uint16_t counter;
        register uint16_t crc = 0;
        for(counter = 0; counter < len; counter++)
        {
            crc = (crc<<8) ^ crc16tab[((crc>>8) ^ *(uint8_t *)buf++)&0x00FF];
        }
        return crc;
    }
}; /* namespace: qb50 */

/*EoF*/
