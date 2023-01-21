#pragma once
#include<iostream>
#include<string>

class User
{
public:
	void Display();
	void LogIn();
	void SignUp();
private:
	std::string m_username;
	std::string m_password;
};

