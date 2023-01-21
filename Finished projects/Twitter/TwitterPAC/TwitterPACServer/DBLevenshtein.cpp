#include "DBLevenshtein.h"

int min(int x, int y, int z) { return std::min(std::min(x, y), z); }

int DBLevenshtein::LevenshteinDistance(std::string firstWord, std::string secondWord)
{
    const int  m = firstWord.length();
    const int n = secondWord.length();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; i++) 
    {
        for (int j = 0; j <= n; j++) 
        {
            if (i == 0)
                dp[i][j] = j;
            else
                if (j == 0)
                    dp[i][j] = i;
                else
                    if (firstWord[i - 1] == secondWord[j - 1])
                        dp[i][j] = dp[i - 1][j - 1];
                    else
                        dp[i][j] = 1 + min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]);
        }
    }
    return dp[m][n];
}

std::vector<std::vector<std::string>> DBLevenshtein::GenerateResults(std::string inputWord)
{
    DBUser* user = DBUser::getInstance();
    int counterUser = 0;
    try
    {
        std::vector<std::vector<std::string>> AllUsersResultList = user->ReadAllUsers();
        AllUsersResultList.erase(
            std::remove_if(
                AllUsersResultList.begin(),
                AllUsersResultList.end(),
                [user](std::vector<std::string> element) -> bool {
                    if(element[1]==user->GetUser())
                        return true;
                }
            ),
            AllUsersResultList.end()
                    );
        std::vector<std::pair<int, int>> levvenshteinResults;
        for (const auto& itUser : AllUsersResultList)
        {
            std::string username = itUser[1];
            levvenshteinResults.push_back(std::make_pair(counterUser, LevenshteinDistance(username, inputWord)));
            counterUser++;
        }
        std::sort(levvenshteinResults.begin(), levvenshteinResults.end(), [](std::pair<int, int> firstValue, std::pair<int, int> secondValue) {
            return firstValue.second < secondValue.second;
            });

        std::vector<std::vector<std::string>> SortedUsernameResults;
        for (auto itOrder : levvenshteinResults)
            SortedUsernameResults.push_back(AllUsersResultList[itOrder.first]);
        return SortedUsernameResults;
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error("Reading all users failed");
    }
}
