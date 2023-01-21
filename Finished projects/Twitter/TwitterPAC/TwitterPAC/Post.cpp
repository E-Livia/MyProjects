#include "Post.h"
#include "ClientSocket.h"
#include "../../cereal/archives/json.hpp"

ClientSocket* Csocket = ClientSocket::GetInstance();

void Post::CreatePost()
{
	const size_t MAXIMUM_CHARS = 140;
	int exit;
	std::string option;
	std::cout << "   If you want to exit press 0 else 1 to continue " << std::endl;
	std::cin >> exit;
	std::cout << std::endl;
	if (exit == 0)
	{

	}
	else {
		std::cout << "Start writing your post" << std::endl;
		std::cin.get();
		for (;;)
		{
			std::getline(std::cin, m_text);
			if (m_text.size() <= MAXIMUM_CHARS)
			{
			}
			else
			{
				m_text.erase(MAXIMUM_CHARS);
				std::cout << m_text << std::endl;
				std::cout << "You must only put 140 characters\n";
			}
			std::cout << "Is the post ready to be sent? type-> yes OR no" << std::endl;;
			std::cin >> option;

			if (option == "yes")
			{
				std::cout << std::endl;
				std::cout << "Post registered!";
				Csocket->SendData("4");
				std::optional<std::string> result = Csocket->RecieveData();
				std::string user, user_ID;
				std::stringstream is(result.value());
				{
					cereal::JSONInputArchive archive_in(is);
					archive_in(user, user_ID);
				}
				std::stringstream os;
				{
					cereal::JSONOutputArchive archive_out(os);
					archive_out(cereal::make_nvp("userID", user_ID), cereal::make_nvp("postBody", m_text));
				}
				Csocket->SendData("5" + os.str());
				break;
			}
			else if (option == "no") {
				std::cout << std::endl;
				std::cout << "Post not registered!";
				break;
			}
		}

	}
	std::cout << std::endl;
}



void Post::SeeAPost()
{
	std::string post_id = "16";
	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(CEREAL_NVP(post_id));
	}
	Csocket->SendData("6" + os.str());
	std::optional<std::string> currentSession = Csocket->RecieveData();

	//deserializare post
	std::string postBody, postedBy, datePosted;
	std::stringstream is(currentSession.value());
	{
		cereal::JSONInputArchive archive_in(is);
		archive_in(datePosted, postBody, post_id, postedBy);
	}
	std::cout << postedBy << std::endl << datePosted.substr(0, 19) << std::endl << postBody << std::endl;
}