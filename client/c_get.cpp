#include "c_get.h"

#include "stream_util.h"
#include "base64.h"

namespace operation
{
	void Get::init()
	{
		streamUtil::cin(this->prompt("Enter path name: "), this->file_);
	}

	void Get::readStream(asio::ip::tcp::iostream& stream)
	{

		std::string size_string;
		streamUtil::getLine(stream, size_string);
		const int file_size = stringUtil::convert(size_string, 0);
		std::string target;
		streamUtil::getLine(stream, target);

		if (file_size >= 0) {

			std::vector<char> data;
			for (int i = 0; i <= file_size; i++)
			{
				std::string string_data;
				streamUtil::getLine(stream, string_data);
				string_data = base64_decode(string_data);
				const unsigned char binary = string_data.front();
				data.push_back(binary);
			}

			fileSystem::file_system_error error;
			this->client_.createFile(target, data, file_size, error);
			std::cout << this->response(fileSystem::ClientFileSystem::errorString(error)) << stringUtil::lf;
		}else
		{
			std::string string_error;
			streamUtil::getLine(stream, string_error);
			std::cout << this->response(string_error) << stringUtil::lf;
		}
	}

	void Get::execute(asio::ip::tcp::iostream& stream)
	{
		// send to server
		stream << this->getCommand() + stringUtil::crlf + this->file_ + stringUtil::crlf;
	}
}
