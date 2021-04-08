#include "c_dir.h"
#include "stream_util.h"

namespace operation
{
	void Dir::init()
	{
		streamUtil::cin(this->prompt("Enter path name: "), this->path_);
	}
	
	void Dir::readStream(asio::ip::tcp::iostream& stream)
	{
		std::string response;
		streamUtil::getLine(stream, response);

		const auto [valid, amount] = stringUtil::extractInteger(response);
		if (valid)
		{
			std::cout << "Entries found: " << amount << stringUtil::lf;
			
			for (int i = 0; i < amount; i++)
			{
				std::string entry;
				streamUtil::getLine(stream, entry);
				std::cout << entry << stringUtil::lf;
			}
		}else
		{
			std::cout << this->response(response) << stringUtil::lf;
		}
	}
	
	void Dir::execute(asio::ip::tcp::iostream& stream)
	{
		// send to server
		stream << this->getCommand() + stringUtil::crlf + this->path_ + stringUtil::crlf;
	}
}
