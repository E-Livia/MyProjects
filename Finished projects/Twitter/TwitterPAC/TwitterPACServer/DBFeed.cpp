#include "DBFeed.h"
#include "DBLink.h"
#include "DBUser.h"

int DBFeed::m_index = 0;
std::unique_ptr<std::vector<std::vector<std::string>>> 
DBFeed::m_postari = std::make_unique<std::vector<std::vector<std::string>>>();

void DBFeed::CalculatePosts()
{
	DBUser* user = DBUser::getInstance();
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("CountPosts",
			"SELECT COUNT(posts.id) FROM followers RIGHT JOIN posts ON followers.followed = posts.user_id WHERE followers.follower = $1"
		);
		pqxx::row postsCount = worker.exec_prepared1("CountPosts", user->GetUserID());
		int remainedPosts = std::stoi(postsCount.at("count").c_str()) - m_index;
		if (remainedPosts > 0)
		{
			worker.conn().prepare("ReadAllPostsFeed",
				"SELECT posts.id,message,date_created,user_id FROM followers RIGHT JOIN posts ON followers.followed = posts.user_id WHERE followers.follower = $1 ORDER BY date_created DESC LIMIT 5 OFFSET "
				+ std::to_string(m_index)
			);
			worker.conn().prepare("GetUsernameFromID", "SELECT username FROM users WHERE id = $1");
			pqxx::result readAllPostsResult = worker.exec_prepared_n(remainedPosts >= 5 ? 5 : remainedPosts, "ReadAllPostsFeed", user->GetUserID());
			for (const auto& currentPost : readAllPostsResult)
			{
				pqxx::row usernameFromID = worker.exec_prepared1("GetUsernameFromID", currentPost.at("user_id").c_str());
				std::string postID = currentPost.at("id").c_str();
				std::string message = currentPost.at("message").c_str();
				std::string dateCreated = currentPost.at("date_created").c_str();
				std::string postedBy = usernameFromID.at("username").c_str();
				m_postari->push_back(std::vector<std::string>{postID, message, dateCreated, postedBy});
			}
			worker.conn().unprepare("ReadAllPostsFeed");
			worker.conn().unprepare("GetUsernameFromID");
			worker.conn().unprepare("CountPosts");
			worker.commit();
			m_index += 5;
			return;
		}
		worker.conn().unprepare("CountPosts");
		worker.commit();
		m_postari->clear();
		m_postari->push_back(std::vector<std::string>{"-1", "End of feed - follow more users for more posts", "-1", "-1"});
	}
	catch (const std::exception& ex)
	{
		worker.conn().unprepare("CountPosts");
		worker.commit();
		throw std::runtime_error(ex.what());
	}
}

std::vector<std::string> DBFeed::GetPost()
{
	if (m_postari.get() == nullptr) 
	{
		m_postari = std::make_unique<std::vector<std::vector<std::string>>>();
	}
	if (m_postari->empty())
	{
		CalculatePosts();
	}
	std::vector<std::string> deReturnat = m_postari->at(0);
	m_postari->erase(DBFeed::m_postari->begin());
	return deReturnat;
}

void DBFeed::ClearFeed()
{
	m_index = 0;
	m_postari.reset();
}

