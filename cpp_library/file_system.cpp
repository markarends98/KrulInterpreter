#include "pch.h"
#include "file_system.h"
#include "date_util.h"
#include "string_util.h"

#include <fstream>
#include <asio/buffer.hpp>

namespace fileSystem
{
	FileSystem::FileSystem(const std::string& root) : root_(root)
	{
		// create the root folder if not exists
		if (!this->exists(root_))
		{
			std::filesystem::create_directory(root_);
		}
	}

	// check certain permissions on a directory
	bool FileSystem::hasPermission(const std::string& path, const unsigned long permissions) const
	{
		file_system_error e;
		return FileSystem::hasPermission(path, permissions, e);
	}

	// check certain permissions on a directory
	bool FileSystem::hasPermission(const std::string& path, unsigned long permissions, file_system_error& error)
	{
		bool b_ret = false;
		const std::wstring converted_path = std::wstring(path.begin(), path.end());
		DWORD length = 0;
		if (!::GetFileSecurity(converted_path.c_str(), OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION
			| DACL_SECURITY_INFORMATION, nullptr, NULL, &length) &&
			ERROR_INSUFFICIENT_BUFFER == ::GetLastError())
		{
			auto* const security = static_cast<PSECURITY_DESCRIPTOR>(::malloc(length));
			if (security && ::GetFileSecurity(converted_path.c_str(),
				OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION
				| DACL_SECURITY_INFORMATION, security, length, &length))
			{
				HANDLE h_token = nullptr;
				if (::OpenProcessToken(::GetCurrentProcess(), TOKEN_IMPERSONATE | TOKEN_QUERY |
					TOKEN_DUPLICATE | STANDARD_RIGHTS_READ, &h_token))
				{
					HANDLE h_impersonated_token = nullptr;
					if (::DuplicateToken(h_token, SecurityImpersonation, &h_impersonated_token))
					{
						PRIVILEGE_SET privileges = { 0 };
						DWORD granted_access = 0, privileges_length = sizeof(privileges);
						BOOL result = FALSE;

						GENERIC_MAPPING mapping;
						mapping.GenericRead = FILE_GENERIC_READ;
						mapping.GenericWrite = FILE_GENERIC_WRITE;
						mapping.GenericExecute = FILE_GENERIC_EXECUTE;
						mapping.GenericAll = FILE_ALL_ACCESS;

						::MapGenericMask(&permissions, &mapping);
						if (::AccessCheck(security, h_impersonated_token, permissions,
							&mapping, &privileges, &privileges_length, &granted_access, &result))
						{
							b_ret = (result == TRUE);
						}
						::CloseHandle(h_impersonated_token);
					}
					::CloseHandle(h_token);
				}
				::free(security);
			}
		}
		error = file_system_error::none;
		if (!b_ret)
		{
			error = file_system_error::no_permission;
		}
		return b_ret;
	}

	// get the full path of a directory
	std::string FileSystem::fullPath(const std::string& path) const
	{
		if (path == "\\" || path == "//" || path == "/" || path.empty())
		{
			return this->root_;
		}
		if (path.find(this->root_) != std::string::npos)
		{
			return path;
		}

		//std::string new_path = path;
		//stringUtil::eraseBegin(new_path, "\\");
		//stringUtil::eraseBegin(new_path, "//");
		//stringUtil::eraseBegin(new_path, "/");
		//stringUtil::eraseBegin(new_path, "\\\\");
		return this->root_ + fileSystem::dirs + path;
	}

	// check if path exists
	bool FileSystem::exists(const std::string& path) const
	{
		file_system_error e;
		return this->exists(path, e);
	}

	// check if path exists
	bool FileSystem::exists(const std::string& path, file_system_error& error) const
	{
		if (std::filesystem::exists(this->fullPath(path)))
		{
			error = file_system_error::duplicate;
			return true;
		}
		error = file_system_error::not_found;
		return false;
	}

	// rename entry
	bool FileSystem::rename(const std::string& path, const std::string& newName) const
	{
		file_system_error e;
		return this->rename(path, newName, e);
	}

	// rename entry
	bool FileSystem::rename(const std::string& path, const std::string& newName, file_system_error& error) const
	{
		// check if path exists
		const std::string full_path = this->fullPath(path);
		if (!this->exists(full_path))
		{
			return false;
		}

		// check permissions
		if (!this->hasPermission(full_path, GENERIC_READ | GENERIC_WRITE, error))
		{
			return false;
		}

		const FileSystemEntry entry = this->queryEntry(full_path, error);
		if (error != file_system_error::none)
		{
			return false;
		}

		try
		{
			std::string new_path;
			if (entry.isDirectory())
			{
				// append name to parent dir to get new dir name
				new_path = entry.parent() + fileSystem::dirs + newName;
			}
			else
			{
				const bool has_extension = newName.find_last_of('.') != std::string::npos;
				new_path = entry.parent() + fileSystem::dirs + newName;

				if (!has_extension)
				{
					// append current extension if missing
					new_path.append(entry.extension());
				}
			}
			std::filesystem::rename(entry.path(), new_path);
			error = file_system_error::none;
			return true;
		}
		catch (...)
		{
			error = file_system_error::failed;
			return false;
		}
	}

	// create a directory
	bool FileSystem::createDirectory(const std::string& path, const std::string& directoryName) const
	{
		file_system_error e;
		return this->createDirectory(path, directoryName, e);
	}

