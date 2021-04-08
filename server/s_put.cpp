#include "s_put.h"
#include "stream_util.h"
#include "base64.h"

namespace operation
{
	void Put::readStream(asio::ip::tcp::iostream& stream)
	{
		streamUtil::getLine(stream, this->target_);

		std::string size_string;
		streamUtil::getLine(stream, size_string);
		this->file_size_ = stringUtil::convert(size_string, 0);

		std::cout << stringUtil::wspc << this->target_ << stringUtil::wspc << size_string << stringUtil::wspc << "(binary data)" << stringUtil::lf;
		
		for (int i = 0; i <= this->file_size_; i++)
		{
			std::string string_data;
			streamUtil::getLine(stream, string_data);
			string_data = base64_decode(string_data);
			const unsigned char binary = string_data.front();
			this->data_.push_back(binary);
		}
		
	}

	void Put::execute(asio::ip::tcp::iostream& stream)
	{
		fileSystem::file_system_error error;
		bool test = this->server_.createFile(this->target_, this->data_, this->file_size_, error);
		stream << fileSystem::ServerFileSystem::errorString(error) << stringUtil::crlf;
	}
}