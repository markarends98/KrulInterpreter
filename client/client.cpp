//
// client.cpp
//
// Created by Bob Polis at 2020-12-02
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>


#include "stream_util.h"
#include "string_util.h"
#include "operation_factory.h"
#include "client_file_system.h"
#include "c_info.h"

int main() {
	try {
		const char* server_address{ "localhost" };
		const char* server_port{ "12345" };
		const char* prompt{ "avansync client> " };
		const char* rprompt{ "avansync response> " };

		asio::ip::tcp::iostream server{ server_address, server_port };
		if (!server) throw std::runtime_error("could not connect to server");
		
		factory::OperationFactory operation_factory;
		operation_factory.registerOperation<operation::InfoOperationCreator>();

		std::unique_ptr<operation::AbstractOperation> operation;
		
		while (server) {
			std::string server_response;
			if (streamUtil::getLine(server, server_response)) {
				if (!server_response.empty()) {
					// print response
					std::cout << rprompt << server_response << stringUtil::lf;

					// exit
					if (server_response == "Bye.") {
						break;
					}

					if (operation != nullptr)
					{
						operation->readStream(server);
					}
				}

				do {
					// get command from user input
					std::string command;
					streamUtil::cin(prompt, command);

					// get operation by command string
					operation = operation_factory.get(command);

					if (operation != nullptr)
					{
						operation->execute(server);
						operation->clean();
					}
				} while (operation == nullptr);
			}
		}

	}
	catch (const std::exception& ex) {
		std::cerr << "client: " << ex.what() << stringUtil::lf;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
