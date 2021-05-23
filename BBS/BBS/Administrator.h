#pragma once
#include "User.h"

class Administrator :public User {
public:
	Administrator(std::string inUserName, std::string inPassword);
};