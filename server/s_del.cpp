#include "s_del.h"
#include "stream_util.h"

namespace operation
{
	void Del::readStream(asio::ip::tcp::iostream& stream)
	{
		streamUtil::getLine(stream, this->target_);
		std::cout << stringUtil::wspc << this->target_ << stringUtil::lf;
	}

	void Del::execute(asio::ip::tcp::iostream& stream)
	{
		fileSystem::file_system_error error;
		this->server_.removeEntry(this->target_, error);
		stream << fileSystem::ServerFileSystem::errorString(error) << stringUtil::crlf;
	}
}
