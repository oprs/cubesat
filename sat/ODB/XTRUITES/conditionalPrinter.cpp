/**
 *  @file       conditionalPrinter.cpp
 *  @brief      Ecriture conditionnelle (Source)
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       20/05/2015
 */

#include "conditionalPrinter.h"


// Disable macro definitions conditional printf and hexdump
#undef  printf
#undef  hexdump


namespace qb50
{


    int cpprintf(const char *format, ...)
    {
        if (XTRUITES::enable)
        {
            return 0;
        }
        va_list vl;
        va_start(vl, format);
        int n= vprintf(format, vl);
        va_end(vl);
        return n;
    }


    /*
     *  max: 78 chars per line (76 formatted + 1 CR + 1 LF)
     *
     *            1         2         3         4         5         6         7
     *  012345678901234567890123456789012345678901234567890123456789012345678901234567
     *
     *  00000000  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  ................␍␊
     *  00000010  00 00 00 00 00 00 00 00  00 00 00 00              ............␍␊
     *            ^-------------------- >>hoff --------------------^^-- >>aoff --^
     *                               (HEX offset)                   (ASCII offset)
     */
    static const char hex[  16 + 1 ] = "0123456789abcdef";
    static const char asc[ 256 + 1 ] = "................................"  \
                                       " !\"#$%&'()*+,-./0123456789:;<=>?" \
                                       "@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_" \
                                       "`abcdefghijklmnopqrstuvwxyz{|}~."  \
                                       "................................"  \
                                       "................................"  \
                                       "................................"  \
                                       "................................";



    void cphexdump( const void *addr, unsigned len )
    {
        if (XTRUITES::enable)
        {
            return;
        }

        /* allocate enough space to hold a full line of data;
           go easy on the stack and use dynamic allocation */

        char *buf = new char[ 78 ];

        const uint8_t *x = (const uint8_t*)addr;
        uint8_t b;

        for( unsigned i = 0 ; i < len ; ) {

            /* format the 32-bit address */

            buf[ 0 ] = hex[ ( (uint32_t)x >> 28 ) & 0x0f ];
            buf[ 1 ] = hex[ ( (uint32_t)x >> 24 ) & 0x0f ];
            buf[ 2 ] = hex[ ( (uint32_t)x >> 20 ) & 0x0f ];
            buf[ 3 ] = hex[ ( (uint32_t)x >> 16 ) & 0x0f ];
            buf[ 4 ] = hex[ ( (uint32_t)x >> 12 ) & 0x0f ];
            buf[ 5 ] = hex[ ( (uint32_t)x >>  8 ) & 0x0f ];
            buf[ 6 ] = hex[ ( (uint32_t)x >>  4 ) & 0x0f ];
            buf[ 7 ] = hex[   (uint32_t)x         & 0x0f ];

            /* couple of spaces */

            buf[ 8 ] = ' ';
            buf[ 9 ] = ' ';

            /* format the data (both HEX and ASCII views) */

            int hoff = 10;  /* offset moving over the HEX part */
            int aoff = 60;  /* offset moving over the ASCII part */

            while( i < len ) {
                b = *(x++);  /* load b and move on to the next byte */

                /* format b as HEX (2 nibbles + 1 space) */

                buf[ hoff++ ] = hex[ ( b >> 4 ) & 0x0f ];
                buf[ hoff++ ] = hex[   b        & 0x0f ];
                buf[ hoff++ ] = ' ';

                /* format b as ASCII (1 char) */

                buf[ aoff++ ] = asc[ b ];

                ++i;

                if(( i % 8 ) == 0 ) {
                /* add an extra space every 8 bytes of data for better readability */
                    buf[ hoff++ ] = ' ';
                /* exit the inner loop after 16 bytes of data (= one line) */
                    if(( i % 16 ) == 0 ) break;
                }
            }

            /* complement with spaces */

            while( hoff < 60 )
                buf[ hoff++ ] = ' ';

            /* add CR+LF and send everything over to TX_DEBUG */

            buf[ aoff++ ] = '\r';
            buf[ aoff++ ] = '\n';

            (void)write( 1, buf, aoff );

            /* start over with the next line (or exit when done) */
        }

        delete[] buf;
    }


// Enable macro definitions conditional printf and hexdump
#define  printf     cpprintf
#define  hexdump    cphexdump


} /* qb50 */

/*EoF*/
