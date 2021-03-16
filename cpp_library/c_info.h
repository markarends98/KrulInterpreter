#ifndef C_INFO_H
#define C_INFO_H
#include "abstract_operation.h"

namespace operation
{
	namespace client
	{
		class info final : public abstract_operation
		{
		public:
			std::string execute() override;
			std::string getCommand() override { return std::string("info"); }
		};
	} // namespace client
} // namespace operation
#endif // C_INFO_H