	// create a directory
	bool FileSystem::createDirectory(const std::string& path, const std::string& directoryName, file_system_error& error) const
	{
		// check if parent path exists
		const std::string full_path = this->fullPath(path);

		if (!this->exists(full_path, error))
		{
			return false;
		}

		// check if duplicate
		const std::string new_dir = full_path + fileSystem::dirs + directoryName;
		if (this->exists(new_dir))
		{
			error = file_system_error::duplicate;
			return false;
		}

		// check permissions
		if (!hasPermission(full_path, GENERIC_WRITE | GENERIC_READ, error))
		{
			return false;
		}

		try
		{
			std::filesystem::create_directory(new_dir);
			error = file_system_error::none;
			return true;
		}
		catch (...)
		{
			error = file_system_error::could_not_create;
			return false;
		}
	}

	// create a file
	bool FileSystem::createFile(const std::string& filePath, const std::vector<char>& bytes) const
	{
		file_system_error e;
		return this->createFile(filePath, bytes, size(bytes), e);
	}

	// create a file
	bool FileSystem::createFile(const std::string& filePath, const std::vector<char>& bytes, const int byteCount) const
	{
		file_system_error e;
		return this->createFile(filePath, bytes, byteCount, e);
	}

	// create a file
	bool FileSystem::createFile(const std::string& filePath, const std::vector<char>& bytes, const int byteCount, file_system_error& error) const
	{
		std::string path;
		const std::string full_path = this->fullPath(filePath);
		stringUtil::findBeforeLast(full_path, '\\', path);
		if (!this->exists(path, error))
		{
			return false;
		}
		std::ofstream file_stream(full_path, std::ios::trunc | std::ios::out | std::ios::binary);
		bool ret;
		if (file_stream.good())
		{
			file_stream.write(bytes.data(), byteCount);
			error = file_system_error::none;
			ret = true;
		}
		else
		{
			error = file_system_error::could_not_create;
			ret = false;
		}

		if (file_stream.is_open())
		{
			file_stream.close();
		}
		return ret;
	}

	// remove entry
	bool FileSystem::removeEntry(const std::string& entryPath) const
	{
		file_system_error e;
		return this->removeEntry(entryPath, e);
	}

	// remove entry
	bool FileSystem::removeEntry(const std::string& entryPath, file_system_error& error) const
	{
		// check if path exists
		const std::string full_path = this->fullPath(entryPath);
		if (!this->exists(full_path, error))
		{
			return false;
		}

		// check permissions
		if (!this->hasPermission(full_path, (GENERIC_READ | GENERIC_WRITE), error))
		{
			return false;
		}

		try
		{
			std::filesystem::remove_all(full_path);
			error = file_system_error::none;
			return true;
		}
		catch (...) {
			error = file_system_error::failed;
			return false;
		}
	}

	// count the amount of entries in a directory
	int FileSystem::countEntries(const std::string& directory) const
	{
		file_system_error e;
		return this->countEntries(directory, e);
	}

	// count the amount of entries in a directory
	int FileSystem::countEntries(const std::string& directory, file_system_error& error) const
	{
		error = file_system_error::none;
		const directory_iterator it = this->iterator(directory, error);
		return it.size();
	}

	// get iterator for directory
	directory_iterator FileSystem::iterator(const std::string& directory) const
	{
		file_system_error e;
		return this->iterator(directory, e);
	}

	// get iterator for directory
	directory_iterator FileSystem::iterator(const std::string& directory, file_system_error& error) const
	{
		const std::string full_path = this->fullPath(directory);
		if (!std::filesystem::is_directory(full_path))
		{
			error = file_system_error::not_found;
			return directory_iterator{};
		}
		std::vector<FileSystemEntry> entries;
		for(auto t : std::filesystem::directory_iterator(full_path))
		{
			entries.push_back(this->queryEntry(t.path().string()));
		}

		error = file_system_error::none;
		return entries;
	}

	// query details of an entry
	FileSystemEntry FileSystem::queryEntry(const std::string& path) const
	{
		file_system_error e;
		return this->queryEntry(path, entry_type::unspecified, e);
	}

	// query details of an entry
	FileSystemEntry FileSystem::queryEntry(const std::string& path, const entry_type& type) const
	{
		file_system_error e;
		return this->queryEntry(path, type, e);
	}

	// query details of an entry
	FileSystemEntry FileSystem::queryEntry(const std::string& path, file_system_error& error) const
	{
		return this->queryEntry(path, entry_type::unspecified, error);
	}

	// query details of an entry
	FileSystemEntry FileSystem::queryEntry(const std::string& path, const entry_type& type, file_system_error& error) const
	{
		const std::string full_path = this->fullPath(path);
		FileSystemEntry entry = FileSystemEntry::findEntry(full_path);

		if (entry.exists())
		{
			if (type == entry_type::unspecified)
			{
				error = file_system_error::none;
				return entry;
			}
			if (type != entry_type::unspecified && entry.type() == type)
			{
				error = file_system_error::none;
				return entry;
			}
		}
		error = file_system_error::not_found;
		return FileSystemEntry{};
	}

	// get error string from code
	std::string FileSystem::errorString(const file_system_error error)
	{
		switch (error)
		{
		case file_system_error::not_found:
			return "Error: no such entry.";
		case file_system_error::no_permission:
			return "Error: no permission.";
		case file_system_error::duplicate:
			return "Error: duplicate entry.";
		case file_system_error::could_not_create:
			return "Error: could not create entry.";
		case file_system_error::none:
			return "OK.";
		case file_system_error::failed:
			return "Error: failed.";
		default:
			return "Error: unknown error.";
		}
	}
} // namespace fileSystem
