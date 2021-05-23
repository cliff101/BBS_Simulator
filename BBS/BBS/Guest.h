#pragma once
#include "User.h"

class Guest :public User {
public:
	Guest();
	Guest(std::ifstream& ifile);//construct user with load file
};