/**
 *  @file       outputStream.cpp
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       23/06/2015
 */
#include "OutputStreamChannel.h"
#include "Config.h"
#include "OutputStream.h"

using namespace std;
using namespace qb50::XTRUITES;

OutputStream::OutputStream()
{
    //  Ajoutez ici les cannaux ici
    //                                  Nom                 Instance de canal
    add(output_stream_channel_pair_t(   "UART3_syscalls",   new UART3_syscalls()    ));
    add(output_stream_channel_pair_t(   "UART3_XTRUITES",   new UART3_XTRUITES()    ));
}

OutputStream& OutputStream::add(output_stream_channel_pair_t item)
{
    _channels.insert(item);
    item.second->
         setName(item.first)
        .setOutputStream(this);
    return *this;
}

OutputStreamChannel& OutputStream::getChannelByName(std::string nameChannel)
{
	return *_channels[nameChannel];
}


OutputStream& OutputStream::on( void )
{
    for (output_stream_channel_map_t::iterator it= _channels.begin(); it != _channels.end(); ++it)
    {
        it->second->on();
    }
	return *this;
}


OutputStream& OutputStream::off( void )
{
    for (output_stream_channel_map_t::iterator it= _channels.begin(); it != _channels.end(); ++it)
    {
        it->second->off();
    }
	return *this;
}


OutputStream& OutputStream::toggle( void )
{
    for (output_stream_channel_map_t::iterator it= _channels.begin(); it != _channels.end(); ++it)
    {
        it->second->toggle();
    }
	return *this;
}
/*EoF*/
