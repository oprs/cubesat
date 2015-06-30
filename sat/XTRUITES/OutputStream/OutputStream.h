/**
 *  @file       outputStream.h
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       23/06/2015
 */

#ifndef _QB50_XTRUITES_OUTPUT_STREAM_H_
#define _QB50_XTRUITES_OUTPUT_STREAM_H_


#include "unistd.h"
#include <string>
#include <map>

namespace qb50
{

    namespace XTRUITES
    {

        class OutputStreamChannel;

        typedef std::map <std::string, OutputStreamChannel*> output_stream_channel_map_t;
        typedef std::pair<std::string, OutputStreamChannel*> output_stream_channel_pair_t;

        class OutputStream
        {
            public:
                OutputStream();
                OutputStreamChannel* getChannelByName(std::string nameChannel);
                OutputStream& add(output_stream_channel_pair_t item);

                OutputStream& on     ( void );
                OutputStream& off    ( void );
                OutputStream& toggle ( void );

            private:
                output_stream_channel_map_t _channels;
        };



    }; /* namespace: XTRUITES */

}; /* namespace: qb50 */

#endif /* _QB50_XTRUITES_OUTPUT_STREAM_H_ */

/*EoF*/
