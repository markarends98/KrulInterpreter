#ifndef S_DIR_H
#define S_DIR_H
#include <abstract_operation.h>
#include "server_file_system.h"

namespace operation
{
	class Dir final : public AbstractOperation
	{
	private:
		fileSystem::ServerFileSystem server_;
		std::string directory_;
	public:
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("dir"); }
	};

	class DirOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("dir"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Dir>(); }
	};
}

#endif // S_DIR_H