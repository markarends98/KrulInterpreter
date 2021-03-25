#include "s_mkdir.h"

#include "file_system.h"
#include "string_util.h"
#include "stream_util.h"

namespace operation
{
	// get path and directory from stream
	void MkDir::readStream(asio::ip::tcp::iostream& stream)
	{
		streamUtil::getLine(stream, this->path_);
		streamUtil::getLine(stream, this->directory_);
		std::cout << stringUtil::wspc << this->path_ << stringUtil::wspc << this->directory_ << stringUtil::lf;
	}

	// create directory in the specified path return message
	void MkDir::execute(asio::ip::tcp::iostream& stream)
	{
		fileSystem::file_system_error error;
		this->server_.createDirectory(this->path_, this->directory_, error);
		stream << fileSystem::ServerFileSystem::errorString(error) << stringUtil::crlf;;
	}
}
