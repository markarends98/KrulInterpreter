#include "s_info.h"

namespace operation
{
	namespace server
	{
		std::string info::execute()
		{
			return std::string("AvanSync server 1.0, copyright (c) 2020 Mark Arends - 2139401");
		}
	} // namespace server
} // namespace operation
