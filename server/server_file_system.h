#ifndef SERVER_FILE_SYSTEM_H
#define SERVER_FILE_SYSTEM_H

#include "file_system.h"

namespace fileSystem
{
	static const std::string SERVER_ROOT{ std::filesystem::current_path().string() + fileSystem::dirs + "files" };
	
	class ServerFileSystem : public FileSystem
	{
	public:
		explicit ServerFileSystem();
	};
} // namespace fileSystem


#endif // SERVER_FILE_SYSTEM_H