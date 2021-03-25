#include "c_info.h"
#include "stream_util.h"

namespace operation
{
	void Info::readStream(asio::ip::tcp::iostream& stream)
	{
		std::string server_response;
		if (streamUtil::getLine(stream, server_response)) {
			// print response
			std::cout << server_response << stringUtil::lf;
		}
	}

	void Info::execute(asio::ip::tcp::iostream& stream)
	{
		stream << this->getCommand() << stringUtil::crlf;
	}
}
