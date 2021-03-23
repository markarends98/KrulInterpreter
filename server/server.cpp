//
// server.cpp
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
#include "s_info.h"
#include "s_mkdir.h"
#include "s_dir.h"
#include "s_ren.h"

int main() {
	try {
		const int server_port{ 12345 };
		const char* prompt{ "avansync server> " };
		asio::io_context io_context;
		asio::ip::tcp::acceptor server{ io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), server_port) };
		asio::ip::tcp::iostream client;

		factory::OperationFactory operation_factory;
		operation_factory.registerOperation<operation::InfoOperationCreator>();
		operation_factory.registerOperation<operation::MkDirOperationCreator>();
		operation_factory.registerOperation<operation::DirOperationCreator>();
		operation_factory.registerOperation<operation::RenOperationCreator>();
		
		do {
			std::cout << "waiting for client to connect" << stringUtil::lf;
			server.accept(client.socket());
			std::cout << "client connected from " << client.socket().local_endpoint() << stringUtil::lf;
			client << "Welcome to AvanSync server 1.0" << stringUtil::crlf;

			while (client) {
				std::string request;
				streamUtil::getLine(client, request);
				if (request.empty())
				{
					client << "" << stringUtil::crlf;
				}
				else {
					std::cout << prompt << request;

					if (request == "quit") {
						client << "Bye." << stringUtil::crlf;
						std::cerr << "will disconnect from client " << client.socket().local_endpoint() << "." << stringUtil::lf;
						break;
					}

					std::unique_ptr<operation::AbstractOperation> operation = operation_factory.get(request);

					if (operation != nullptr)
					{
						operation->readStream(client);
						operation->execute(client);
					}
					else
					{
						std::cout << stringUtil::lf;
						client << "server command not found." << stringUtil::crlf;
					}
				}
			}
		} while (client);
	}
	catch (const std::exception& ex) {
		std::cerr << "server: " << ex.what() << stringUtil::lf;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
