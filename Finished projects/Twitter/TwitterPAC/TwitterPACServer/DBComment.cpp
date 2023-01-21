#include "DBComment.h"

void DBComment::CreateComment(const std::string& userID, const std::string& postID, const std::string& commentBody)
{
	pqxx::work worker(*DBLink::GetInstance());
	worker.conn().prepare("CreateComment", "INSERT INTO comments (user_id,post_id,comment_body) VALUES ($1,$2,$3)");
	try
	{
		pqxx::result createCommentResult = worker.exec_prepared0("CreateComment", userID, postID,commentBody);
		worker.commit();
		std::cout << "Created comment successfully" << std::endl;
		worker.conn().unprepare("CreateComment");
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CreateComment");
		throw std::runtime_error("Comment Creation failed");
	}
}

std::vector<std::vector<std::string>> DBComment::ReadAllComments(const std::string& postID)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("CountComments", "SELECT COUNT(comment_body) FROM comments WHERE post_id = $1");
		worker.conn().prepare("ReadAllComments", "SELECT * from comments WHERE post_id = $1");
		pqxx::row countCommentsResult = worker.exec_prepared1("CountComments", postID);
		std::string number = countCommentsResult.at("count").c_str();
		pqxx::result readAllCommentsResult = worker.exec_prepared_n(std::stoi(number), "ReadAllComments", postID);
		
		std::vector<std::vector<std::string>> commentsVector;
		for (const auto currentComment : readAllCommentsResult)
		{
			std::string commentID = currentComment.at("id").c_str();
			std::string userID = currentComment.at("user_id").c_str();
			std::string commentBody = currentComment.at("comment_body").c_str();
			commentsVector.push_back(std::vector<std::string>{commentID, userID, commentBody});
		}
		worker.commit();
		worker.conn().unprepare("CountComments");
		worker.conn().unprepare("ReadAllComments");
		return commentsVector;
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CountComments");
		worker.conn().unprepare("ReadAllComments");
		throw std::runtime_error("Reading all comments failed");
	}
}

std::vector<std::string> DBComment::ReadComment(const std::string& commentID)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("ReadComment", "SELECT * FROM comments where id=$1");
		pqxx::row readCommentResult = worker.exec_prepared1("ReadComment", commentID);
		worker.commit();
		std::string commentID = readCommentResult.at("id").c_str();
		std::string userID = m_userID;
		std::string commentBody = readCommentResult.at("comment_body").c_str();

		worker.conn().unprepare("ReadComment");
		return std::vector<std::string>{commentID, userID, commentBody};
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("ReadComment");
		throw std::runtime_error("Error reading comment");
	}
}

void DBComment::UpdateComment(const std::string& commentID, const std::string& newCommentBody)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("UpdateCommentBody", "UPDATE comments SET comment_body = $1 WHERE id=$2");
		pqxx::result updatePostResult = worker.exec_prepared0("UpdateCommentBody", newCommentBody, commentID);
		worker.conn().unprepare("UpdateCommentBody");
		worker.commit();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("UpdateCommentBody");
		throw std::runtime_error("Error updating comment");
	}
}

void DBComment::DeleteComment(const std::string& commentID)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("DeleteComment", "DELETE FROM comments where id=$1");
		pqxx::result deletePostResult = worker.exec_prepared0("DeleteComment", commentID);
		worker.conn().unprepare("DeleteComment");
		worker.commit();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("DeleteComment");
		throw std::runtime_error("Error deleting comment");
	}
}

std::string DBComment::CountComments(const std::string& postID)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("CountComment", "SELECT COUNT(id) FROM comments where post_id=$1");
		pqxx::row countCommentResult = worker.exec_prepared1("CountComment", postID);
		worker.conn().unprepare("CountComment");
		worker.commit();
		std::string commentCountResult = countCommentResult.at("count").c_str();
		return commentCountResult;
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CountComment");
		throw std::runtime_error("Error counting comments of a post");
	}
}
