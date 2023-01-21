#include "DBPost.h"

void DBPost::CreatePost(const std::string& userID, const std::string& postBody, std::string retweetID)
{
	pqxx::work worker(*DBLink::GetInstance());
	{
		std::string insert("INSERT INTO posts(user_id, message) VALUES($1, $2)");
		if (retweetID != "-1")
		{
			insert = "INSERT INTO posts(user_id, message, retweet_id) VALUES($1, $2, $3)";
		}
		worker.conn().prepare("CreatePost", insert);
	}
	try
	{
		pqxx::result PostCreationResult;
		if (retweetID != "-1")
		{
			PostCreationResult = worker.exec_prepared0("CreatePost", userID, postBody, retweetID);
		}
		else
		{
			PostCreationResult = worker.exec_prepared0("CreatePost", userID, postBody);
		}
		worker.commit();
		worker.conn().unprepare("CreatePost");
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CreatePost");
		throw std::runtime_error("Post Creation failed");
	}
}

std::vector<std::string> DBPost::ReadPost(const std::string& idPost)
{
	pqxx::work worker(*DBLink::GetInstance());
	worker.conn().prepare("ReadPost", "SELECT * FROM posts WHERE id = $1");
	try
	{
		pqxx::row PostCreationResult = worker.exec_prepared1("ReadPost",idPost);
		worker.commit();
		std::string datePosted = PostCreationResult.at("date_created").c_str();
		std::string postBody = PostCreationResult.at("message").c_str();
		std::string postID = PostCreationResult.at("id").c_str();
		try
		{
			worker.conn().prepare("GetUsername", "SELECT username FROM users WHERE id= $1");
			pqxx::row UsernameSearchResult = worker.exec_prepared1("GetUsername", PostCreationResult.at("user_id").c_str());
			std::string postedBy = UsernameSearchResult.at("username").c_str();
			worker.conn().unprepare("ReadPost");
			worker.conn().unprepare("GetUsername");
			return std::vector<std::string>{datePosted, postBody, postID, postedBy};
		}
		catch (const pqxx::unexpected_rows&)
		{
			worker.conn().unprepare("ReadPost");
			worker.conn().unprepare("GetUsername");
			throw std::runtime_error("Finding user failed");
		}
	}
	catch (const pqxx::unexpected_rows&)
	{
		throw std::runtime_error("Reading Post failed");
	}
}

std::vector<std::vector<std::string>> DBPost::ReadAllPosts(const std::string& userID)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("CountPosts", "SELECT COUNT(id) FROM posts WHERE user_id = $1");
		worker.conn().prepare("ReadAllPosts", "SELECT * from posts WHERE user_id = $1 ORDER BY date_created DESC");
		pqxx::row countPostsResult = worker.exec_prepared1("CountPosts", userID);
		std::string number = countPostsResult.at("count").c_str();
		pqxx::result readAllPostsResult = worker.exec_prepared_n(std::stoi(number), "ReadAllPosts", userID);

		std::vector<std::vector<std::string>> postsVector;

		for (const auto currentPost : readAllPostsResult)
		{
			std::string postID = currentPost.at("id").c_str();
			std::string message = currentPost.at("message").c_str();
			std::string dateCreated = currentPost.at("date_created").c_str();
			postsVector.push_back(std::vector<std::string>{postID, message, dateCreated});
		}
		worker.conn().unprepare("CountPosts");
		worker.conn().unprepare("ReadAllPosts");
		worker.commit();
		return postsVector;
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CountPosts");
		worker.conn().unprepare("ReadAllPosts");
		throw std::runtime_error("Reading all of an users posts failed");
	}
}

void DBPost::UpdatePost(const std::string& idPost, const std::string& newBody)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("UpdatePostBody", "UPDATE posts SET message = $1 WHERE id=$2");
		pqxx::result UpdatePost = worker.exec_prepared0("UpdatePostBody", newBody, idPost);
		worker.conn().unprepare("UpdatePostBody");
		worker.commit();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("UpdatePostBody");
		throw std::runtime_error("Error finidng post");
	}
}

void DBPost::DeletePost(const std::string& idPost)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("DeletePost", "DELETE FROM POSTS where id=$1");
		pqxx::result UpdatePost = worker.exec_prepared0("DeletePost", idPost);
		worker.conn().unprepare("DeletePost");
		worker.commit();
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("DeletePost");
		throw std::runtime_error("Error finidng post");
	}
}

std::vector<std::string> DBPost::GetInitialPost(const std::string& idPost)
{
	pqxx::work worker(*DBLink::GetInstance());
	worker.conn().prepare("GetRetweetID", "SELECT retweet_id from posts WHERE id=$1;");
	worker.conn().prepare("GetInitialPost", "SELECT p2.* FROM posts P1 INNER JOIN posts P2 ON $1 = p2.id FETCH FIRST ROW ONLY; ");
	try
	{
		pqxx::row retweetID = worker.exec_prepared1("GetRetweetID", idPost);
		std::string retweetIDstr = retweetID.at("retweet_id").c_str();
		pqxx::row getInitialPostResult;
		try {
			getInitialPostResult = worker.exec_prepared1("GetInitialPost", std::stoi(retweetIDstr));
		}
		catch (const std::exception& e)
		{
			worker.conn().unprepare("GetRetweetID");
			worker.conn().unprepare("GetInitialPost");
			worker.commit();
			throw std::runtime_error("No retweet found for this post");
		}
		std::string datePosted = getInitialPostResult.at("date_created").c_str();
		std::string postBody = getInitialPostResult.at("message").c_str();
		std::string postID = getInitialPostResult.at("id").c_str();
		try
		{
			worker.conn().prepare("GetUsername", "SELECT username FROM users WHERE id= $1");
			pqxx::row UsernameSearchResult = worker.exec_prepared1("GetUsername", getInitialPostResult.at("user_id").c_str());
			std::string postedBy = UsernameSearchResult.at("username").c_str();
			worker.conn().unprepare("GetRetweetID");
			worker.conn().unprepare("GetInitialPost");
			worker.conn().unprepare("GetUsername");
			worker.commit();
			return std::vector<std::string>{datePosted, postBody, postID, postedBy};
		}
		catch (const pqxx::unexpected_rows&)
		{
			worker.conn().unprepare("GetRetweetID");
			worker.conn().unprepare("GetInitialPost");
			worker.conn().unprepare("GetUsername");
			worker.commit();
			throw std::runtime_error("Finding user failed");
		}
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error(e.what());
	}
}

std::string DBPost::CountRetweets(std::string postID)
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("CountRetweets", "SELECT COUNT(id) FROM posts where retweet_id=$1");
		pqxx::row countRetweetResult = worker.exec_prepared1("CountRetweets", postID);
		worker.conn().unprepare("CountRetweets");
		worker.commit();
		std::string retweetCountResult = countRetweetResult.at("count").c_str();
		return retweetCountResult;
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CountRetweets");
		throw std::runtime_error("Error counting retweets of a post");
	}
}

std::vector<std::string>*& DBPost::GetPostData()
{
	std::vector<std::string>* postData = new std::vector<std::string>();
	postData->reserve(3);
	return postData;
}