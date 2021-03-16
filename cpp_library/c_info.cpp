#include "c_info.h"

namespace operation
{
	namespace client
	{
		std::string info::execute()
		{
			return std::string(this->getCommand());
		}
	} // namespace client
} // namespace operation
