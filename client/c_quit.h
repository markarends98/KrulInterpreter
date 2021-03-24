#ifndef C_QUIT_H
#define C_QUIT_H
#include <abstract_operation.h>

namespace operation
{
	class Quit final : public AbstractOperation
	{
	public:
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("quit"); }
	};

	class QuitOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("quit"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Quit>(); }
	};
}
#endif // C_QUIT_H
