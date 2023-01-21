#pragma once
#include <string>
#include "DBUser.h"

class DBFollowers
{
public:
	void FollowPerson(const std::string& toFollow);
	void UnfollowPerson(const std::string& userToUnfollow);
	std::string CalculateFollowers(const std::string& userID);
	bool CheckExistingFollower(const std::string& toCheck);
	std::vector<std::string> ShowFollowersFromProfile(const std::string& userID);
private:
	DBUser* user = DBUser::getInstance();
	std::string m_username = user->GetUser(), m_userID = user->GetUserID();
};

