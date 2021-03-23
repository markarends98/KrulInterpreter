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
			const int entries_count = server_.countEntries(this->directory_, error);
			if (error != fileSystem::file_system_error::none)
			{
				stream << fileSystem::ServerFileSystem::errorString(error);
				return;
			}

			const fileSystem::directory_iterator entries = server_.iterator(this->directory_, error);
			if (error != fileSystem::file_system_error::none)
			{
				stream << fileSystem::ServerFileSystem::errorString(error);
				return;
			}

			std::string entries_str_count = std::to_string(entries_count);
			std::string entries_header = "Entries found: " + entries_str_count;
			std::string entries_details;

			for (const auto& entry : entries)
			{
				fileSystem::FileSystemEntry server_entry = server_.queryEntry(entry.path().string());
				std::string details = server_entry.detailedString();
				stringUtil::addCrlf(details);
				entries_details.append(details);
			}

			stringUtil::addCrlf(entries_str_count);
			stringUtil::addCrlf(entries_header);
			stringUtil::addCrlf(entries_details);
			stream << entries_str_count << entries_header << entries_details;
		}
} // namespace operation