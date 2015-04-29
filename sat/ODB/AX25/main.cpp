/**
 *  AX25_test.cpp
 *  28/04/2015
 */

#include "AX25.h"
#include <stdio.h>

using namespace qb50;

/**
 * AX25_PacketExampleThread
 *
 * Test AX25 thread
 * @author     Jérôme Skoda    <jerome.skoda@hotmail.fr>
 * @version    1.9             (24/04/2015 - 28/04/2015)
 */
void AX25_PacketExampleThread( Thread *self )
{
    (void)self;

    PacketAX25 PacketTest;

    // define destination
    AX25AddressField destinationField;
    destinationField.CCR = 0x03;
    destinationField.SSID = 0;
    uint8_t destinationAddress[]= "TELEM";
    destinationField.address= destinationAddress;
    PacketTest.destination = destinationField;


    // define source
    AX25AddressField sourceField;
    sourceField.CCR = 0x03;
    sourceField.SSID = 1;
    uint8_t sourceAddress[]= "F6FAO";
    sourceField.address= sourceAddress;
    PacketTest.source = sourceField;


    // define control and PID
    PacketTest.controle= AX25_control_Mode::UI;
    PacketTest.PID= AX25_PID_Mode::NO_LAYER_3;


    // define information/data
    uint8_t src[]="Lorem ipsum dolor sit posuere.";
    size_t src_len = (size_t)30;


    // memory receive packet
    uint8_t *dst = new uint8_t[200];
    for(int i=0; i<200; ++i)
    {
        dst[i]= 0;
    }


    // write packet AX25 in dst
    size_t dst_len = PacketTest.writePacket(dst, src, (size_t)src_len);
    (void)dst_len;

    while(1);
}

/*EoF*/
