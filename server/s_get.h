#ifndef S_GET_H
#define S_GET_H
#include <abstract_operation.h>

#include "server_file_system.h"

namespace operation
{
	class Get final : public AbstractOperation
	{
	private:
		fileSystem::ServerFileSystem server_;
		std::string target_;
		std::string data_;
		int file_size_ = 0;
	public:
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("get"); }
	private:
		_NODISCARD std::pair<std::string, int> getFile(const std::string& target) const;
	};

	class GetOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("get"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Get>(); }
	};
}
#endif // S_GET_H
