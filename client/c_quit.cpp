#include "c_quit.h"
#include "stream_util.h"

namespace operation
{
	void Quit::readStream(asio::ip::tcp::iostream& stream)
	{
		std::string server_response;
		if (streamUtil::getLine(stream, server_response)) {
			// print response
			std::cout << this->response(server_response) << stringUtil::lf;
			stream.clear();
			stream.close();
		}
	}

	void Quit::execute(asio::ip::tcp::iostream& stream)
	{
		stream << this->getCommand() << stringUtil::crlf;
	}
}
