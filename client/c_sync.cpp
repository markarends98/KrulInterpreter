#include "c_sync.h"

#include <thread>


#include "c_dir.h"
#include "c_del.h"
#include "c_put.h"
#include "c_get.h"
#include "c_mkdir.h"

#include "date_util.h"
#include "stream_util.h"

namespace operation
{
	void Sync::execute(asio::ip::tcp::iostream& stream)
	{
		sync("", "", stream);
	}

	void Sync::readStream(asio::ip::tcp::iostream& stream)
	{
		std::cout << this->response("Completed.") << stringUtil::lf;
	}

	void Sync::sync(const std::string& path, const std::string& dirName, asio::ip::tcp::iostream& stream)
	{
		std::string full_dir = dirName;

		if(!path.empty())
		{
			full_dir = path + fileSystem::dirs + dirName;
		}
		// Get current dir from server
		Dir cmd_dir;
		cmd_dir.setPath(full_dir);
		cmd_dir.execute(stream);

		// Get response from server
		std::string cmd_dir_response;
		streamUtil::getLine(stream, cmd_dir_response);

		// Get file amount
		const auto [valid, amount] = stringUtil::extractInteger(cmd_dir_response);

		// Server files from current dir
		std::vector<SyncFile> server_files;
		
		if (valid)
		{
			// Get files inside current dir from server
			for (int i = 0; i < amount; i++)
			{
				std::string server_entry;
				streamUtil::getLine(stream, server_entry);
				std::vector<std::string> server_sentry_data = stringUtil::splitString<std::string>(server_entry, '|');
				if (server_sentry_data.size() != 4)
				{
					continue;
				}

				SyncFile server_file;
				server_file.type = server_sentry_data[0];
				server_file.name = server_sentry_data[1];
				server_file.modified_at = dateUtil::toTimeT(server_sentry_data[2]);
				server_file.mod = dateUtil::format(server_file.modified_at);
				server_file.size = std::stoi(server_sentry_data[3]);
				server_file.dir = full_dir;
				server_file.path = full_dir + server_sentry_data[1];
				server_files.push_back(server_file);
			}
		}else
		{
			std::string empty;
			streamUtil::getLine(stream, empty);

			std::cout << this->prompt("Creating dir") << stringUtil::wspc << full_dir << stringUtil::wspc << "on server" << stringUtil::lf;
			MkDir cmd_mkdir;
			cmd_mkdir.setPath(path);
			cmd_mkdir.setDirectory(dirName);
			cmd_mkdir.execute(stream);
			cmd_mkdir.readStream(stream);
		}
		
		//Delete files that don't exist on client side
		//for (const SyncFile& sync_file : server_files)
		//{
		//	fileSystem::FileSystemEntry c_entry = this->client_.queryEntry(sync_file.path);

		//	if (!c_entry.exists())
		//	{
		//		std::cout << this->prompt("Deleting") << stringUtil::wspc << sync_file.path << stringUtil::wspc << "from server" << stringUtil::lf;
		//		Del cmd_del;
		//		cmd_del.setTarget(sync_file.path);
		//		cmd_del.execute(stream);
		//		cmd_del.readStream(stream);
		//	}
		//}

		// Client files from current dir
		const fileSystem::directory_iterator entries = this->client_.iterator(full_dir);

		for (const auto& client_entry : entries)
		{
			if (client_entry.isDirectory())
			{
				// sync directory
				sync(full_dir, client_entry.name(), stream);
			}
			else {
				// parse files
				std::string name = client_entry.name();
				auto it = std::find_if(server_files.begin(), server_files.end(), [&name](const SyncFile& obj) {return obj.name == name; });

				std::string target = full_dir + fileSystem::dirs + name;
				bool exists_on_server = false;
				bool client_newer = false;
				
				if (it != server_files.end())
				{
					SyncFile server_file = *it;
					client_newer = client_entry.dateModified() > server_file.modified_at;
					exists_on_server = true;
				}

				if(!exists_on_server || (exists_on_server && client_newer))
				{
					// Uploading file to server
					std::cout << this->prompt("Uploading") << stringUtil::wspc << target << stringUtil::wspc << "to server" << stringUtil::lf;
					Put put_cmd;

					put_cmd.setFile(target);
					put_cmd.execute(stream);
					put_cmd.readStream(stream);
				}

				if(exists_on_server && !client_newer)
				{
					// Downloading file from server
					std::cout << this->prompt("Downloading") << stringUtil::wspc << target << stringUtil::wspc << "from server" << stringUtil::lf;
					Get get_cmd;
					get_cmd.setFile(target);
					get_cmd.execute(stream);
					get_cmd.readStream(stream);
				}
			}
		}
	}
}
