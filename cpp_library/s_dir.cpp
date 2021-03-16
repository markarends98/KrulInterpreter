#include "s_dir.h"

namespace operation
{
	namespace server
	{
		void dir::readStream(asio::ip::tcp::iostream& stream)
		{
			getline(stream, this->directory_);
		}

		std::string dir::execute()
		{
			fileSystem::server_file_system server;
			return std::string(this->getCommand());
		}
	} // namespace server
} // namespace operation