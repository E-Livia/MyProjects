#pragma once
#include <string>
#include <pqxx/pqxx>
#include <iostream>
#include "../cereal/archives/json.hpp"
#include "ServerSocket.h"
#include "DBLink.h"

class DBPost
{
public:
	void CreatePost(const std::string& userID, const std::string& postBody, std::string retweetID = "-1");
	std::vector<std::string> ReadPost(const std::string& idPost);
	std::vector<std::vector<std::string>> ReadAllPosts(const std::string& userID); //a fi folosit pe userProfile
	void UpdatePost(const std::string& idPost, const std::string& newBody);
	void DeletePost(const std::string& idPost);

	std::vector<std::string> GetInitialPost(const std::string& idPost);

	std::string CountRetweets(std::string postID);

	std::vector<std::string>*& GetPostData(); //returneaza postarile in ordinea prioritatii
};

