#include "pch.h"
#include "file_system_entry.h"

#include <fstream>


#include "date_util.h"

namespace fileSystem {
	FileSystemEntry::FileSystemEntry()
	{
		this->exists_ = false;
		this->type_ = entry_type::unspecified;
	}

	FileSystemEntry::FileSystemEntry(const std::filesystem::directory_entry& directoryEntry)
	{
		this->exists_ = directoryEntry.exists();
		if(!this->exists_)
		{
			return;
		}

		this->name_ = directoryEntry.path().filename().string();
		this->path_ = directoryEntry.path().string();
		this->extension_ = directoryEntry.path().extension().string();;
		this->parent_ = directoryEntry.path().parent_path().string();
		this->size_ = directoryEntry.file_size();
		this->type_ = directoryEntry.is_directory() ? entry_type::directory : directoryEntry.is_regular_file() ? entry_type::file : entry_type::miscellaneous;
		
		std::ifstream file_stream(directoryEntry.path().string(), std::ios::in | std::ios::binary);
		if (file_stream.good())
		{
			while(!file_stream.eof())
			{
				this->bytes_.push_back(file_stream.get());
			}
		}

		auto time = directoryEntry.last_write_time();
		this->date_modified_ = dateUtil::toTimeT(time);
		this->date_modified_string_ = dateUtil::format(time, "%Y-%m-%d %H:%M:%S");
	}

	FileSystemEntry FileSystemEntry::findEntry(const std::string& path)
	{
		const std::filesystem::directory_entry entry = std::filesystem::directory_entry(path);
		return FileSystemEntry{ entry };
	}

	bool FileSystemEntry::exists() const
	{
		return this->exists_;
	}

	std::string FileSystemEntry::name() const
	{
		return this->name_;
	}

	std::string FileSystemEntry::path() const
	{
		return this->path_;
	}

	std::string FileSystemEntry::extension() const
	{
		return this->extension_;
	}

	std::string FileSystemEntry::parent() const
	{
		return this->parent_;
	}

	time_t FileSystemEntry::dateModified() const
	{
		return  this->date_modified_;
	}

	std::string FileSystemEntry::dateModifiedString() const
	{
		return  this->date_modified_string_;
	}

	std::vector<char> FileSystemEntry::bytes() const
	{
		return this->bytes_;
	}

	uintmax_t FileSystemEntry::size() const
	{
		return this->size_;
	}

	entry_type FileSystemEntry::type() const
	{
		return this->type_;
	}

	std::string FileSystemEntry::detailedString() const
	{
		return std::string(1, static_cast<char>(this->type_)) + "|" + this->name_ + "|" + this->date_modified_string_ + "|" + std::to_string(this->size_);
	}

	bool FileSystemEntry::isDirectory() const
	{
		return this->type_ == entry_type::directory;
	}

	bool FileSystemEntry::isFile() const
	{
		return this->type_ == entry_type::file;
	}

	bool FileSystemEntry::isMiscellaneous() const
	{
		return this->type_ == entry_type::miscellaneous;
	}
} // namespace fileSystem