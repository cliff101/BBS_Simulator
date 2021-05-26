#include "User.h"
#include "FileIOTools.h"

User::User(std::string inUserName, std::string inPassword, int inprl) :UserName(inUserName), Permission_level(inprl), Password(inPassword),postsID(0) {}
User::User(std::ifstream& ifile) : UserName(""), Permission_level(-1), Password(""),postsID(0) {
	LoadUserFromFile(ifile);
}
User::User() {};
User::User(const User& in)
{
	postsID = in.postsID;
	UserName = in.UserName;
	Password = in.Password;
	Permission_level = in.Permission_level;
}

void User::ChangeUserName(std::string inUserName) {
	UserName = inUserName;
}
void User::ChangePassword(std::string inPassword) {
	Password = inPassword;
}
int User::GetPermission_level() {
	return Permission_level;
}
std::string User::GetUserName() {
	return UserName;
}
bool User::CheckUserName(std::string inUserName) {
	return UserName == inUserName;
}
bool User::CheckPassword(std::string inPassword) {
	return Password == inPassword;
}

void User::NewpostID(int postID) {
	postsID.push_back(postID);
}
void User::DeletepostID(int postID) {
	auto it = std::find(postsID.begin(), postsID.end(), postID);
	if (it != postsID.end()) {
		postsID.erase(it);
	}
}
std::vector<int> User::GetpostsID() {
	return postsID;
}

void User::SaveUserToFile(std::ofstream& ofile) {
	SaveVectorToFile(postsID, ofile);
	SaveNormDataToFile(Permission_level, ofile);
	SaveStrToFile(UserName, ofile);
	SaveStrToFile(Password, ofile);
}
void User::LoadUserFromFile(std::ifstream& ifile) {
	LoadVectorFromFile(postsID, ifile);
	LoadNormDataFromFile(Permission_level, ifile);
	LoadStrFromFile(UserName, ifile);
	LoadStrFromFile(Password, ifile);
}