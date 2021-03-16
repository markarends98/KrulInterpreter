#ifndef S_INFO_H
#define S_INFO_H
#include "abstract_operation.h"

namespace operation
{
	namespace server
	{
		class info final : public abstract_operation
		{
		public:
			std::string execute() override;
			std::string getCommand() override { return std::string("info"); }
		};
	} // namespace server
} // namespace operation
#endif // S_INFO_H
