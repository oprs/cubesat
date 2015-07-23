/**
 *  @file       channel.cpp
 *  @brief
 *  @author     Jérôme Skoda <jerome.skoda@hotmail.fr>
 *  @version    1.2
 *  @date       23/06/2015
 */

 #include "OutputStreamChannel.h"


using namespace std;
using namespace qb50::XTRUITES;

OutputStreamChannel::OutputStreamChannel( void )
{
}

OutputStreamChannel& OutputStreamChannel::on( void )
{
    enable= true;
	return *this;
}


OutputStreamChannel& OutputStreamChannel::off( void )
{
    enable= false;
	return *this;
}


OutputStreamChannel& OutputStreamChannel::toggle( void )
{
    enable= !enable;
	return *this;
}


OutputStreamChannel& OutputStreamChannel::setName(std::string nameVal)
{
    _name= nameVal;
    return *this;
}

std::string OutputStreamChannel::getName( void )
{
    return _name;
}


OutputStreamChannel& OutputStreamChannel::setOutputStream(OutputStream* outputStreamVal)
{
    _outputStream= outputStreamVal;
    return *this;
}

OutputStream* OutputStreamChannel::getOutputStream( void )
{
    return _outputStream;
}


size_t OutputStreamChannel::write(const void *x, size_t len)
{
    if(!enable)
    {
        return 0;
    }
    return ch_write(x, len);
}

size_t OutputStreamChannel::ch_write(const void *x, size_t len)
{
  (void) x;
  (void) len;

  return 0;
}
