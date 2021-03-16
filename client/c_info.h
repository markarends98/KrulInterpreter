#ifndef C_INFO_H
#define C_INFO_H
#include "abstract_operation.h"

namespace operation
{
	class Info final : public AbstractOperation
	{
	public:
		void readStream(asio::ip::tcp::iostream& stream) override;
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("info"); }
	};

	class InfoOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("info"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Info>(); }
	};
} // namespace operation
#endif // C_INFO_H