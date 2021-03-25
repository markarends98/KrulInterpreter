#ifndef S_DEL_H
#define S_DEL_H
#include <abstract_operation.h>

#include "server_file_system.h"

namespace operation
{
	class Del final : public AbstractOperation
	{
	private:
		fileSystem::ServerFileSystem server_;
		std::string target_;
	public:
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("del"); }
	};

	class DelOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("del"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Del>(); }
	};
}

#endif // S_DEL_H
