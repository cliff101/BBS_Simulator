#include "Member.h"

Member::Member(std::string inUserName, std::string inPassword) :User(inUserName, inPassword,1) {}
Member::Member(std::ifstream& ifile) : User(ifile) {}

Member::Member(const Member& in):User(in){}
