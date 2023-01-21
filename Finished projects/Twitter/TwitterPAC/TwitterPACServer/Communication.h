#pragma once
#include <iostream>
#include "DBUser.h"
#include "DBPost.h"
#include "DBComment.h"
#include "DBInvertedIndex.h"
#include "DBFeed.h"
#include "DBLikes.h"
#include "DBDislikes.h"
#include "DBFollowers.h"
#include "DBLevenshtein.h"
#include "../Logging/Logging.h"

class Communication
{
public:
	enum class Operations {
		eLogin, //0
		eRegister, //1
		eReadUser, //2
		eUpdateUser, //3
		eReturnCurrentSession, //4
		eCreatePost, //5
		eReadPost, //6
		eReadAllPosts, //7
		eUpdatePost, //8
		eDeletePost, //9
		eCreateComment, //10
		eReadComment, //11
		eReadAllComments, //12
		eUpdateComment, //13
		eDeleteComment, //14
		eLikePost, //15
		eUnlikePost, //16
		eCalculatePostLikes, //17
		eCheckExistingLike, //18
		eDislikePost, //19
		eUndislikePost, //20
		eCalculatePostDislikes, //21
		eCheckExistingDislike, //22
		eFollowPerson, //23
		eUnfollowPerson, //24
		eCalculateFollowers, //25
		eCheckExistingFollower, //26
		eReadAllUsersFeed, //27 -- de utilizat in cadrul feedului pentru searchuri
		eCreateDictionary, //28
		eCheckSentence, //29
		eGetFeedPost, //30
		eClearFeed, //31
		eGenerateUserList, // 32 --de utilizat pentru levvenshtein
		eShowFollowersForProfile, //33
		eCalculatePostComments, //34
		eCalculatePostRetweets, //35
		eRetweetPost, //36
		eReferencedTweet //37
	};
	void ExecuteOperation(Operations operation,std::string& data);
};

