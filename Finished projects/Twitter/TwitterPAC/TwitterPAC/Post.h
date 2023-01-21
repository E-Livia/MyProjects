#pragma once
#include<string>
#include<iostream>
#include<vector>

class Post
{
public:
	void CreatePost();
	void SeeAPost();
private:
	std::string m_text;
};

