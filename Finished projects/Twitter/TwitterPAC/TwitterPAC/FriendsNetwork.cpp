#include "FriendsNetwork.h"
#include "ClientSocket.h"
#include"UserSearch.h"
#include <iomanip>
#include "../../cereal/archives/json.hpp"

ClientSocket* CsocketFriends = ClientSocket::GetInstance();


void FriendsNetwork::GoToFollow()
{
		UserSearch search;
		std::string status_code, personToFollow;
	
		search.UserSearching();
		std::cout << std::endl;
		std::cout << "Introduceti userul dorit pentru a urmarii: ";
		std::cin >> personToFollow;

		std::stringstream os;
		{
			cereal::JSONOutputArchive archive_out(os);
			archive_out(CEREAL_NVP(personToFollow));
		}
		CsocketFriends->SendData("23" + os.str());
		std::optional<std::string> currentSession = CsocketFriends->RecieveData();
		std::stringstream is(currentSession.value());
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(status_code);
		}
		if (status_code == "failure") {
			std::cout << "Error followig person: " << personToFollow << std::endl;
			std::cout << "Try again!" << std::endl;
		}
		if (status_code == "success") {
			std::cout << "You followed: " << personToFollow <<" with succes"<< std::endl;
		}
}

void FriendsNetwork::GoToUnFollow()
{
	ShowFollowers();
	std::cout << std::endl;
	std::string status_code, personToFollow;
	std::cout << "Introduceti userul dorit pentru a nu mai urmarii: ";
	std::cin >> personToFollow;

	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(CEREAL_NVP(personToFollow));
	}
	CsocketFriends->SendData("24" + os.str());
	std::optional<std::string> currentSession = CsocketFriends->RecieveData();
	std::stringstream is(currentSession.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(status_code);
	}
	if (status_code == "failure") {
		std::cout << "Error unfollowig person: " << personToFollow << std::endl;
		std::cout << "Try again!" << std::endl;
	}
	if (status_code == "success") {
		std::cout << "You unfollowed: " << personToFollow << " with succes" << std::endl;
	}
}

void FriendsNetwork::GetNumberOfFollowers()
{
	std::string numberOfFollowers;

	CsocketFriends->SendData("4");
	std::optional<std::string> result = CsocketFriends->RecieveData();
	std::string user, user_ID;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(user, user_ID);
	}
		std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(CEREAL_NVP(user_ID));
	}
	CsocketFriends->SendData("25" + os.str());
	std::optional<std::string> currentSession = CsocketFriends->RecieveData();

	std::stringstream is2(currentSession.value());
	{
		cereal::JSONInputArchive archive_in(is2);
		archive_in(numberOfFollowers);
	}
	std::cout << numberOfFollowers<< std::endl;
}

void FriendsNetwork::ShowFollowers()
{
	CsocketFriends->SendData("4");
	std::optional<std::string> result = CsocketFriends->RecieveData();
	std::string user, userID, vectorSize, username;

	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(user, userID);
	}
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("userID", userID));
	}

	CsocketFriends->SendData("33" + os.str());
	std::optional<std::string> currentSession = CsocketFriends->RecieveData();

	std::stringstream isF(currentSession.value());
	{
		cereal::JSONInputArchive archive_in(isF);
		archive_in(vectorSize);
		int stringToInt = std::stoi(vectorSize);
		std::cout << std::left << std::setw(20) << "Users found";
		for (auto index = 0; index < stringToInt; index++)
		{
			archive_in(username);
			std::cout << std::endl<< std::left << std::setw(20) << username;
		}
	}
}

