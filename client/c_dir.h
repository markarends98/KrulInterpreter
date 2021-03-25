#ifndef C_DIR_H
#define C_DIR_H
#include <abstract_operation.h>

namespace operation
{
	class Dir final : public AbstractOperation
	{
	private:
		std::string path_;
	public:
		void init() override;
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("dir"); }
		void setPath(const std::string& path) { path_ = path; }
	};

	class DirOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("dir"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Dir>(); }
	};
}

#endif // C_DIR_H