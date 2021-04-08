#include "c_ren.h"
#include "stream_util.h"

namespace operation
{
	void Ren::init()
	{
		streamUtil::cin(this->prompt("Enter path name: "), this->path_);
		streamUtil::cin(this->prompt("Enter new name: "), this->new_name_);
	}

	void Ren::readStream(asio::ip::tcp::iostream& stream)
	{
		std::string server_response;
		if (streamUtil::getLine(stream, server_response)) {
			// print response
			std::cout << this->response(server_response) << stringUtil::lf;
		}
	}

	void Ren::execute(asio::ip::tcp::iostream& stream)
	{
		stream << this->getCommand() + stringUtil::crlf + this->path_ + stringUtil::crlf + this->new_name_ + stringUtil::crlf;
	}
}
