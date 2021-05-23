#include "Guest.h"

Guest::Guest() :User("guest", "", 2) {}
Guest::Guest(std::ifstream& ifile) : User(ifile) {}