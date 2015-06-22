
#ifndef _QB50_SYS_AX25OUT_H
#define _QB50_SYS_AX25OUT_H

#include <FreeRTOS.h>
#include <semphr.h>
#include <queue>
#include <iostream>
#include "device/GPIOPin.h"
#include "Device.h"
#include "device/EXTI.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#undef FIFO
#include "device/FIFO.hpp"


namespace qb50 {

    class AX25Out : public Device
    {
        public:

            AX25Out( FIFO<bool>& fifo );
            ~AX25Out();

            AX25Out& enable  ( void );
            AX25Out& disable ( void );

            void sendFlag();
            void sendPacket( const uint8_t *x, unsigned len );
            /*void fifoBuffer(const std::queue<uint8_t>& val);
            void afficherFifoBuffer(const std::queue<uint8_t>& data);
            */


        private:

            xSemaphoreHandle _sendLock;

/*
            GPIOPin& _clkPin;
            GPIOPin& _txPin;
*/

            //FIFO<bool> _fifo( 1024 );
            FIFO<bool>& _fifo;

    };

    extern qb50::AX25Out ax25;
}


#endif /*_QB50_SYS_AX25OUT_H*/
