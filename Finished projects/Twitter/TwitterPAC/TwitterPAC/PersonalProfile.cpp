#include "PersonalProfile.h"
#include "UserMenu.h"
#include "ClientSocket.h"
#include "../../cereal/archives/json.hpp"
#include <iomanip>

ClientSocket* CsocketProfile = ClientSocket::GetInstance();

void  PersonalProfile::ShowInterfaceProfile()
{
	//get user logged
	CsocketProfile->SendData("4");
	std::optional<std::string> result = CsocketProfile->RecieveData();
	std::string user, user_ID;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(user, user_ID);
	}
	std::cout << "     Name-->  " << user << std::endl;

	//interface
	std::cout << m_bar_corner_left_up << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal <<
		m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_corner_right_up << std::endl;
	std::cout << m_bar_vertically << "1.Post History" << " 2.ShowFollowers" << " 0.Exit" << m_bar_vertically;
	std::cout << std::endl;
	std::cout << m_bar_corner_left_down << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal <<
		m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_corner_right_fown << std::endl;

	std::cout << "Select an option to go to" << std::endl;
	std::cout << m_bar_corner_left_up << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal;
	std::cout << std::endl;
	std::cout << m_bar_vertically << "   ";

	uint16_t option;
	std::cin >> option;
	GetOptionProfile(option);

}

void  PersonalProfile::GetOptionProfile(uint16_t const& option)
{
	UserMenu menu;
	FriendsNetwork friends;
	switch (option)
	{
	case 1:
		system("CLS");
		ShowPostHistory();
		Exit();
		break;
	case 2:
		system("CLS");
		std::cout << "Number of followers: ";
		friends.GetNumberOfFollowers();
		std::cout << std::endl;
		friends.ShowFollowers();
		Exit();
		break;
	case 0:
		system("CLS");
		menu.CreateMenu();
	}
}

void PersonalProfile::ShowPostHistory()
{
	std::string posts;

	CsocketProfile->SendData("4");
	std::optional<std::string> result = CsocketProfile->RecieveData();
	std::string user, userID;

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

	std::string word;
	CsocketProfile->SendData("7" + os.str());
	std::optional<std::string> currentSession = CsocketProfile->RecieveData();

	std::stringstream is1(currentSession.value());
	{
		cereal::JSONInputArchive archive_in(is1);
		std::string vectorSize;
		archive_in(vectorSize);
		int vectorSizeInt = std::stoi(vectorSize);
		std::cout << std::left << std::setw(75) << "Mesaj" << std::setw(20) << "Data postarii" << std::endl;
		for (auto index = 0; index < vectorSizeInt; index++)
		{
			std::string postID, message, dateCreated;
			archive_in(postID, message, dateCreated);
			if (message.size() < 70)
			{
				std::cout << std::left << std::setw(75) << message << std::setw(20) << dateCreated.substr(0, 19) << std::endl;
				continue;
			}
			std::cout << std::left << std::setw(75) << message.substr(0, 70) << std::setw(20) << dateCreated.substr(0, 19) << std::endl;
			std::cout << std::left << std::setw(75) << message.substr(71, message.size()) << std::endl;
		}
	}
}

void PersonalProfile::Exit()
{
	std::string back;
	std::cout << std::endl << "Go back to menu press 0!" << std::endl;
	std::cin >> back;
	if (back == "0") {
		system("CLS");
		ShowInterfaceProfile();
	}
}
