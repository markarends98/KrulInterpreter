#ifndef S_DIR_H
#define S_DIR_H
#include "abstract_operation.h"

namespace operation
{
	namespace server
	{
		class dir final : public abstract_operation
		{
		private:
			std::string directory_;
		public:
			void readStream(asio::ip::tcp::iostream& stream) override;
			std::string execute() override;
			std::string getCommand() override { return std::string("dir"); }
		};
	} // namespace server
} // namespace operation
#endif // S_DIR_H

