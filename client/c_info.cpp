#include "c_info.h"
#include "stream_util.h"
#include "string_util.h"

namespace operation
{
	void Info::readStream(asio::ip::tcp::iostream& stream)
	{

	}

	void Info::execute(asio::ip::tcp::iostream& stream)
	{
		stream << this->getCommand() << stringUtil::crlf;
	}
}
