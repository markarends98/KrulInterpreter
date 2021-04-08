#ifndef C_SYNC_H
#define C_SYNC_H
#include <abstract_operation.h>

#include "client_file_system.h"

namespace operation
{
	class Sync final : public AbstractOperation
	{
	private:
		struct SyncFile
		{
			std::string type;
			std::string dir;
			std::string name;
			std::string path;
			std::string mod;
			time_t modified_at;
			int size;
		};
		
		fileSystem::ClientFileSystem client_;
	public:
		void execute(asio::ip::tcp::iostream& stream) override;
		void readStream(asio::ip::tcp::iostream& stream) override;
		void sync(const std::string& path, const std::string& dirName, asio::ip::tcp::iostream& stream);
		std::string getCommand() override { return std::string("sync"); }
	};

	class SyncOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("sync"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Sync>(); }
	};
}

#endif // C_SYNC_H
