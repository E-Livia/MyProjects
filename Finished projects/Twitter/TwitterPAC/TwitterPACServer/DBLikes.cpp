#include "DBLikes.h"

void DBLikes::LikePost(const std::string& postID)
{
	pqxx::work worker(*DBLink::GetInstance());
	worker.conn().prepare("LikePost", "INSERT INTO likes (user_id,post_id) VALUES ($1,$2)");
	try
	{
		pqxx::result likePost = worker.exec_prepared0("LikePost", m_userID, postID);
		worker.conn().unprepare("LikePost");
		worker.commit();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("LikePost");
		throw std::runtime_error("Liking post failed");
	}
}

void DBLikes::UnlikePost(const std::string& postID)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("UnlikePost", "DELETE FROM likes WHERE post_id=$1 AND user_id=$2");
		pqxx::result unlikePost = worker.exec_prepared0("UnlikePost", postID, m_userID);
		worker.conn().unprepare("UnlikePost");
		worker.commit();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("UnlikePost");
		throw std::runtime_error("Error unliking post");
	}
}

std::string DBLikes::CalculatePostLikes(const std::string& postID)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("CountPostLikes", "SELECT COUNT(id) FROM likes WHERE post_id = $1");
		pqxx::row calculatePostLikes = worker.exec_prepared1("CountPostLikes", postID);
		worker.conn().unprepare("CountPostLikes");
		worker.commit();
		return calculatePostLikes.at("count").c_str();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CountPostLikes");
		throw std::runtime_error("Error calculating post likes");
	}
}

bool DBLikes::CheckExistingLike(const std::string& postID)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("CheckExistingLike", "SELECT COUNT(id) FROM likes WHERE post_id = $1 AND user_id = $2");
		pqxx::row checkExistingLike = worker.exec_prepared1("CheckExistingLike", postID, m_userID);
		worker.conn().unprepare("CheckExistingLike");
		if (checkExistingLike.at("count").c_str() == std::string("1"))
			return 1;
		else
			return 0;
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CheckExistingLike");
		throw std::runtime_error("Error checking existing likes");
	}
}
