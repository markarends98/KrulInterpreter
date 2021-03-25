#ifndef C_DEL_H
#define C_DEL_H
#include <abstract_operation.h>

namespace operation
{
	class Del final : public AbstractOperation
	{
	private:
		std::string target_;
	public:
		void init() override;
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("del"); }
		void setTarget(const std::string& target) { target_ = target; }
	};

	class DelOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("del"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Del>(); }
	};
} // namespace operation
#endif // C_DEL_H
