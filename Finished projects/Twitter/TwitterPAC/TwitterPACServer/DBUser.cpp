#include "DBUser.h"
#include "ServerSocket.h"

DBUser* DBUser::instance(nullptr);

DBUser* DBUser::getInstance()
{
	if (instance == nullptr)
	{
		instance = new DBUser();
	}
	return instance;
}


void DBUser::CreateUser(std::string & user, std::string const& pw)
{
	pqxx::work worker(*DBLink::GetInstance());
	worker.conn().prepare("SignUp", "INSERT INTO users VALUES($1,$2)");
	for (auto& c : user)
	{
		c = tolower(c);
	}
	try
	{
		pqxx::result signUpResult = worker.exec_prepared0("SignUp", user, worker.conn().encrypt_password(user, pw, "md5"));
		worker.commit();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.abort();
		throw std::runtime_error("SignUp failed");
	}

	//to be modified later
	catch (std::exception& e)
	{
		worker.conn().unprepare("SignUp");
		worker.abort();
		throw std::runtime_error(e.what());
	}
}

void DBUser::LoginUser(std::string & user, std::string const& pw)
{
	pqxx::work worker(*DBLink::GetInstance());
	worker.conn().prepare("LogIn", "SELECT * FROM users WHERE username = $1 AND password = $2");
	for (auto& c : user)
	{
		c = tolower(c);
	}
	try
	{
		pqxx::row logInResult = worker.exec_prepared1("LogIn", user, worker.conn().encrypt_password(user, pw, "md5"));
		m_user = user;
		m_userID = logInResult.at("id").c_str();
		worker.conn().unprepare("LogIn");
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("LogIn");
		throw std::runtime_error("Login failed");
	}
}

std::string DBUser::ReadUser(const std::string userID)
{
	pqxx::work worker(*DBLink::GetInstance());
	worker.conn().prepare("GetUsername", "SELECT username FROM users WHERE id= $1");
	try
	{
		pqxx::row getUsername = worker.exec_prepared1("GetUsername", userID);
		worker.commit();
		std::string username = getUsername[0].c_str();
		worker.conn().unprepare("GetUsername");
		return username;
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("GetUsername");
		throw std::runtime_error("Getting username failed");
	}
}

void DBUser::UpdateUser(const std::string& newUsername)
{
	pqxx::work worker(*DBLink::GetInstance());
	worker.conn().prepare("UpdateUsername", "UPDATE users SET username = $1 WHERE id=$2");
	try
	{
		pqxx::result updateUsernameResult = worker.exec_prepared0("UpdateUsername", newUsername, m_userID);
		worker.commit();
		m_user = newUsername;
		worker.conn().unprepare("UpdateUsername");
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("UpdateUsername");
		throw std::runtime_error("Updating username failed");
	}
}

std::vector<std::vector<std::string>> DBUser::ReadAllUsers()
{

	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("CountAllUsers", "SELECT COUNT(id) FROM users");
		worker.conn().prepare("ReadAllUsers", "SELECT * from users");
		pqxx::row countUsersResult = worker.exec_prepared1("CountAllUsers");
		std::string number = countUsersResult.at("count").c_str();
		pqxx::result readAllUsersResult = worker.exec_prepared_n(std::stoi(number), "ReadAllUsers");

		std::vector<std::vector<std::string>> usersResult;

		for (const auto currentUser : readAllUsersResult)
		{
			std::string userID = currentUser.at("id").c_str();
			std::string username = currentUser.at("username").c_str();
			usersResult.push_back(std::vector<std::string>{userID, username});
		}
		worker.commit();
		worker.conn().unprepare("CountAllUsers");
		worker.conn().unprepare("ReadAllUsers");
		return usersResult;
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CountAllUsers");
		worker.conn().unprepare("ReadAllUsers");
		throw std::runtime_error("Reading all users failed");
	}
}

std::string DBUser::GetUser()
{
	return m_user;
}

std::string DBUser::GetUserID()
{
	return m_userID;
}
