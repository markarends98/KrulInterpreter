#ifndef C_PUT_H
#define C_PUT_H
#include <abstract_operation.h>
#include "client_file_system.h"

namespace operation {
	class Put final : public AbstractOperation
	{
	private:
		fileSystem::ClientFileSystem client_;
		std::string target_;
		std::string data_;
		int file_size_ = 0;
	public:
		void init() override;
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("put"); }
		bool setFile(const std::string& target);
	private:
		_NODISCARD std::pair<std::string, int> getFile(const std::string& target) const;
	};

	class PutOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("put"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Put>(); }
	};
}
#endif // C_PUT_H
