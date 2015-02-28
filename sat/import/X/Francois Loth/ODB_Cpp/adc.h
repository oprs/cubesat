#include <stm32f4xx_spi.h>

/*
enum channel
        {
            canal0 = 128 + 0 + 15,    // ADCS
            canal1 = 128 + 64 + 15,   //I_EXP
            canal2 = 128 + 16 + 15,   //I_RX
            canal3 = 128 + 80 + 15,   //RSSI
            canal4 = 128 + 32 + 15,   //I_TX
            canal5 = 128 + 96 + 15,   //P_TX
            canal6 = 128 + 48 + 15,   //P_PA
            canal7 = 128 + 112 + 15   //T_PA
        };
*/


//uint8_t value(int canal);

uint8_t READ(int CS,int canal);
