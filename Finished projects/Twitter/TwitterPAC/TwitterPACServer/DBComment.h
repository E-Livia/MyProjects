#pragma once
#include <string>
#include <pqxx/pqxx>
#include <iostream>
#include "ServerSocket.h"
#include "DBLink.h"
#include "../cereal/archives/json.hpp"
#include "DBUser.h"

class DBComment
{
public:
	void CreateComment(const std::string& userID,const std::string& postID, const std::string& commentBody);
	std::vector<std::vector<std::string>> ReadAllComments(const std::string& postID);
	std::vector<std::string> ReadComment(const std::string& commentID);
	void UpdateComment(const std::string& postID, const std::string& newCommentBody);
	void DeleteComment(const std::string& commentID);
	std::string CountComments(const std::string& postID);
private:
	DBUser* user = DBUser::getInstance();
	std::string m_username = user->GetUser(), m_userID = user->GetUserID();
};

