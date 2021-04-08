#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include "dllexport.h"
#include <string>
#include <filesystem>

#include "file_system_entry.h"

namespace fileSystem
{
	using directory_iterator = std::vector<FileSystemEntry>;
	
	static const char* dirs{ "\\" };
	
	CPP_LIBRARY_API enum class file_system_error
	{
		none = 0,
		not_found,
		no_permission,
		duplicate,
		could_not_create,
		failed,
		test
	};
	
	CPP_LIBRARY_API class FileSystem
	{
	public:
		explicit FileSystem(const std::string& root);
	private:
		const std::string& root_;
	public:
		std::string fullPath(const std::string& path) const;
		bool hasPermission(const std::string& path, unsigned long permissions) const;
		static bool hasPermission(const std::string& path, unsigned long permissions, file_system_error& error);
		bool exists(const std::string& path) const;
		bool exists(const std::string& path, file_system_error& error) const;
		bool rename(const std::string& path, const std::string& newName) const;
		bool rename(const std::string& path, const std::string& newName, file_system_error& error) const;
		bool createDirectory(const std::string& path, const std::string& directoryName) const;
		bool createDirectory(const std::string& path, const std::string& directoryName, file_system_error& error) const;
		bool createFile(const std::string& filePath, const std::vector<char>& bytes) const;
		bool createFile(const std::string& filePath, const std::vector<char>& bytes, int byteCount) const;
		bool createFile(const std::string& filePath, const std::vector<char>& bytes, int byteCount, file_system_error& error) const;
		bool removeEntry(const std::string& entryPath) const;
		bool removeEntry(const std::string& entryPath, file_system_error& error) const;
		int countEntries(const std::string& directory) const;
		int countEntries(const std::string& directory, file_system_error& error) const;
		directory_iterator iterator(const std::string& directory) const;
		directory_iterator iterator(const std::string& directory, file_system_error& error) const;
		FileSystemEntry queryEntry(const std::string& path) const;
		FileSystemEntry queryEntry(const std::string& path, const entry_type& type) const;
		FileSystemEntry queryEntry(const std::string& path, file_system_error& error) const;
		FileSystemEntry queryEntry(const std::string& path, const entry_type& type, file_system_error& error) const;
		static std::string errorString(file_system_error error);
	};
} // namespace fileSystem


#endif // FILE_SYSTEM_H
