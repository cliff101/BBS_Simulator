#pragma once
#include "User.h"
#include <string>
#include <iostream>

class Administrator :public User {
public:
	Administrator(std::string inUserName, std::string inPassword);
	Administrator(std::ifstream& ifile);//construct user with load file
	Administrator(const Administrator&);
};