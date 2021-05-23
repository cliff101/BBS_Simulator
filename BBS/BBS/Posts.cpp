#include "Post.h"

Post::Comment::Comment(std::string incmcontent, int increateuserID, std::vector<User*>* inusersptr) :cmcontent(incmcontent), createuserID(increateuserID), usersptr(inusersptr) {}
Post::Comment::Comment(std::ifstream& ifile, std::vector<User*>* inusersptr) : usersptr(inusersptr) {
	///*/*logic*/*/
}

Post::Post(std::string incontent, int increateuserID, std::vector<User*>* inusersptr, int inthis_postID) :content(incontent), createuserID(increateuserID), usersptr(inusersptr),this_postID(inthis_postID) {}
Post::Post(std::ifstream& ifile, std::vector<User*>* inusersptr) : usersptr(inusersptr) {
	///*/*logic*/*/
}