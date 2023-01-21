#pragma once

#include <string>
#include <iostream>
#include <pqxx/pqxx>
#include "../Logging/Logging.h"
#include <iostream>
#include <string>
#include <asio.hpp>
#include "ServerSocket.h"
#include "Communication.h"

int main()
{
    std::ofstream LoggerOut("LoggingRecords.txt");
    Logging Logger(LoggerOut);
    Logger.log("Server application started", Logging::Level::eINFO);

    ServerSocket* socket = ServerSocket::GetInstance();
    socket->StartServerSocket();
    std::cout << std::endl;

    while (true)
    {
        Communication communicationInterface;
        auto data = socket->RecieveData();
        if (data.has_value())
        {
            size_t pos = data.value().find_first_of("{");
            std::string command = data.value().substr(0, pos);
            data = data.value().erase(0, pos);
            communicationInterface.ExecuteOperation(static_cast<Communication::Operations>(std::stoi(command)), data.value());
            socket->SendData(data.value());
        }
    }
}