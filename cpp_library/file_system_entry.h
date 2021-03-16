#ifndef FILE_SYSTEM_ENTRY_H
#define FILE_SYSTEM_ENTRY_H
#include <filesystem>
#include <string>
#include <vector>

#include "dllexport.h"

namespace fileSystem
{
	CPP_LIBRARY_API enum class entry_type : char
	{
		directory = 'D',
		file = 'F',
		miscellaneous = '*',
		unspecified = ' '
	};
	
	CPP_LIBRARY_API class FileSystemEntry
	{
	public:
		explicit FileSystemEntry();
		explicit FileSystemEntry(const std::filesystem::directory_entry& directoryEntry);
	private:
		bool exists_{};
		std::string name_{};
		std::string path_{};
		std::string extension_{};
		std::string parent_{};
		time_t date_modified_{};
		std::string date_modified_string_{};
		std::vector<unsigned char> bytes_{};
		uintmax_t size_{};
		entry_type type_{};
	public:
		static FileSystemEntry findEntry(const std::string& path);
		_NODISCARD bool exists() const;
		_NODISCARD std::string name() const;
		_NODISCARD std::string path() const;
		_NODISCARD std::string extension() const;
		_NODISCARD std::string parent() const;
		_NODISCARD time_t dateModified() const;
		_NODISCARD std::string dateModifiedString() const;
		_NODISCARD std::vector<unsigned char> bytes() const;
		_NODISCARD uintmax_t size() const;
		_NODISCARD entry_type type() const;
		_NODISCARD std::string detailedString() const;
		_NODISCARD bool isDirectory() const;
		_NODISCARD bool isFile() const;
		_NODISCARD bool isMiscellaneous() const;
	};
} // namespace fileSystem
#endif // FILE_SYSTEM_ENTRY_H
