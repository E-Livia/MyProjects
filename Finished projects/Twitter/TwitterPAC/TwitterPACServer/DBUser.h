#pragma once
#include <string>
#include <pqxx/pqxx>
#include <iostream>
#include "DBLink.h"
#include "ServerSocket.h"
#include "../cereal/archives/json.hpp"

class DBUser
{
public:
	DBUser(DBUser& otherSingleton) = delete;
	void operator=(const DBUser& copySingleton) = delete;

	void CreateUser(std::string & user, const std::string const& pw);
	void LoginUser(std::string & user, std::string const& pw);
	std::string ReadUser(const std::string userID);
	void UpdateUser(const std::string& newUsername);
	std::vector<std::vector<std::string>> ReadAllUsers();

	std::string GetUser(); //din clasa
	std::string GetUserID(); //din clasa

	static DBUser* getInstance();
private:
	static DBUser* instance;

	DBUser()
	{

	}
	std::string m_user, m_userID;
};


