/**
 *  @file       channel.h
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       23/06/2015
 */


#ifndef _QB50_XTRUITES_OUTPUT_STREAM_CHANNEL_H_
#define _QB50_XTRUITES_OUTPUT_STREAM_CHANNEL_H_

#include <string>
#include <map>

namespace qb50
{

    namespace XTRUITES
    {

        class OutputStream;

        class OutputStreamChannel
        {

            public:
                bool enable= true;
                OutputStreamChannel( void );
                OutputStreamChannel& setName(std::string nameVal);
                std::string getName( void );
                OutputStreamChannel& setOutputStream(OutputStream* outputStreamVal);
                OutputStream* getOutputStream( void );
                OutputStreamChannel& on     ( void );
                OutputStreamChannel& off    ( void );
                OutputStreamChannel& toggle ( void );
                size_t write(const void *x, size_t len);

            private:
                virtual size_t ch_write(const void* /* x */, size_t /* len */);
                std::string _name= "";
                OutputStream* _outputStream;

        };

    } /* namespace: XTRUITES */

} /* namespace: qb50 */

#endif /* _QB50_XTRUITES_OUTPUT_STREAM_CHANNEL_H_ */

/*EoF*/
