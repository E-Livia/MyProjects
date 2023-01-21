#pragma once
#include <string>
#include "DBUser.h"

class DBDislikes
{
public:
	void DislikePost(const std::string& postID);
	void UndislikePost(const std::string& postID);
	std::string CalculatePostDislikes(const std::string& postID);
	bool CheckExistingDislike(const std::string& postID);
private:
	DBUser* user = DBUser::getInstance();
	std::string m_username = user->GetUser(), m_userID = user->GetUserID();
};

