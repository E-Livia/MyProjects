#pragma once
#include <string>
#include "DBUser.h"

class DBLikes
{
public:
	void LikePost(const std::string& postID);
	void UnlikePost(const std::string& postID);
	std::string CalculatePostLikes(const std::string& postID);
	bool CheckExistingLike(const std::string& postID);
private:
	DBUser* user = DBUser::getInstance();
	std::string m_username = user->GetUser(), m_userID = user->GetUserID();
};

