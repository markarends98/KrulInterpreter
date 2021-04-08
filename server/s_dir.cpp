#include "s_dir.h"

#include "file_system.h"
#include "stream_util.h"
#include "string_util.h"

namespace operation
{
	// get directory from string
	void Dir::readStream(asio::ip::tcp::iostream& stream)
	{
		streamUtil::getLine(stream, this->directory_);
		std::cout << stringUtil::wspc << this->directory_ << stringUtil::lf;
	}

	// list directory
	void Dir::execute(asio::ip::tcp::iostream& stream)
	{
		fileSystem::file_system_error error;
		const int entries_count = this->server_.countEntries(this->directory_, error);
		if (error != fileSystem::file_system_error::none)
		{
			stream << fileSystem::ServerFileSystem::errorString(error) << stringUtil::crlf;
			return;
		}

		const fileSystem::directory_iterator entries = this->server_.iterator(this->directory_, error);
		if (error != fileSystem::file_system_error::none)
		{
			stream << fileSystem::ServerFileSystem::errorString(error) << stringUtil::crlf;
			return;
		}

		std::string entries_str_count = std::to_string(entries_count);
		std::string entries_details;

		for (const auto& entry : entries)
		{
			std::string details = entry.detailedString();
			stringUtil::addCrlf(details);
			entries_details.append(details);
		}

		stringUtil::addCrlf(entries_str_count);
		stringUtil::addCrlf(entries_details);
		stream << entries_str_count << entries_details;
	}
} // namespace operation