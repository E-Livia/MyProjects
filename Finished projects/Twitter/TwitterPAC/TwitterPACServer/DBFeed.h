#pragma once
#include <vector>
#include <string>
#include <memory>

class DBFeed
{
public:
	void CalculatePosts();
	std::vector<std::string> GetPost();
	void ClearFeed();
private:
	static std::unique_ptr<std::vector<std::vector<std::string>>> m_postari;
	static int m_index;
};

