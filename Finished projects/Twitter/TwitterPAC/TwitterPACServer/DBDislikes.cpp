#include "DBDislikes.h"

void DBDislikes::DislikePost(const std::string& postID)
{
	pqxx::work worker(*DBLink::GetInstance());
	worker.conn().prepare("DislikePost", "INSERT INTO dislikes (user_id,post_id) VALUES ($1,$2)");
	try
	{
		pqxx::result dislikePost = worker.exec_prepared0("DislikePost", m_userID, postID);
		worker.conn().unprepare("DislikePost");
		worker.commit();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("DislikePost");
		throw std::runtime_error("Liking post failed");
	}
}

void DBDislikes::UndislikePost(const std::string& postID)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("UndislikePost", "DELETE FROM dislikes WHERE post_id=$1 AND user_id=$2");
		pqxx::result undislikePost = worker.exec_prepared0("UndislikePost", postID, m_userID);
		worker.conn().unprepare("UndislikePost");
		worker.commit();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("UndislikePost");
		throw std::runtime_error("Error unliking post");
	}
}

std::string DBDislikes::CalculatePostDislikes(const std::string& postID)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("CountPostDislikes", "SELECT COUNT(id) FROM dislikes WHERE post_id = $1");
		pqxx::row calculatePostDislikes = worker.exec_prepared1("CountPostDislikes", postID);
		worker.conn().unprepare("CountPostDislikes");
		worker.commit();
		return calculatePostDislikes.at("count").c_str();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CountPostDislikes");
		throw std::runtime_error("Error calculating post dislikes");
	}
}

bool DBDislikes::CheckExistingDislike(const std::string& postID)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("CheckExistingDislike", "SELECT COUNT(id) FROM dislikes WHERE post_id = $1 AND user_id = $2");
		pqxx::row checkExistingDislike = worker.exec_prepared1("CheckExistingDislike", postID, m_userID);
		worker.commit();
		worker.conn().unprepare("CheckExistingDislike");
		if (checkExistingDislike.at("count").c_str() == std::string("1"))
			return 1;
		else
			return 0;
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CheckExistingDislike");
		throw std::runtime_error("Error checking existing dislikes");
	}
}
