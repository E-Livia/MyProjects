#include "Feed.h"
#include "UserMenu.h"
#include "ClientSocket.h"
#include "../../cereal/archives/json.hpp"

ClientSocket* ClientSocketFeed = ClientSocket::GetInstance();

void Feed::ReadPostFromDB(std::string& postID, std::string& postBody, std::string& dateCreated, std::string& postedBy)
{
	ClientSocketFeed->SendData("30");
	std::optional<std::string> result = ClientSocketFeed->RecieveData();

	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(postID, postBody, dateCreated, postedBy);
	}

}

void Feed::DisplayPostStructure(const std::string &postID, const std::string &postBody, const std::string &dateCreated, const std::string &postedBy)
{
	std::cout << std::endl <<"Posted By: "<< postedBy << std::endl <<"Post Body: "<< postBody << std::endl <<"Date Created: " << dateCreated.substr(0, 19) << std::endl;
	std::cout << std::endl << "Likes " << DisplayLikesNo(postID) << " | " << "Dislikes " << DisplayDislikesNo(postID) << " | " << "Comments " << DisplayCommentsNo(postID) << " | " << "Retweets " <<DisplayRetweetsNo(postID) << std::endl;
}

void Feed::ShowFeed()
{
	std::string postID, postBody, dateCreated, postedBy;
	ReadPostFromDB(postID,postBody,dateCreated,postedBy);

	if (postedBy == "-1")
	{
		system("cls");
		std::cout << "Feedul este gol! Trebuie sa ai pe cineva la follow!"<<std::endl;
		UserMenu menu;
		menu.CreateMenu();
	}
	else
	{
		DisplayPostStructure(postID, postBody, dateCreated, postedBy);
		int choice;
		do {

			if (CheckExistingLike(postID) == false && CheckExistingDislike(postID) == false)
			{
				std::cout << std::endl << "Press: \n1 to like, \n2 to dislike, \n3 to comment, \n4 to see all the comments, \n5 to retweet the post,\n6 go to reference tweet \n9 to continue scrolling, \n0 to go back to menu" << std::endl;
			}
			else if (CheckExistingLike(postID) == true && CheckExistingDislike(postID) == false)
			{
				std::cout << std::endl << "Press: \n1 to unlike, \n2 to dislike, \n3 to comment, \n4 to see all the comments, \n5 to retweet the post,\n6 go to reference tweet \n9 to continue scrolling, \n0 to go back to menu" << std::endl;
			}
			else if (CheckExistingLike(postID) == false && CheckExistingDislike(postID) == true)
			{
				std::cout << std::endl << "Press: \n1 to like, \n2 to remove dislike, \n3 to comment, \n4 to see all the comments, \n5 to retweet the post,\n6 go to reference tweet \n9 to continue scrolling, \n0 to go back to menu" << std::endl;
			}
			else if (CheckExistingLike(postID) == true && CheckExistingDislike(postID) == true)
			{
				std::cout << std::endl << "Press: \n1 to unlike, \n2 to remove dislike, \n3 to comment, \n4 to see all the comments, \n5 to retweet the post,\n6 go to reference tweet \n9 to continue scrolling, \n0 to go back to menu" << std::endl;
			}
			std::cin >> choice;

			switch (choice)
			{
			case 1:
			{
				if (CheckExistingLike(postID) == false)
				{
					AddLike(postID);
					if (CheckExistingDislike(postID) == true)
					{
					RemoveDislike(postID);
					}
					DisplayPostStructure(postID, postBody, dateCreated, postedBy);
					break;
				}
				RemoveLike(postID);
				DisplayPostStructure(postID, postBody, dateCreated, postedBy);
				break;
			}
			case 2:
				if (CheckExistingDislike(postID) == false)
				{
					AddDislike(postID);
					if (CheckExistingLike(postID) == true)
					{
						RemoveLike(postID);
					}
					DisplayPostStructure(postID, postBody, dateCreated, postedBy);
					break;
				}
				RemoveDislike(postID);
				DisplayPostStructure(postID, postBody, dateCreated, postedBy);
				break;
			case 3:
				AddComment(postID);
				DisplayPostStructure(postID, postBody, dateCreated, postedBy);
				break;
			case 4:
				SeeAllComments(postID);
				break;
			case 5:
				Retweet(postID, postBody);
				break;
			case 6:
				GoToReferenceTweet(postID);
				break;
			case 9:
				ReadPostFromDB(postID, postBody, dateCreated, postedBy);
				if (postID == "-1")
					goto jump;
				DisplayPostStructure(postID, postBody, dateCreated, postedBy);
				break;
			case 0:
			jump:
				system("cls");
				ClearFeed();
				UserMenu menu;
				menu.CreateMenu();
				break;
			}
		} while (choice != 0);
	}
}

void Feed::ClearFeed()
{
	ClientSocketFeed->SendData("31");
	std::optional<std::string> result = ClientSocketFeed->RecieveData();

	std::string statusCode;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(statusCode);
	}
	if (statusCode == "success")
	{
		std::cout << std::endl << "The feed has been closed with success" << std::endl;
	}
	else
	{
		std::cout << std::endl << "The ClearFeed function failed" << std::endl;
	}
}

void Feed::AddLike(const std::string& postID)
{
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("postID", postID));
	}
	ClientSocketFeed->SendData("15" + os.str());
	std::optional<std::string>result = ClientSocketFeed->RecieveData();
}

 std::string Feed::DisplayLikesNo(const std::string& postID) const
{
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("postID", postID));
	}
	ClientSocketFeed->SendData("17" + os.str());
	std::optional<std::string>result = ClientSocketFeed->RecieveData();

	std::string likesCounter;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(likesCounter);
	}
	return likesCounter;
}

