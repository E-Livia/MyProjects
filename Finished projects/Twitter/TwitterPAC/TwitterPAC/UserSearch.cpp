#include "UserSearch.h"
#include "ClientSocket.h"
#include "../../cereal/archives/json.hpp"

ClientSocket* CsocketUserSearch = ClientSocket::GetInstance();

void UserSearch::UserSearching()
{
    std::string userToSearch, userID, username;
    std::cout << "Enter the name to be searched: ";
    std::cin >> userToSearch;
    std::cout << std::endl;

    std::stringstream os;
    {
        cereal::JSONOutputArchive archive_out(os);
        archive_out(cereal::make_nvp("userID", userToSearch));
    }

    CsocketUserSearch->SendData("32"+os.str());
    std::optional<std::string> currentSession = CsocketUserSearch->RecieveData();

    std::stringstream is(currentSession.value());
    {
        cereal::JSONInputArchive archive_in(is);
        std::string vectorSize;
        archive_in(vectorSize);
        if(vectorSize != "0")
        {
            int maxsize=std::stoi(vectorSize);
            for (int i = 0; i < maxsize; i++) {
                archive_in(userID, username);
                std::cout << username << std::endl;
            }
            return;
        }
        std::cout << "Utilizator negasit" << std::endl;
    }
}
