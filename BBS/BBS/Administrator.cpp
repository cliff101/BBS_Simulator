#include "Administrator.h"

Administrator::Administrator(std::string inUserName, std::string inPassword) :User(inUserName, inPassword,0) {}
Administrator::Administrator(std::ifstream& ifile):User(ifile){}

Administrator::Administrator(const Administrator& in):User(in){}
