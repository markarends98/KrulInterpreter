#ifndef C_GET_H
#define C_GET_H
#include <abstract_operation.h>
#include "client_file_system.h"

namespace operation
{
	class Get final : public AbstractOperation
	{
	private:
		std::string file_;
		fileSystem::ClientFileSystem client_;
	public:
		void init() override;
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("get"); }
		void setFile(const std::string& file) { file_ = file; }
	};

	class GetOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("get"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Get>(); }
	};
}

#endif // C_GET_H
