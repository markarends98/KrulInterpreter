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
	};
} // namespace operation
#endif // C_INFO_H

