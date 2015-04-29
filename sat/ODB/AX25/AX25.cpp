/**
 *  File: AX25.cpp
 *  27/04/2015
 */

#include "AX25.h"
#include "CRC16_CCITT.h"

using namespace qb50;


/**
 *  StringToAddressAX25
 *
 *  Change string to address with AX25 protocol.
 *
 *  If character in string is not a capital letter and not a number, it's change to space character
 *  All character is left shift. The string output has length of 6 characters.
 *
 *  Example: "AbC3"       (4  bytes) is convert to "A C3  "<<1 (6 bytes)
 *           "GRâ€ liçlà" (10 bytes) is convert to "GR    "<<1 (6 bytes)
 *
 *  @author     Jérôme Skoda    <jerome.skoda@hotmail.fr>
 *  @version    1.1             (22/04/2015)
 */
void StringToAddressAX25(uint8_t *dst, uint8_t *adress)
{
    // Adresse 6 caractére maximum
    for(int n=0; n < 6; ++n)
    {
        // [A-Z0-9] sinon ' '
        if(((((uint8_t*)adress)[n] >= 'A') && ((uint8_t*)adress)[n] <= 'Z') || ((((uint8_t*)adress)[n] >= '0') && ((uint8_t*)adress)[n] <= '9'))
        {
            // Ecriture de la [A-Z0-9] << 1
            ((uint8_t*)dst)[n]= ((uint8_t*)adress)[n] << 1;
        }
        else
        {
            // Ecriture ' ' << 1
            ((uint8_t*)dst)[n]= ' ' << 1;
        }
    }
}

/**
 *  writeHeader
 *
 *  Write header section 16 bytes with AX25 protocol
 *  ╔══════════════════╦══════════════════╦════════╦═════════════╦═════════╦═════════════════════╗
 *  ║ Destination name ║ destination SSID ║ Source ║ Source SSID ║ Control ║ Protocol identifier ║
 *  ╠══════════════════╬══════════════════╬════════╬═════════════╬═════════╬═════════════════════╣
 *  ║ bytes 1-6        ║ 7                ║ 8-13   ║ 14          ║ 15      ║ 16                  ║
 *  ╚══════════════════╩══════════════════╩════════╩═════════════╩═════════╩═════════════════════╝
 *
 *  @author     Jérôme Skoda    <jerome.skoda@hotmail.fr>
 *  @version    1.3             (24/04/2015)
 */
size_t PacketAX25::writeHeader(uint8_t  *dst)
{
    // Write address destination octet 0-5
    StringToAddressAX25(dst, destination.address);

    // Write CCR/SSID octet 6
    ((uint8_t*)dst)[6]=  (
                          // CCR 7-5 bits
                          ((destination.CCR  & 0x07) << 5) +
                          // SSID 4-1 bits
                          ((destination.SSID & 0x0F) << 1)
                          // '0' last bit required
                         ) & 0xFE;

    // Write address destination octet 7-13
    StringToAddressAX25(&(((uint8_t*)dst)[7]), source.address);

    // Write CCR/SSID octet 14
    ((uint8_t*)dst)[13]= (
                          // CCR 7-5 bits
                          ((source.CCR  & 0x07) << 5) +
                          // SSID 4-1 bits
                          ((source.SSID & 0x0F) << 1)
                          // '1' last bit of address section
                         ) | 0x01;

    // Write control field, look AX25_control_Mode enumerate
    ((uint8_t*)dst)[14]= controle;

    // Write control field, look AX25_PID_Mode enumerate
    ((uint8_t*)dst)[15]= PID;

    return (size_t)16;
}

/**
 *  writePacket
 *
 *  Write transfer frame format with AX25 protocol
 * ╔══════════╦══════════╦═════════╦════════╦════════════════════╦═════════╦══════════╗
 * ║   Flag   ║ Address  ║ Control ║  PID   ║    Information     ║   FCS   ║   Flag   ║
 * ╠══════════╬══════════╬═════════╬════════╬════════════════════╬═════════╬══════════╣
 * ║ 01111110 ║ 112 Bits ║ 8 Bits  ║ 8 Bits ║ N*8 Bits (32-2048) ║ 16 Bits ║ 01111110 ║
 * ╚══════════╩══════════╩═════════╩════════╩════════════════════╩═════════╩══════════╝
 *
 *  @author     Jérôme Skoda    <jerome.skoda@hotmail.fr>
 *  @version    1.2             (24/04/2015 - 28/04/2015)
 */
size_t PacketAX25::writePacket(uint8_t  *dst, uint8_t *src, size_t src_len )
{
    size_t cursor= 0;

    // Write Flag
    ((uint8_t*)dst)[cursor]= 0x7E;
    cursor++;

    // Write Header
    cursor+= writeHeader(&((uint8_t*)dst)[cursor]);

    // Write Information
    cursor+= writeInformation(&((uint8_t*)dst)[cursor], src, src_len);

    // Write CRC-16-CCITT
    uint16_t crc = crc16_ccitt(&((uint8_t*)dst)[1], cursor-1);
    ((uint8_t*)dst)[cursor]= crc >> 8;
    cursor++;
    ((uint8_t*)dst)[cursor]= crc & 0x00ff;
    cursor++;

    // Write End Flag
    ((uint8_t*)dst)[cursor]= 0x7E;
    cursor++;

    return cursor;
}


/**
 *  writeInformation
 *
 *  Write information/data field. AX.25 support 256 bytes maximum.
 *  In XCubeSat the maximum supported is 128 bytes.
 *
 *  @author     Jérôme Skoda    <jerome.skoda@hotmail.fr>
 *  @version    1.0             (27/04/2015)
 */
size_t PacketAX25::writeInformation(uint8_t  *dst, uint8_t *src, size_t src_len )
{
    uint16_t length;

    // Write data
    for(length=0; (length < 128 && length < src_len) ; length++)
    {
        ((uint8_t*)dst)[length]= ((uint8_t*)src)[length];
    }

    return (size_t)length;
}

/*EoF*/
