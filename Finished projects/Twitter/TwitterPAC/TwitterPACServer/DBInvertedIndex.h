#pragma once
#include <unordered_map>
#include <pqxx/pqxx>
#include <sstream>
#include <set>
#include <vector>
#include "DBLink.h"
#include "DBPost.h"

class DBInvertedIndex
{
public:
	void CreateDictionary();
	std::vector<std::vector<std::string>> CheckSentence(std::string givenSentence);
	std::vector<std::vector<std::string>> ShowMatchedPosts(std::set<std::string> postsToBeShown);

private:
	std::unordered_map<std::string, std::vector<std::string>> dictionary;
};

