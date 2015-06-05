#ifndef AX25OUT_H_INCLUDED
#define AX25OUT_H_INCLUDED

#include <FreeRTOS.h>
#include <semphr.h>
#include <queue>
#include <iostream>
#include "device/GPIOPin.h"
#include "device/FIFO.h"
#include "Device.h"
#include "device/EXTI.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


namespace qb50 {


    class AX25Out : public Device
    {
        public:

            AX25Out( GPIOPin& clkPin, GPIOPin& txPin );
            ~AX25Out();

            AX25Out& enable  ( void );
            AX25Out& disable ( void );

            void sendFlag();
            void sendPacket( uint8_t *x, unsigned len );
            /*void fifoBuffer(const std::queue<uint8_t>& val);
            void afficherFifoBuffer(const std::queue<uint8_t>& data);
            */


        private:

			xSemaphoreHandle _sendLock;

			GPIOPin& _clkPin;
			GPIOPin& _txPin;

			FIFO _fifo;

    };

    extern qb50::AX25Out ax25;
}



#endif /* AX25OUT_H_INCLUDED */
