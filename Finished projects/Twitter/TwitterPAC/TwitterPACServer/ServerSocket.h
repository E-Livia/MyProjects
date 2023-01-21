#pragma once
#include <asio.hpp>
#include <iostream>
#include <optional>

using asio::ip::tcp;

class ServerSocket
{
public:
    ServerSocket(ServerSocket& otherSingleton) = delete;
    void operator= (const ServerSocket& copySingleton) = delete;

    tcp::acceptor* InitAcceptor();
    tcp::socket* InitSocket();
    void StartServerSocket();
    void SendData(std::string message);
    std::optional<std::string> RecieveData();

    static ServerSocket* GetInstance();

private:
    static ServerSocket* instance;
    tcp::acceptor* acceptor;
    tcp::socket* socket;
    asio::io_context io_context;

    ServerSocket()
    {
        acceptor = InitAcceptor();
        socket = InitSocket();
    }

    ~ServerSocket() {
        delete socket;
        delete acceptor;
        std::cout << "Server closed";
    }
};