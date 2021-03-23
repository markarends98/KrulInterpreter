#ifndef C_MKDIR_H
#define C_MKDIR_H
#include <abstract_operation.h>

namespace operation
{
	class MkDir final : public AbstractOperation
	{
	private:
		std::string path_;
		std::string directory_;
	public:
		void init() override;
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("mkdir"); }
		void setPath(const std::string& path) { path_ = path; }
		void setDirectory(const std::string& directory) { directory_ = directory; }
	};

	class MkDirOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("mkdir"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<MkDir>(); }
	};
} // namespace operation
#endif // C_MKDIR_H
