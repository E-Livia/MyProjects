#include "DBInvertedIndex.h"

void DBInvertedIndex::CreateDictionary()
{
	pqxx::work worker(*DBLink::GetInstance());
	try
	{
		worker.conn().prepare("CountPostsDictionary", "SELECT COUNT(id) FROM posts");
		worker.conn().prepare("ReadAllPostsDictionary", "SELECT id,message from posts");
		pqxx::row countPostsResult = worker.exec_prepared1("CountPostsDictionary");
		std::string number = countPostsResult.at("count").c_str();
		pqxx::result readAllPostsResult = worker.exec_prepared_n(std::stoi(number), "ReadAllPostsDictionary");

		for (auto currentPost : readAllPostsResult)
		{
			std::string postID = currentPost.at("id").c_str();
			std::string message = currentPost.at("message").c_str();
			std::for_each(message.begin(), message.end(), [](char& c) {
				c = ::tolower(c);
				});
			std::istringstream inputStringStream{ message };
			std::string dictionaryUtilitary{};

			while (inputStringStream >> dictionaryUtilitary)
			{
				if (dictionary.count(dictionaryUtilitary) == 0)
					dictionary.emplace(dictionaryUtilitary, std::vector<std::string>{postID});
				else
					dictionary.at(dictionaryUtilitary).push_back(postID);
			}
		}
		worker.conn().unprepare("CountPostsDictionary");
		worker.conn().unprepare("ReadAllPostsDictionary");
	}
	catch (const pqxx::unexpected_rows&)
	{
		worker.conn().unprepare("CountPostsDictionary");
		worker.conn().unprepare("ReadAllPostsDictionary");
		throw std::runtime_error("Reading all of an users posts for dictionary failed");
	}
}

std::vector<std::vector<std::string>> DBInvertedIndex::CheckSentence(std::string givenSentence)
{
	std::for_each(givenSentence.begin(), givenSentence.end(), [](char& c) {
		c = ::tolower(c);
		});

	std::istringstream inputStringStream{ givenSentence };
	std::string auxiliaryMapIterator;
	std::set<std::string> postsToBeShown;

	while (inputStringStream >> auxiliaryMapIterator)
	{
		if (dictionary.find(auxiliaryMapIterator) != dictionary.cend())
			std::copy(dictionary.at(auxiliaryMapIterator).begin(), dictionary.at(auxiliaryMapIterator).end(),
				std::inserter(postsToBeShown,postsToBeShown.end()));
	}
	return ShowMatchedPosts(postsToBeShown);
}

std::vector<std::vector<std::string>> DBInvertedIndex::ShowMatchedPosts(std::set<std::string> postsToBeShown)
{
	std::vector<std::vector<std::string>> matchedResult;
	for (auto itSet : postsToBeShown)
	{
		DBPost post;
		matchedResult.push_back(post.ReadPost(itSet));
	}
	return matchedResult;
}
