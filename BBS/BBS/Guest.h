#pragma once
#include "User.h"

class Guest :public User {
public:
	Guest(std::string inUserName,std::string inPassword);
};