#ifndef C_REN_H
#define C_REN_H
#include <abstract_operation.h>

namespace operation
{
	class Ren final : public AbstractOperation
	{
	private:
		std::string path_;
		std::string new_name_;
	public:
		void init() override;
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("ren"); }
		void setPath(const std::string& path) { path_ = path; }
		void setNewName(const std::string& newName) { new_name_ = newName; }
	};

	class RenOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("ren"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Ren>(); }
	};
}

#endif // C_REN_H
