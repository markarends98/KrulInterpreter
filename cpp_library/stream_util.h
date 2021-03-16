#ifndef STREAM_UTIL_H
#define STREAM_UTIL_H
#include <iostream>
#include <string>

#include "string_util.h"

namespace streamUtil
{
	static inline void cin(const std::string& message, std::string& output, const bool acceptEmpty = false)
	{
		do {
			std::cout << message;
			std::getline(std::cin, output);
			stringUtil::trim(output);
			if(acceptEmpty)
			{
				break;
			}
		} while (output.empty());
	}

	template<typename elem,typename traits>
	static inline bool getLine(std::basic_istream<elem, traits>& stream, std::string& output)
	{
		if(std::getline(stream, output))
		{
			stringUtil::eraseCr(output);
			return true;
		}
		return false;
	}
}
#endif // STREAM_UTIL_H
