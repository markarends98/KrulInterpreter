#include "c_dir.h"
#include "stream_util.h"

namespace operation
{
	void Dir::init()
	{
		streamUtil::cin(this->prompt("Enter path name: "), path_);
	}
	
	void Dir::readStream(asio::ip::tcp::iostream& stream)
	{
		std::string response;
		streamUtil::getLine(stream, response);

		const auto [valid, amount] = stringUtil::extractInteger(response);
		if (valid)
		{
			std::string header;
			streamUtil::getLine(stream, header);
			std::cout << header << stringUtil::lf;
			
			for (int i = 0; i < amount; i++)
			{
				std::string entry;
				streamUtil::getLine(stream, entry);
				std::cout << entry << stringUtil::lf;
				file_data_.push_back(entry);
			}
		}else
		{
			std::cout << response << stringUtil::lf;
		}
	}
	
	void Dir::execute(asio::ip::tcp::iostream& stream)
	{
		// send to server
		stream << this->getCommand() + stringUtil::crlf + path_ + stringUtil::crlf;
	}
}
