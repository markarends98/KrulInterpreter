#include "c_put.h"
#include "stream_util.h"
#include "base64.h"

namespace operation
{
	std::pair<std::string, int> Put::getFile(const std::string& target) const
	{
		std::string data;
		int file_size = 0;
		const fileSystem::FileSystemEntry entry = this->client_.queryEntry(target);
		if (entry.exists() && entry.isFile())
		{
			file_size = entry.size();
			std::vector<char> bytes = entry.bytes();
			for (char byte : bytes)
			{
				std::string str_data(1, byte);
				str_data = base64_encode(str_data);
				stringUtil::addCrlf(str_data);
				data.append(str_data);
			}
		}
		return { data , file_size };
	}

	void Put::init()
	{
		do {
			streamUtil::cin(this->prompt("Enter target name: "), this->target_);
			const auto [file_data, file_size] = getFile(this->target_);
			this->data_ = file_data;
			this->file_size_ = file_size;
			
			if(this->data_.empty())
			{
				std::cerr << this->error("File not found.") << stringUtil::lf;
			}
		} while (this->data_.empty());
	}

	void Put::readStream(asio::ip::tcp::iostream& stream)
	{
		std::string server_response;
		if (streamUtil::getLine(stream, server_response)) {
			// print response
			std::cout << this->response(server_response) << stringUtil::lf;
		}
	}

	void Put::execute(asio::ip::tcp::iostream& stream)
	{
		stream << this->getCommand() << stringUtil::crlf << this->target_ << stringUtil::crlf << this->file_size_ << stringUtil::crlf << this->data_;
	}

	bool Put::setFile(const std::string& target)
	{
		const auto [file_data, file_size] = getFile(target);
		this->target_ = target;
		this->data_ = file_data;
		this->file_size_ = file_size;
		return !this->data_.empty();
	}
}
