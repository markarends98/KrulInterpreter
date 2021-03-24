#include "s_quit.h"

#include <iostream>

#include "string_util.h"

namespace operation
{
	void Quit::execute(asio::ip::tcp::iostream& stream)
	{
		stream << "Bye." << stringUtil::crlf;
		std::cout << "will disconnect from client: " << stream.socket().local_endpoint() << "." << stringUtil::lf;
		stream.clear();
		stream.close();
	}

}
