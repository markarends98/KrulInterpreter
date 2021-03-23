#include "c_ren.h"
#include "stream_util.h"

namespace operation
{
	void Ren::init()
	{
		streamUtil::cin(this->prompt("Enter path name: "), path_);
		streamUtil::cin(this->prompt("Enter new name: "), new_name_);
	}

	void Ren::readStream(asio::ip::tcp::iostream& stream)
	{
		std::string server_response;
		if (streamUtil::getLine(stream, server_response)) {
			// print response
			std::cout << server_response << stringUtil::lf;
		}
	}

	void Ren::execute(asio::ip::tcp::iostream& stream)
	{
		stream << this->getCommand() + stringUtil::crlf + path_ + stringUtil::crlf + new_name_ + stringUtil::crlf;
	}
}
