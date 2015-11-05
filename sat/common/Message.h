#ifndef _QB50_COMMUN_MESSAGE_H
#define _QB50_COMMUN_MESSAGE_H


namespace qb50{

    enum Commands_ODB{
        PING = 'P',
        MODE_ATT_DET = 'D',
        MODE_ATT_CON = 'C', //A Confirmer
        ASK_ATT = 'Q',
        ASK_MAG_RAW = 'M',
        ASK_GYR_RAW = 'G',
        ASK_SUN_RAW = 'J',
        ASK_SUN_TRUE = 'F',
        SET_TIME = 'K',
        READ_TIME = 'H',
        STOP = 'S'

        //to Add and confirm with Gerard

        /* ASK_MAG_TRUE  True Magnetic field
           ASK_GYR_TRUE  True Gyrometer Readings */
    };

}
#endif
