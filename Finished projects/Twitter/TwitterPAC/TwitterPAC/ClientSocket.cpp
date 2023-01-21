
#include "ClientSocket.h"

ClientSocket* ClientSocket::instance(nullptr);

ClientSocket* ClientSocket::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new ClientSocket();
    }
    return instance;
}

void ClientSocket::ConnectToServer(char* ipAddress)
{
	auto ip_address = asio::ip::make_address_v4(ipAddress);
	const unsigned port = 27015;
	auto endpoint = tcp::endpoint{ ip_address, port };

	auto resolver = tcp::resolver{ io_context };
	auto endpoints = resolver.resolve(endpoint);
	socket = new tcp::socket{ io_context };
	asio::connect(*socket, endpoints);
    asio::socket_base::keep_alive option(true);
    socket->set_option(option);
}

void ClientSocket::SendData(std::string buffer)
{
    try {
        asio::error_code ignored_error;
        asio::write(*socket, asio::buffer(buffer), ignored_error);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

std::optional<std::string>
ClientSocket::RecieveData()
{
    try
    {
        char data[5000];
        asio::error_code error;
        while (true)
        {
            size_t length = socket->read_some(asio::buffer(data), error);
            if (asio::buffer(data).data() == NULL)
            {
                break;
            }
            if (error == asio::error::eof) return std::nullopt; // Connection closed cleanly by peer.
            else if (error)
                throw asio::system_error(error); // Some other error.
            return std::string{ data, length };
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return {};
}

