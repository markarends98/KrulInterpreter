#ifndef S_INFO_H
#define S_INFO_H
#include "abstract_operation.h"

namespace operation
{
	class Info final : public AbstractOperation
	{
	public:
		void execute(asio::ip::tcp::iostream& stream) override;
		std::string getCommand() override { return std::string("info"); }
	};

	class InfoOperationCreator final : public AbstractOperationCreator
	{
		std::string getIdentifier() override { return std::string("info"); }
		std::unique_ptr<AbstractOperation> create() override { return std::make_unique<Info>(); }
	};

} // namespace operation
#endif // S_INFO_H