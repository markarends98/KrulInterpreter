#include "c_dir.h"
#include "string_util.h"

#include <iostream>

namespace operation
{
	namespace client
	{
		void dir::readString(const std::string& string)
		{
			if(string.empty())
			{
				std::cout << this->getCommand() << ">" << stringUtil::lf;
				std::cout << "Enter directory name: ";
				std::getline(std::cin, this->directory_);
			}

			this->directory_ = string;
		}
		
		std::string dir::execute()
		{
			
			return std::string(this->getCommand() + stringUtil::crlf + directory_);
		}
	} // namespace client
} // namespace operation
