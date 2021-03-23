#ifndef S_REN_H
#define S_REN_H
#include <abstract_operation.h>
#include "server_file_system.h"

namespace operation
{
	class Ren final : public AbstractOperation
	{
	private:
		fileSystem::ServerFileSystem server_;
		std::string path_;
		std::string new_name_;
	public:
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("ren"); }
	};

	class RenOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("ren"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Ren>(); }
	};
}

#endif // S_REN_H
