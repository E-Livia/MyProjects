#include "UserMenu.h"
#include "ClientSocket.h"
#include "../../cereal/archives/json.hpp"

ClientSocket* CsocketMenu = ClientSocket::GetInstance();


void UserMenu::CreateMenu()
{
	system("COLOR 3");
	std::string spacing = "          ";

	std::cout << spacing << m_bar_corner_left_up << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_corner_right_up << std::endl;
	std::cout << spacing << m_bar_vertically << "         MENU         " << m_bar_vertically << std::endl;

	std::cout << spacing << m_bar_left_breakup << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_right_breakup << std::endl;
	std::cout << spacing << m_bar_vertically << "  1->Post             " << m_bar_vertically << std::endl;

	std::cout << spacing << m_bar_left_breakup << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_right_breakup << std::endl;
	std::cout << spacing << m_bar_vertically << "  2->Personal Profile " << m_bar_vertically << std::endl;

	std::cout << spacing << m_bar_left_breakup << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_right_breakup << std::endl;
	std::cout << spacing << m_bar_vertically << "  3->Feed             " << m_bar_vertically << std::endl;

	std::cout << spacing << m_bar_left_breakup << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_right_breakup << std::endl;
	std::cout << spacing << m_bar_vertically << "  4->Keyword Search   " << m_bar_vertically << std::endl;

	std::cout << spacing << m_bar_left_breakup << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_right_breakup << std::endl;
	std::cout << spacing << m_bar_vertically << "  5->User Search      " << m_bar_vertically << std::endl;

	std::cout << spacing << m_bar_left_breakup << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_right_breakup << std::endl;
	std::cout << spacing << m_bar_vertically << "  6->Follow           " << m_bar_vertically << std::endl;

	std::cout << spacing << m_bar_left_breakup << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_right_breakup << std::endl;
	std::cout << spacing << m_bar_vertically << "  7->Exit             " << m_bar_vertically << std::endl;

	std::cout << spacing << m_bar_corner_left_down << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_corner_right_fown << std::endl;

	std::cout << "         " << "Select an option to go to" << std::endl;
	std::cout << "         " << m_bar_corner_left_up << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal;
	std::cout << std::endl;
	std::cout << "         " << m_bar_vertically << "   ";

	uint16_t opt;
	std::cin >> opt;
	SetOptionMenu(opt);
	GetMenuOption();
}


void UserMenu::GoToPost()
{
	Post post;
	int command = 0;
	std::string spacing = "          ";

	do {
		std::cout << spacing << m_bar_corner_left_up << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_corner_right_up << std::endl;
		std::cout << spacing << m_bar_vertically << "  1->Write Post       " << m_bar_vertically << std::endl;

		std::cout << spacing << m_bar_left_breakup << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_right_breakup << std::endl;
		std::cout << spacing << m_bar_vertically << "  2->Back to menu     " << m_bar_vertically << std::endl;
		std::cout << spacing << m_bar_corner_left_down << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_corner_right_fown << std::endl;

		std::cout << "         " << "Select an option to go to" << std::endl;
		std::cout << "         " << m_bar_corner_left_up << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal << m_bar_horizontal;
		std::cout << std::endl;
		std::cout << "         " << m_bar_vertically << "   ";
		std::cin >> command;
		switch (command)
		{
		case 1:
			system("CLS");
			post.CreatePost();
			std::cout << std::endl;
			//system("CLS");
			break;
		case 2:
			system("CLS");
			CreateMenu();
			break;
		}
	} while (command != 2);
}

void UserMenu::GoToPersonalProfile()
{
	PersonalProfile prof;
	prof.ShowInterfaceProfile();
}

void UserMenu::GoToFeed()
{
	Feed feed;
	feed.ShowFeed();
}

void UserMenu::GoToKeywordSearch()
{
	InvertedIndex keySearch;
	keySearch.KeySearch();
	Exit();
}

void UserMenu::GoToUserSearch()
{
	UserSearch user;
	user.UserSearching();
	Exit();
}

void UserMenu::GoToFollow()
{
	FriendsNetwork friends;
	int option;

	std::cout << "Introudceti optiunea dorita  1.Follow 2.UnFollow 0.Exit" << std::endl;
	std::cin >> option;
	switch (option)
	{
	case 1:
		system("CLS");
		friends.GoToFollow();
		Exit();
		break;
	case 2:
		system("CLS");
		friends.GoToUnFollow();
		Exit();
		break;
	case 0:
		system("CLS");
		CreateMenu();
		break;
	default:
		break;
	}
}

void UserMenu::GetMenuOption()
{
	uint16_t optionSelected;
	optionSelected = GetOptionMenu();
	switch (optionSelected)
	{
	case 1:
		system("CLS");
		GoToPost();
		break;
	case 2:
		system("CLS");
		GoToPersonalProfile();
		break;
	case 3:
		system("CLS");
		GoToFeed();
		break;
	case 4:
		system("CLS");
		GoToKeywordSearch();
		break;
	case 5:
		system("CLS");
		GoToUserSearch();
		break;
	case 6:
		system("CLS");
		GoToFollow();
		break;
	case 7:
		break;
	}
}

void UserMenu::MenuRead(char* ipAdress)
{
	do {
		system("CLS");
		CreateMenu();
		GetMenuOption();

	} while (GetOptionMenu() != 6);
}

void UserMenu::SetOptionMenu(const uint16_t &opt)
{
	m_option_user_menu = opt;
}

const uint16_t UserMenu::GetOptionMenu()const
{
	return m_option_user_menu;
}

void UserMenu::Exit()
{
	std::string back;
	std::cout << std::endl;
	std::cout << "Go back to menu press 0!" << std::endl;
	std::cin >> back;
	if (back == "0") {
		system("CLS");
		CreateMenu();
		GetMenuOption();
	}
}

