
#ifndef _QB50_SYS_AX25OUT_H
#define _QB50_SYS_AX25OUT_H

#include "device/GPIOPin.h"
#include "Device.h"
#include "device/EXTI.h"
#include "device/NRZI.h"

#undef FIFO
#include "device/FIFO.hpp"

#include <queue>
#include <iostream>


namespace qb50 {

    class AX25Out : public Device
    {
        public:

            AX25Out( const char *name, FIFO<bool>& fifo );
            ~AX25Out();

            AX25Out& init    ( void );
            AX25Out& enable  ( bool silent = false );
            AX25Out& disable ( bool silent = false );

            void sendFlag();
            void sendPacket( const uint8_t *x, unsigned len );

        private:

            xSemaphoreHandle _sendLock;

            void _sendByte( uint8_t x, bool stuff );

            FIFO<bool>& _fifo;
            int         _nbit;
            uint16_t    _fcs;

    };

    extern qb50::AX25Out ax25;
}


#endif /*_QB50_SYS_AX25OUT_H*/
