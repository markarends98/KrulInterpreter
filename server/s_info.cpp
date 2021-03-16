#include "s_info.h"
#include "string_util.h"

namespace operation
{
	void Info::execute(asio::ip::tcp::iostream& stream)
	{
		stream << "AvanSync server 1.0, copyright (c) 2020 Mark Arends - 2139401" << stringUtil::crlf;
	}
}
