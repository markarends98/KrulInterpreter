#ifndef CLIENT_FILE_SYSTEM_H
#define CLIENT_FILE_SYSTEM_H

#include "file_system.h"

namespace fileSystem
{
	static const std::string CLIENT_ROOT{ std::filesystem::current_path().string() + fileSystem::dirs + "files" };
	
	class ClientFileSystem : public FileSystem
	{
	public:
		explicit ClientFileSystem();
	};
} // namespace fileSystem


#endif // CLIENT_FILE_SYSTEM_H