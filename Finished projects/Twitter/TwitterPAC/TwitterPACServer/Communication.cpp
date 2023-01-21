#include "Communication.h"

void Communication::ExecuteOperation(Operations operation,std::string& data)
{
	std::ofstream LoggerOut("LoggingRecords.txt", std::ios_base::app);
	Logging Logger(LoggerOut);
	switch (operation)
	{
	case Communication::Operations::eLogin:
	{
		DBUser* user = DBUser::getInstance();
		std::string username, password;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(username, password);
		}
		try
		{
			user->LoginUser(username, password);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("success")));
			}
			data = os.str();
			Logger.log("Logging in was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("error")));
			}
			data = os.str();
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eRegister:
	{
		DBUser* user = DBUser::getInstance();
		std::string username, password;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(username, password);
		}
		std::stringstream os;
		try
		{
			user->CreateUser(username, password);
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("success")));
			}
			Logger.log("Register was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("error")));
			}
		}
		data = os.str();
		break;
	}
	case Communication::Operations::eReadUser:
	{
		DBUser* user = DBUser::getInstance();
		std::string userID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(userID);
		}
		std::stringstream os;
		try
		{
			std::string usernameReturnResult = user->ReadUser(userID);
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("username",usernameReturnResult));
			}
			Logger.log("Reading username was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("error")));
			}
		}
		data = os.str();
		break;
	}
	case Communication::Operations::eUpdateUser:
	{
		DBUser* user = DBUser::getInstance();
		std::string newUsername;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(newUsername);
		}
		try
		{
			user->UpdateUser(newUsername);
			data = "";
			Logger.log("Updating user data was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eReturnCurrentSession:
	{
		DBUser* user = DBUser::getInstance();
		std::string username = user->GetUser();
		std::string id = user->GetUserID();
		std::stringstream os;
		{
			cereal::JSONOutputArchive archive_out(os);
			archive_out(CEREAL_NVP(username), CEREAL_NVP(id));
		}
		data = os.str();
		Logger.log("Returned current session successfully", Logging::Level::eINFO);
		break;
	}
	case Communication::Operations::eCreatePost:
	{
		DBPost post;
		std::string postBody, userID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(userID,postBody);
		}
		try
		{
			post.CreatePost(userID, postBody);
			data = "";
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eReadPost:
	{
		DBPost post;
		std::string id;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(id);
		}
		std::vector<std::string> postData = post.ReadPost(id);
		std::stringstream os;
		{
			cereal::JSONOutputArchive archive_out(os);
			archive_out(cereal::make_nvp("datePosted",postData[0]), cereal::make_nvp("postBody",postData[1]), 
				cereal::make_nvp("postID",postData[2]), cereal::make_nvp("postedBy",postData[3]));
		}
		data = os.str();
		Logger.log("Read post successfully", Logging::Level::eINFO);
		break;
	}
	case Communication::Operations::eReadAllPosts:
	{
		DBPost post;
		std::string userID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(userID);
		}
		try
		{
			std::vector<std::vector<std::string>> allPostData = post.ReadAllPosts(userID);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				int counter = 1;
				archive_out(cereal::make_nvp("vectorSize", std::to_string(allPostData.size())));
				for (auto currentPost : allPostData)
				{
					archive_out(cereal::make_nvp("postID", currentPost[0]), cereal::make_nvp("message", currentPost[1]),
						cereal::make_nvp("date_created", currentPost[2]));
				}

			}
			data = os.str();
			Logger.log("Read all posts successfully", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eUpdatePost:
	{
		DBPost post;
		std::string postID, newPostBody;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(postID, newPostBody);
		}
		try
		{
			post.UpdatePost(postID, newPostBody);
			data = "";
			Logger.log("Updating post data was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eDeletePost:
	{
		DBPost post;
		std::string postID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(postID);
		}
		try
		{
			post.DeletePost(postID);
			data = "";
			Logger.log("Deleting post was succsseful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eCreateComment:
	{
		DBComment comment;
		std::string userID,postID,commentBody;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(userID, postID, commentBody);
		}
		try
		{
			comment.CreateComment(userID, postID, commentBody);
			data = "";
			Logger.log("Created comment successfully", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eReadComment:
	{
		DBComment comment;
		std::string commentID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(commentID);
		}
		try
		{
			std::vector<std::string> commentData= comment.ReadComment(commentID);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("commentID", commentData[0]), cereal::make_nvp("userID", commentData[1]),
					cereal::make_nvp("commentBody", commentData[2]));
			}
			data = os.str();
			Logger.log("Reading comment was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eReadAllComments:
	{
		DBComment comment;
		std::string postID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(postID);
		}
		try
		{
			std::vector<std::vector<std::string>> allCommentData = comment.ReadAllComments(postID);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				int counter = 1;
				archive_out(cereal::make_nvp("VectorSize", std::to_string(allCommentData.size())));
				for (auto currentComment : allCommentData)
				{
					archive_out(cereal::make_nvp("commentID", currentComment[0]), cereal::make_nvp("userID", currentComment[1]),
						cereal::make_nvp("commentBody", currentComment[2]));
				}
				
			}
			data = os.str();
			Logger.log("Reading all comments was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eUpdateComment:
	{
		DBComment comment;
		std::string commentID, newCommentBody;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(commentID, newCommentBody);
		}
		try
		{
			comment.UpdateComment(commentID, newCommentBody);
			data = "";
			Logger.log("Updating comment data was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eDeleteComment:
	{
		DBComment comment;
		std::string commentID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(commentID);
		}
		try
		{
			comment.DeleteComment(commentID);
			data = "";
			Logger.log("Deleting comment data was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eLikePost:
	{
		DBLikes likes;
		std::string postID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(postID);
		}
		std::stringstream os;
		try
		{
			likes.LikePost(postID);
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("success")));
			}
			Logger.log("Liked post successfully", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("failure")));
			}
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		data = os.str();
		break;
	}
	case Communication::Operations::eUnlikePost:
	{
		DBLikes likes;
		std::string postID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(postID);
		}
		std::stringstream os;
		try
		{
			likes.UnlikePost(postID);
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("success")));
			}
			Logger.log("Diskliked post successfully", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("failure")));
			}
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		data = os.str();
		break;
	}
	case Communication::Operations::eCalculatePostLikes:
	{
		DBLikes likes;
		std::string postID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(postID);
		}
		try
		{
			std::string numberOfLikes = likes.CalculatePostLikes(postID);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(CEREAL_NVP(numberOfLikes));
			}
			data = os.str();
			Logger.log("Calculating the number of post likes was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eCheckExistingLike:
	{
		DBLikes likes;
		std::string postID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(postID);
		}
		try
		{
			bool existingFollower = likes.CheckExistingLike(postID);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(CEREAL_NVP(existingFollower));
			}
			data = os.str();
			Logger.log("Checking existing like was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eDislikePost:
	{
		DBDislikes dislikes;
		std::string postID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(postID);
		}
		std::stringstream os;
		try
		{
			dislikes.DislikePost(postID);
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("success")));
			}
			Logger.log("Disliked post successfully", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("failure")));
			}
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		data = os.str();
		break;
	}
	case Communication::Operations::eUndislikePost:
	{
		DBDislikes dislikes;
		std::string postID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(postID);
		}
		std::stringstream os;
		try
		{
			dislikes.UndislikePost(postID);
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("success")));
			}
			Logger.log("UnDisliked post successfully", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("failure")));
			}
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		data = os.str();
		break;
	}
	case Communication::Operations::eCalculatePostDislikes:
	{
		DBDislikes dislikes;
		std::string postID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(postID);
		}
		try
		{
			std::string numberOfDislikes = dislikes.CalculatePostDislikes(postID);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(CEREAL_NVP(numberOfDislikes));
			}
			data = os.str();
			Logger.log("Calculating the number of post dislikes was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eCheckExistingDislike:
	{
		DBDislikes dislikes;
		std::string postID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(postID);
		}
		try
		{
			bool existingFollower = dislikes.CheckExistingDislike(postID);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(CEREAL_NVP(existingFollower));
			}
			data = os.str();
			Logger.log("Checking existing dislike was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eFollowPerson:
	{
		DBFollowers followers;
		std::string personToFollow;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(personToFollow);
		}
		std::stringstream os;
		try
		{
			followers.FollowPerson(personToFollow);
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("success")));
			}
			Logger.log("Followed another person successfully", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("failure")));
			}
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		data = os.str();
		break;
	}
	case Communication::Operations::eUnfollowPerson:
	{
		DBFollowers followers;
		std::string personToFollow;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(personToFollow);
		}
		std::stringstream os;
		try
		{
			followers.UnfollowPerson(personToFollow);
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("success")));
			}
			Logger.log("Unfollowed said person successfully", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("failure")));
			}
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		data = os.str();
		break;
	}
	case Communication::Operations::eCalculateFollowers:
	{
		DBFollowers followers;
		std::string person;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(person);
		}
		try
		{
			std::string numberOfFollowers = followers.CalculateFollowers(person);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(CEREAL_NVP(numberOfFollowers));
			}
			data = os.str();
			Logger.log("Calculated followers successfully", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eCheckExistingFollower:
	{
		DBFollowers followers;
		std::string person;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(person);
		}
		try
		{
			bool existingFollower = followers.CheckExistingFollower(person);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(CEREAL_NVP(existingFollower));
			}
			data = os.str();
			Logger.log("Checking existing follow executed successfully", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eReadAllUsersFeed:
	{
		DBUser* user= DBUser::getInstance();
		try
		{
			std::vector<std::vector<std::string>> allUsers = user->ReadAllUsers();
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				int counter = 1;
				for (auto currentUser : allUsers)
				{
					archive_out(cereal::make_nvp("userID", currentUser[0]), cereal::make_nvp("username", currentUser[1]));
				}

			}
			data = os.str();
			Logger.log("Read all users successfully", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eCheckSentence:
	{
		DBInvertedIndex index;
		std::string inputSentence;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(inputSentence);
		}
		std::stringstream os;
		try
		{

			index.CreateDictionary();
			std::vector<std::vector<std::string>> indexResult = index.CheckSentence(inputSentence);
			{
				cereal::JSONOutputArchive archive_out(os);

				archive_out(cereal::make_nvp("vectorSize", std::to_string(indexResult.size())));
				for (const auto& currentIndexPost : indexResult)
				{
					archive_out(cereal::make_nvp("datePosted", currentIndexPost[0]), cereal::make_nvp("postBody", currentIndexPost[1]),
						cereal::make_nvp("postID", currentIndexPost[2]), cereal::make_nvp("postedBy", currentIndexPost[3]));
				}
			}
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		data = os.str();
		break;
	}
	case Communication::Operations::eGetFeedPost:
	{
		DBFeed feed;
		std::vector<std::string> postData;
		try
		{
			postData = feed.GetPost();
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("postID", postData[0]), cereal::make_nvp("postBody", postData[1]),
					cereal::make_nvp("dateCreated", postData[2]), cereal::make_nvp("postedBy", postData[3]));
			}
			Logger.log("Reading a post for feed was successfull", Logging::Level::eINFO);
			data = os.str();
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eClearFeed:
	{
		DBFeed feed;
		std::stringstream os;
		try
		{
			feed.ClearFeed();
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("success")));
			}
			Logger.log("Cleared feed successfully", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("status_code", std::string("failed")));
			}
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		data = os.str();
		break;
	}
	case Communication::Operations::eGenerateUserList:
	{
		DBLevenshtein levenshtein;
		try
		{
			std::string inputWord;
			std::stringstream is(data);
			{
				cereal::JSONInputArchive archive_in(is);
				archive_in(inputWord);
			}
			std::vector<std::vector<std::string>> levenshteinResults= levenshtein.GenerateResults(inputWord);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("vectorSize", std::to_string(levenshteinResults.size())));
				for (auto currentUser : levenshteinResults)
				{
					archive_out(cereal::make_nvp("id", currentUser[0]), cereal::make_nvp("username", currentUser[1]));
				}
			}
			Logger.log("Levenshtein returned successfully", Logging::Level::eINFO);
			data = os.str();
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eShowFollowersForProfile:
	{
		DBFollowers follower;
		try
		{
			std::string userID;
			std::stringstream is(data);
			{
				cereal::JSONInputArchive archive_in(is);
				archive_in(userID);
			}

			std::vector<std::string> followerVectorResult = follower.ShowFollowersFromProfile(userID);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("vectorSize", std::to_string(followerVectorResult.size())));
				for (auto currentUser : followerVectorResult)
				{
					archive_out(cereal::make_nvp("username", currentUser));
				}
			}
			data = os.str();
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eCalculatePostComments:
	{
		DBComment comment;
		std::string postID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(postID);
		}
		try
		{
			std::string numberOfComments = comment.CountComments(postID);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(CEREAL_NVP(numberOfComments));
			}
			data = os.str();
			Logger.log("Calculating the number of post comments was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eCalculatePostRetweets:
	{
		DBPost post;
		std::string postID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(postID);
		}
		try
		{
			std::string numberOfRetweets = post.CountRetweets(postID);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(CEREAL_NVP(numberOfRetweets));
			}
			data = os.str();
			Logger.log("Calculating the number of post retweets was successful", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eRetweetPost:
	{
		DBPost post;
		std::string postBody, userID, retweetID;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(userID, postBody, retweetID);
		}
		try
		{
			post.CreatePost(userID, postBody, retweetID);
			data = "";
		}
		catch (const std::exception& e)
		{
			Logger.log(e.what(), Logging::Level::eERROR);
		}
		break;
	}
	case Communication::Operations::eReferencedTweet:
	{
		DBPost post;
		std::string id;
		std::stringstream is(data);
		{
			cereal::JSONInputArchive archive_in(is);
			archive_in(id);
		}
		try
		{
			std::vector<std::string> postData = post.GetInitialPost(id);
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("datePosted", postData[0]), cereal::make_nvp("postBody", postData[1]),
					cereal::make_nvp("postID", postData[2]), cereal::make_nvp("postedBy", postData[3]));
			}
			data = os.str();
			Logger.log("Read referenced tweet succesfully", Logging::Level::eINFO);
		}
		catch (const std::exception& e)
		{
			std::stringstream os;
			{
				cereal::JSONOutputArchive archive_out(os);
				archive_out(cereal::make_nvp("datePosted", std::to_string('-1')), cereal::make_nvp("postBody", std::string("error")),
					cereal::make_nvp("postID", std::to_string('-1')), cereal::make_nvp("postedBy", std::to_string('-1')));
			}
			data = os.str();
			Logger.log(e.what(), Logging::Level::eINFO);
		}
		break;
	}
	default:
		Logger.log("Operatie necunoscuta", Logging::Level::eWARNING);
		data = "";
		break;
	}
}
