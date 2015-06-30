/**
 *  @file       config.h
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       23/06/2015
 */

#ifndef _QB50_XTRUITES_OUTPUT_STREAM_CONFIG_H_
#define _QB50_XTRUITES_OUTPUT_STREAM_CONFIG_H_


#include "OutputStream/OutputStreamChannel.h"
#include <sys/types.h>

namespace qb50
{

    namespace XTRUITES
    {

        class UART3_syscalls : public OutputStreamChannel
        {
            private:
                ssize_t ch_write(const void *x, size_t len);
        };

        class UART3_XTRUITES : public OutputStreamChannel
        {
            private:
                ssize_t ch_write(const void *x, size_t len);
        };

    }; /* namespace: XTRUITES */

}; /* namespace: qb50 */

#endif /* _QB50_XTRUITES_OUTPUT_STREAM_CONFIG_H_ */

/*EoF*/
