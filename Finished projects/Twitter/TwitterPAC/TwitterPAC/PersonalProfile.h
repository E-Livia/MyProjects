#pragma once
#include<iostream>
#include<string>
#include"FriendsNetwork.h"

class PersonalProfile
{
public:
	void GetOptionProfile(uint16_t const & option);
	void ShowInterfaceProfile();
public:
	void ShowPostHistory();
	void Exit();
public:
	const char m_bar_vertically = char(186);
	const char  m_bar_horizontal = char(205);
	const char  m_bar_corner_left_up = char(201);
	const char  m_bar_corner_right_up = char(187);
	const char  m_bar_left_breakup = char(204);
	const char  m_bar_right_breakup = char(185);
	const char  m_bar_corner_left_down = char(200);
	const char  m_bar_corner_right_fown = char(188);
};