bool Feed::CheckExistingLike(const std::string& postID) const
{
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("postID", postID));
	}
	ClientSocketFeed->SendData("18" + os.str());
	std::optional<std::string>result = ClientSocketFeed->RecieveData();

	bool check;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(check);
	}
	return check;
}

void Feed::RemoveLike(const std::string& postID)
{
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("postID", postID));
	}
	ClientSocketFeed->SendData("16" + os.str());
	std::optional<std::string>result = ClientSocketFeed->RecieveData();
}

void Feed::AddDislike(const std::string& postID)
{
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("postID", postID));
	}
	ClientSocketFeed->SendData("19" + os.str());
	std::optional<std::string>result = ClientSocketFeed->RecieveData();
}

std::string Feed::DisplayDislikesNo(const std::string& postID) const
{
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("postID", postID));
	}
	ClientSocketFeed->SendData("21" + os.str());
	std::optional<std::string>result = ClientSocketFeed->RecieveData();

	std::string dislikesCounter;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(dislikesCounter);
	}
	return dislikesCounter;
}

bool Feed::CheckExistingDislike(const std::string& postID) const
{
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("postID", postID));
	}
	ClientSocketFeed->SendData("22" + os.str());
	std::optional<std::string>result = ClientSocketFeed->RecieveData();

	bool check;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(check);
	}
	return check;
}

void Feed::RemoveDislike(const std::string& postID)
{
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("postID", postID));
	}
	ClientSocketFeed->SendData("20" + os.str());
	std::optional<std::string>result = ClientSocketFeed->RecieveData();
}

void Feed::AddComment(const std::string& postID)
{
	std::cout << "Write a comment: " << std::endl;
	std::cin.get();
	std::getline(std::cin, m_comment);

	ClientSocketFeed->SendData("4");
	std::optional<std::string> result = ClientSocketFeed->RecieveData();
	std::string user, userID;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(user, userID);
	}

	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("userID", userID), cereal::make_nvp("postID", postID), cereal::make_nvp("commentBody",m_comment));
	}
	ClientSocketFeed->SendData("10"+os.str());
}

std::string Feed::DisplayCommentsNo(const std::string& postID) const
{
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("postID", postID));
	}
	ClientSocketFeed->SendData("34" + os.str());
	std::optional<std::string>result = ClientSocketFeed->RecieveData();

	std::string commentsCounter;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(commentsCounter);
	}
	return commentsCounter;
}

void Feed::SeeAllComments(const std::string& postID)
{
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("postID", postID));
	}
	ClientSocketFeed->SendData("12" + os.str());
	std::optional<std::string>result = ClientSocketFeed->RecieveData();

	std::string vectorSize;
	std::string commentID, userID, commentBody;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(vectorSize);
		int stringToInt = std::stoi(vectorSize);
		for (int i = 0; i < stringToInt; i++)
		{
			archive_in(commentID, userID,commentBody);
			std::stringstream os2;
			{
				cereal::JSONOutputArchive archive_out(os2);
				archive_out(cereal::make_nvp("userID", userID));
			}
			ClientSocketFeed->SendData("2" + os2.str());
			std::optional<std::string>resultUsername = ClientSocketFeed->RecieveData();
			std::string username;
			std::stringstream is2(resultUsername.value());
			{
				cereal::JSONInputArchive archive_in(is2);
				archive_in(username);
			}
			std::cout <<"Comment posted by: " << username << std::endl << commentBody << std::endl;
		}
	}
}

void Feed::Retweet(const std::string& postID, std::string postBody)
{
	ClientSocketFeed->SendData("4");
	std::optional<std::string> result = ClientSocketFeed->RecieveData();
	std::string user, user_ID,retweetText;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(user, user_ID);
	}

	std::cout << postBody <<std::endl<< "Introudceti text pentru retweet: ";
	std::cin.get();
	std::getline(std::cin, retweetText);
	postBody = postBody + " RT:"+retweetText;

	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("userID", user_ID), cereal::make_nvp("postBody", postBody), cereal::make_nvp("retweetID", postID));
	}
	std::cout << "Retweet succesful";
	ClientSocketFeed->SendData("36" + os.str());
}

std::string Feed::DisplayRetweetsNo(const std::string& postID) const
{
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("postID", postID));
	}
	ClientSocketFeed->SendData("35" + os.str());
	std::optional<std::string>result = ClientSocketFeed->RecieveData();

	std::string retweetsCounter;
	std::stringstream is(result.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(retweetsCounter);
	}
	return retweetsCounter;
}

void Feed::GoToReferenceTweet(const std::string& postID)
{
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(CEREAL_NVP(postID));
	}
	ClientSocketFeed->SendData("37" + os.str());
	std::optional<std::string> currentSession = ClientSocketFeed->RecieveData();

	std::string postBody, postedBy, datePosted, postIDreceived;
	std::stringstream is(currentSession.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(datePosted, postBody, postIDreceived, postedBy);
	}
	if (postBody != "error")
	{
		std::cout << "Posted By: " << postedBy << std::endl;
		std::cout<< "Post body: " << postBody << std::endl;
		std::cout << "Date Created: " << datePosted.substr(0, 19) << std::endl;
		return;
	}
	std::cout << "Nu exista o postare de baza" << std::endl;
}
