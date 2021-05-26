#pragma once
#include "User.h"

class Member :public User {
public:
	Member(std::string inUserName,std::string inPassword);
	Member(std::ifstream& ifile);//construct user with load file
	Member(const Member&);
};