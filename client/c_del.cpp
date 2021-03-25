#include "c_del.h"

#include "stream_util.h"

namespace operation
{
	void Del::init()
	{
		streamUtil::cin(this->prompt("Enter target name: "), this->target_);
	}

	void Del::readStream(asio::ip::tcp::iostream& stream)
	{
		std::string server_response;
		if (streamUtil::getLine(stream, server_response)) {
			// print response
			std::cout << server_response << stringUtil::lf;
		}
	}

	void Del::execute(asio::ip::tcp::iostream& stream)
	{
		stream << this->getCommand() + stringUtil::crlf + this->target_ + stringUtil::crlf;
	}
} // namespace operation
