#include "DBFollowers.h"

void DBFollowers::FollowPerson(const std::string& toFollow)
{
	pqxx::work worker(*DBLink::GetInstance());
	worker.conn().prepare("GetUserID", "SELECT id FROM users WHERE username= $1");
	worker.conn().prepare("FollowPerson", "INSERT INTO followers (follower,followed) VALUES ($1,$2)");
	try
	{
		pqxx::row getUserIdResult = worker.exec_prepared1("GetUserID", toFollow);
		pqxx::result likePost = worker.exec_prepared0("FollowPerson", m_userID, getUserIdResult.at("id").c_str());
		worker.conn().unprepare("FollowPerson");
		worker.conn().unprepare("GetUserID");
		worker.commit();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("GetUserID");
		worker.conn().unprepare("FollowPerson");
		throw std::runtime_error("User followed successfully");
	}
}


void DBFollowers::UnfollowPerson(const std::string& userToUnfollow)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("UnfollowPerson", "DELETE FROM followers WHERE follower = $1 AND followed = $2");
		worker.conn().prepare("GetUserID", "SELECT id FROM users WHERE username= $1");

		pqxx::row getUserIdResult = worker.exec_prepared1("GetUserID", userToUnfollow);
		pqxx::result unlikePost = worker.exec_prepared0("UnfollowPerson", m_userID, getUserIdResult.at("id").c_str());
		worker.conn().unprepare("UnfollowPerson");
		worker.conn().unprepare("GetUserID");
		worker.commit();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("GetUserID");
		worker.conn().unprepare("UnfollowPerson");
		throw std::runtime_error("Error unfollowing user");
	}
}	

std::string DBFollowers::CalculateFollowers(const std::string& userID)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("CountUserFollowers", "SELECT COUNT(id) FROM followers WHERE follower = $1");
		pqxx::row calculatePostLikes = worker.exec_prepared1("CountUserFollowers", userID);
		worker.conn().unprepare("CountUserFollowers");
		worker.commit();
		return calculatePostLikes[0].c_str();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CountUserFollowers");
		throw std::runtime_error("Error calculating followers");
	}
}

bool DBFollowers::CheckExistingFollower(const std::string& toCheck)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("CheckUserFollowers", "SELECT COUNT(id) FROM followers WHERE follower = $1 AND followed = $2");
		pqxx::row checkExistingFollower = worker.exec_prepared1("CheckUserFollowers", m_userID, toCheck);
		worker.conn().unprepare("CheckUserFollowers");
		if (checkExistingFollower.at("count").c_str() == std::string("1"))
			return 1;
		else
			return 0;
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CheckUserFollowers");
		throw std::runtime_error("Error checking existing follower");
	}
}

std::vector<std::string> DBFollowers::ShowFollowersFromProfile(const std::string& userID)
{
	pqxx::work worker(*DBLink::GetInstance());
	std::vector<std::string> followersList;
	try
	{

		worker.conn().prepare("CountNoFollowers", "SELECT COUNT(follower) FROM followers WHERE follower = $1");
		worker.conn().prepare("GetFollowersMyProfile", "SELECT users.username FROM followers INNER JOIN users ON followers.followed=users.id WHERE followers.follower= $1");

		pqxx::row countNoFollowersResult = worker.exec_prepared1("CountNoFollowers",userID);
		std::string number = countNoFollowersResult.at("count").c_str();
		pqxx::result readAllFollowersResult = worker.exec_prepared_n(std::stoi(number), "GetFollowersMyProfile",userID);

		for (auto currentFollower : readAllFollowersResult)
		{
			followersList.push_back(currentFollower.at("username").c_str());
		}
		worker.conn().unprepare("CountNoFollowers");
		worker.conn().unprepare("GetFollowersMyProfile");
		worker.commit();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CountNoFollowers");
		worker.conn().unprepare("GetFollowersMyProfile");
		throw std::runtime_error("Error getting followers for profile");
	}
	return followersList;
}



