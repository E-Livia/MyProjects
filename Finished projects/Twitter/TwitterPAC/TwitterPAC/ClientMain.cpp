
#include <iostream>
#include <asio.hpp>
#include "UserMenu.h"
#include "User.h"
#include "ClientSocket.h"
#include "../../cereal/archives/json.hpp"
using asio::ip::tcp;

int main(int argc, char* argv[])
{
	ClientSocket* clientSocket = ClientSocket::GetInstance();
	clientSocket->ConnectToServer(argv[1]);
	User user;
	user.Display();
 }