#pragma once
#include<iostream>
#include<string>
#include<map>
#include "PersonalProfile.h"
#include"Feed.h"
#include"UserSearch.h"
#include "InvertedIndex.h"

class UserMenu
{
public:
    void CreateMenu();
    void GetMenuOption();
    void MenuRead(char*);

    void SetOptionMenu(const uint16_t&);
    const uint16_t GetOptionMenu()const;
    void Exit();

public:
    void GoToPost();
    void GoToPersonalProfile();
    void GoToFeed();
    void GoToKeywordSearch();
    void GoToUserSearch();
    void GoToFollow();

public:

    char m_bar_vertically = char(186);
    char m_bar_horizontal = char(205);
    char m_bar_corner_left_up = char(201);
    char m_bar_corner_right_up = char(187);
    char m_bar_left_breakup = char(204);
    char m_bar_right_breakup = char(185);
    char m_bar_corner_left_down = char(200);
    char m_bar_corner_right_fown = char(188);

private:
    uint16_t m_option_user_menu;
};
