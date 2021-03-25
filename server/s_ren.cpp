#include "s_ren.h"
#include "stream_util.h"

namespace operation
{
	// get path and directory from string
	void Ren::readStream(asio::ip::tcp::iostream& stream)
	{
		streamUtil::getLine(stream, this->path_);
		streamUtil::getLine(stream, this->new_name_);
		std::cout << stringUtil::wspc << this->path_ << stringUtil::wspc << this->new_name_ << stringUtil::lf;
	}

	// create directory in the specified path
	void Ren::execute(asio::ip::tcp::iostream& stream)
	{
		fileSystem::file_system_error error;
		this->server_.rename(this->path_, this->new_name_, error);
		stream << fileSystem::ServerFileSystem::errorString(error) << stringUtil::crlf;
	}
}
