#pragma once
#include<string>
#include<vector>
#include<iostream>
#include "DBUser.h"

class DBLevenshtein
{
public:
	std::vector<std::vector<std::string>> GenerateResults(std::string inputWord);
private:
	int LevenshteinDistance(std::string firstWord, std::string secondWord);
};

