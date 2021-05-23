#pragma once
#include "User.h"

class Administrator :public User {
public:
	Administrator(std::string inUserName, std::string inPassword);
	Administrator(std::ifstream& ifile);//construct user with load file
};