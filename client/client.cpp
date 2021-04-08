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
#include "c_mkdir.h"
#include "c_dir.h"
#include "c_ren.h"
#include "c_quit.h"
#include "c_del.h"
#include "c_put.h"
#include "c_get.h"
#include "c_sync.h"
#include "date_util.h"
#include <thread>
#include <iostream>
#include <chrono>
void f()
{
	std::cout << "Output from thread...";
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "...thread calls flush()\n";
	//std::cout.flush();
}

int main() {
	try {
		const char* server_address{ "localhost" };
		const char* server_port{ "12345" };
		const char* prompt{ "avansync client> " };

		asio::ip::tcp::iostream server{ server_address, server_port };
		if (!server) throw std::runtime_error("could not connect to server");
		
		factory::OperationFactory operation_factory;
		operation_factory.registerOperation<operation::InfoOperationCreator>();
		operation_factory.registerOperation<operation::MkDirOperationCreator>();
		operation_factory.registerOperation<operation::DirOperationCreator>();
		operation_factory.registerOperation<operation::RenOperationCreator>();
		operation_factory.registerOperation<operation::QuitOperationCreator>();
		operation_factory.registerOperation<operation::DelOperationCreator>();
		operation_factory.registerOperation<operation::PutOperationCreator>();
		operation_factory.registerOperation<operation::GetOperationCreator>();
		operation_factory.registerOperation<operation::SyncOperationCreator>();

		std::unique_ptr<operation::AbstractOperation> operation;
		
		std::string server_response;
		if (server && streamUtil::getLine(server, server_response)) {
			std::cout << server_response << stringUtil::lf;
		}
		
		while (server) {
			if(!server.rdbuf()->is_open())
			{
				break;
			}

			do {
				// get command from user input
				std::string command;
				streamUtil::cin(prompt, command);

				// get operation by command string
				operation = operation_factory.get(command);

				if (operation != nullptr)
				{
					operation->init();
					operation->execute(server);
					operation->readStream(server);
				}
			} while (operation == nullptr);
		}

	}
	catch (const std::exception& ex) {
		std::cerr << "client: " << ex.what() << stringUtil::lf;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
