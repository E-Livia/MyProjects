#include "User.h"
#include "../../cereal/archives/json.hpp"
#include "ClientSocket.h"
#include"UserMenu.h"
#include <regex>

ClientSocket* clientSocket = ClientSocket::GetInstance();

void User::Display()
{
	system("cls");
	std::string m_answer;
	std::cout << "			Welcome to TWITTER!			" << std::endl;
	std::cout << "		Do you have an account? YES/NO		" << std::endl;
	std::getline(std::cin, m_answer);
	std::for_each(m_answer.begin(), m_answer.end(), [](char& m_character)
		{
			m_character = ::tolower(m_character);
		});
	while (m_answer != "yes" && m_answer != "no")
	{
		std::cout << "The answer is wrong! Please try again!\n";
		std::getline(std::cin, m_answer);
		std::for_each(m_answer.begin(), m_answer.end(), [](char& m_character)
			{
				m_character = ::tolower(m_character);
			});
	}
	if (m_answer == "yes")
	{
		LogIn();
	}
	else if (m_answer == "no")
	{
		SignUp();
		system("cls");
		LogIn();
	}
}

void User::LogIn()
{
	UserMenu menu;
	std::string username;
	do {
		std::cout << "Username-ul poate contine doar litere, cifre si caracterele _ . - si are minim 4 caractere" <<
			std::endl << "Username: ";
		std::cin >> username;
	} while (!std::regex_match(username, std::regex("^[a-zA-Z0-9_.-]{4,}")));
	m_username = username;
	std::cout << "Password: ";
	std::cin >> m_password;
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("username", m_username), cereal::make_nvp("password", m_password));
	}
	clientSocket->SendData("0" + os.str());
	std::optional<std::string> result = clientSocket->RecieveData();

	std::string statusCode;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(statusCode);
	}
	if (statusCode == "success")
	{
		system("cls");
		menu.CreateMenu();
	}
	else
	{
		std::cout << "Authentication error. Please try again\n";
		LogIn();
	}
}

void User::SignUp()
{
	std::string m_password2;
	std::string username;
	do {
		std::cout << "Username-ul poate contine doar litere, cifre si caracterele _ . - si are minim 4 caractere" <<
			std::endl << "Username: ";
		std::cin >> username;
	} while (!std::regex_match(username, std::regex("^[a-zA-Z0-9_.-]{4,}")));
	m_username = username;
	std::cout << "Password: ";
	std::cin >> m_password;
	std::cout << "Confirm password: ";
	std::cin >> m_password2;
	while (m_password != m_password2)
	{
		std::cout << "The passwords are different!" << std::endl;
		m_password.clear();
		m_password2.clear();
		std::cout << "Password: ";
		std::cin >> m_password;
		std::cout << "Confirm password: ";
		std::cin >> m_password2;
	}
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("username", m_username), cereal::make_nvp("password", m_password));
	}
	clientSocket->SendData("1" + os.str());
	std::optional<std::string> result = clientSocket->RecieveData();
	//std::cout << result.value()<<std::endl;

	std::string statusCode;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(statusCode);
	}
	while (statusCode == "error")
	{
		std::cout << "Registration error. Please try again\n";
		SignUp();
	}
}