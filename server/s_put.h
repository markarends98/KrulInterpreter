#ifndef S_PUT_H
#define S_PUT_H
#include "abstract_operation.h"
#include "server_file_system.h"

namespace operation
{
	class Put final : public AbstractOperation
	{
	private:
		fileSystem::ServerFileSystem server_;
		std::string target_;
		std::vector<char> data_;
		int file_size_ = 0;
	public:
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("put"); }
	};

	class PutOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("put"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Put>(); }
	};
}

#endif // S_PUT_H
