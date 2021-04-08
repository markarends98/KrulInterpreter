#include "c_mkdir.h"
#include "stream_util.h"
#include "string_util.h"

namespace operation
{
	void MkDir::init()
	{
		streamUtil::cin(this->prompt("Enter existing path name: "), this->path_);
		streamUtil::cin(this->prompt("Enter new directory name: "), this->directory_);
	}
	
	void MkDir::readStream(asio::ip::tcp::iostream& stream)
	{
		std::string server_response;
		if (streamUtil::getLine(stream, server_response)) {
			// print response
			std::cout << this->response(server_response) << stringUtil::lf;
		}
	}
	
	void MkDir::execute(asio::ip::tcp::iostream& stream)
	{
		// send to server
		stream << this->getCommand() + stringUtil::crlf + this->path_ + stringUtil::crlf + this->directory_ + stringUtil::crlf;
	}
}
