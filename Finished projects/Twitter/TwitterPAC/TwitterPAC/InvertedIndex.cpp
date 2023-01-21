#include "InvertedIndex.h"
#include "ClientSocket.h"
#include <iomanip>
#include "../../cereal/archives/json.hpp"

ClientSocket* CsocketKeySearch = ClientSocket::GetInstance();


void InvertedIndex::KeySearch()
{
	std::string keySearch, posts;
	std::cout << "Key to be found: ";
	std::cin >> keySearch;
	std::cout << std::endl;

	std::stringstream os;
	{
		cereal::JSONOutputArchive archive_out(os);
		archive_out(cereal::make_nvp("inputSentence", keySearch));
	}

	CsocketKeySearch->SendData("29"+os.str());
	std::optional<std::string> currentSession2 = CsocketKeySearch->RecieveData();

	std::cout << std::left << std::setw(20) << "Username";
	std::cout<< std::setw(80) << "PostBody" << std::endl;
	std::stringstream is(currentSession2.value());
	{
		std::string postBody, postedBy, datePosted, postID, vectorSize;
		cereal::JSONInputArchive archive_in(is);
		archive_in(vectorSize);
		if (vectorSize != "0") {
			int vectorSizeInt = std::stoi(vectorSize);
			for (int i = 0; i < vectorSizeInt; i++) {
				archive_in(datePosted, postBody, postID, postedBy);
				std::cout << std::left << std::setw(20) << postedBy;
				std::cout << std::setw(80) << postBody << std::endl;
			}
			return;
		}
		std::cout << "Key word not found in DB" << std::endl;
	}
}

