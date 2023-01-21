#pragma once
#include <pqxx/pqxx>

class DBLink
{
public:
	DBLink(DBLink& otherSingleton) = delete;
	void operator=(const DBLink& copySingleton) = delete;

	static pqxx::connection *GetInstance();
private:
	static std::unique_ptr<DBLink> instance;
	const std::string m_connectionString;
	pqxx::connection m_connectionObject;
	DBLink() : 
		m_connectionString("host=ec2-54-74-35-87.eu-west-1.compute.amazonaws.com port=5432 dbname=d8iolcesns1bj4 user=pktunepcutgdqh password=7e3eeef2e01e0d8ae555c7236b1c3375789259dfb6acba41225cc4f55394836c"),
		m_connectionObject(m_connectionString.c_str())
	{
	}
};

