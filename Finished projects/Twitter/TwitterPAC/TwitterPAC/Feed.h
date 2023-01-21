#pragma once
#include"Post.h"

class Feed
{
public:
	void ReadPostFromDB(std::string& postID, std::string& postBody, std::string& dateCreated, std::string& postedBy);
	void DisplayPostStructure(const std::string& postID,const std::string& postBody, const std::string &dateCreated, const std::string &postedBy);
	void ShowFeed();
	void ClearFeed();	

	void AddLike(const std::string& postID);
	std::string DisplayLikesNo(const std::string& postID)const;
	bool CheckExistingLike(const std::string& postID)const;
	void RemoveLike(const std::string& postID);

	void AddDislike(const std::string& postID);
	std::string DisplayDislikesNo(const std::string& postID)const;
	bool CheckExistingDislike(const std::string& postID)const;
	void RemoveDislike(const std::string& postID);

	void AddComment(const std::string& postID);
	std::string DisplayCommentsNo(const std::string& postID)const;
	void SeeAllComments(const std::string& postID);

	void Retweet(const std::string& postID, std::string postBody);
	std::string DisplayRetweetsNo(const std::string& postID)const;
	void GoToReferenceTweet(const std::string& postID);

private:
	std::string m_comment;
};

