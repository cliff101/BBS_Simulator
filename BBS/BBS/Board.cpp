#include "Board.h"

Board::Board(std::string inTopic,int increateuserID, std::vector<User*>* inusersptr):Topic(inTopic),createuserID(increateuserID),usersptr(inusersptr){}
Board::Board(std::ifstream& ifile, std::vector<User*>* inusersptr):usersptr(inusersptr) {
	///*/*logic*/*/
}