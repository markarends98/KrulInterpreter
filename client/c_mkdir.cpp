#include "c_mkdir.h"
#include "stream_util.h"
#include "string_util.h"

namespace operation
{
	void MkDir::init()
	{
		streamUtil::cin(this->prompt("Enter existing path name: "), path_);
		streamUtil::cin(this->prompt("Enter new directory name: "), directory_);
	}
	
	void MkDir::readStream(asio::ip::tcp::iostream& stream)
	{
		std::string server_response;
		if (streamUtil::getLine(stream, server_response)) {
			// print response
			std::cout << server_response << stringUtil::lf;
		}
	}
	
	void MkDir::execute(asio::ip::tcp::iostream& stream)
	{
		// send to server
		stream << this->getCommand() + stringUtil::crlf + path_ + stringUtil::crlf + directory_ + stringUtil::crlf;
	}
}
