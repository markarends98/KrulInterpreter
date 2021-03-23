#ifndef S_MKDIR_H
#define S_MKDIR_H
#include "abstract_operation.h"
#include "server_file_system.h"

namespace operation
{
	class MkDir final : public AbstractOperation
	{
	private:
		fileSystem::ServerFileSystem server_;
		std::string path_;
		std::string directory_;
	public:
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("mkdir"); }
	};

	class MkDirOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("mkdir"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<MkDir>(); }
	};

} // namespace operation
#endif // S_MK_DIR_H