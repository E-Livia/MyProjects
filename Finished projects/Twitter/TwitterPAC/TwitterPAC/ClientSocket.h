#pragma once
#include <asio.hpp>
#include <iostream>
#include <optional>

using asio::ip::tcp;

class ClientSocket
{
public:
	ClientSocket(ClientSocket& otherSingleton) = delete;
	void operator=(const ClientSocket& copySingleton) = delete;

	static ClientSocket* GetInstance();

	void ConnectToServer(char* ipAddress);
	void SendData(std::string buffer);
	std::optional<std::string> RecieveData();

private:
	static ClientSocket* instance;

	asio::io_context io_context;
	tcp::socket* socket;

	ClientSocket() {

	}
};


