#ifndef C_DIR_H
#define C_DIR_H
#include "abstract_operation.h"

namespace operation
{
	namespace client
	{
		class dir final : public abstract_operation
		{
		private:
			std::string directory_;
		public:
			void readString(const std::string& string) override;
			std::string execute() override;
			std::string getCommand() override { return std::string("dir"); }
		};
	} // namespace client
} // namespace operation
#endif // C_DIR_H

