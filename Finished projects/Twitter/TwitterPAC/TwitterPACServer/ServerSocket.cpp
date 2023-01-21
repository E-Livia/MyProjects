#include "ServerSocket.h"
#include <optional>

tcp::acceptor* ServerSocket::InitAcceptor()
{
    try
    {
        return new tcp::acceptor(io_context, tcp::endpoint(tcp::v4(), 27015));
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return nullptr;
}

tcp::socket* ServerSocket::InitSocket()
{
    try
    {
        return new tcp::socket(io_context);
        asio::socket_base::keep_alive option(true);
        socket->set_option(option);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return nullptr;
}

void ServerSocket::SendData(std::string buffer)
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

void ServerSocket::StartServerSocket()
{
    try
    {
        std::cout << "Server started";
        acceptor->accept(*socket);
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

std::optional<std::string> ServerSocket::RecieveData()
{
    try
    {
        char data[5000];
        asio::error_code error;
        size_t length = socket->read_some(asio::buffer(data), error);
        if (error == asio::error::eof) return std::nullopt; // Connection closed cleanly by peer.
            else if (error)
                throw asio::system_error(error); // Some other error.
         return std::string{ data, length };
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return {};
}

ServerSocket* ServerSocket::instance(nullptr);

ServerSocket* ServerSocket::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new ServerSocket();
    }
    return instance;
}