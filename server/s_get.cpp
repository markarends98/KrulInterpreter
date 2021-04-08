#include "s_get.h"
#include "stream_util.h"
#include "base64.h"

namespace operation
{
	void Get::readStream(asio::ip::tcp::iostream& stream)
	{
		streamUtil::getLine(stream, this->target_);
		std::cout << stringUtil::wspc << this->target_ << stringUtil::lf;
		
		fileSystem::file_system_error error;
		const fileSystem::FileSystemEntry entry = this->server_.queryEntry(this->target_, error);
		if (entry.exists() && entry.isFile())
		{
			this->file_size_ = entry.size();
			std::vector<char> bytes = entry.bytes();
			for (char byte : bytes)
			{
				std::string str_data(1, byte);
				str_data = base64_encode(str_data);
				stringUtil::addCrlf(str_data);
				this->data_.append(str_data);
			}
		}else
		{
			this->file_size_ = -1;
			this->target_ = "";
			this->data_ = fileSystem::ServerFileSystem::errorString(error) + stringUtil::crlf;
		}
	}
	
	void Get::execute(asio::ip::tcp::iostream& stream)
	{
		stream << this->file_size_ << stringUtil::crlf << this->target_  << stringUtil::crlf << this->data_;
	}
}
