#pragma once
#include "User.h"

class Member :public User {
public:
	Member(std::string inUserName,std::string inPassword);
};