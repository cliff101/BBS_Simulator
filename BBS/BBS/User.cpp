#include "User.h"

User::User(std::string inUserName, std::string inPassword,int inprl):UserName(inUserName),Permission_level(inprl),Password(inPassword){}
User::User(std::ifstream& ifile){
	LoadSUserFromFile(ifile);
}

void User::ChangeUserName(std::string inUserName){
	UserName = inUserName;
}
void User::ChangePassword(std::string inPassword){
	Password = inPassword;
}
int User::GetPermission_level(){
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

void User::NewpostID(int postID){
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

void User::SaveUserToFile(std::ofstream& ofile){
	long long posts = sizeof(postsID), postslen = postsID.size();
	ofile.write((char*)&posts, sizeof(posts));
	ofile.write((char*)&postslen, sizeof(postslen));
	if (postslen > 0) {
		ofile.write((char*)postsID.data(), sizeof(postsID));
	}
	ofile.write((char*)&Permission_level, sizeof(Permission_level));
	std::string::size_type susn = sizeof(UserName);
	std::string::size_type spw = sizeof(Password);
	long long usnlen = UserName.size(), pwlen = Password.size();
	ofile.write((char*)&susn, sizeof(susn));
	ofile.write((char*)&usnlen, sizeof(usnlen));
	ofile.write((char*)UserName.data(), susn);
	ofile.write((char*)&spw, sizeof(spw));
	ofile.write((char*)&pwlen, sizeof(pwlen));
	ofile.write((char*)Password.data(), spw);
}
void User::LoadSUserFromFile(std::ifstream& ifile) {
	long long posts = 0,postslen = 0;
	ifile.read((char*)&posts, sizeof(posts));
	ifile.read((char*)&postslen, sizeof(postslen));
	if (postslen > 0) {
		postsID.resize(postslen);
		ifile.read((char*)postsID.data(), posts);
	}
	ifile.read((char*)&Permission_level, sizeof(Permission_level));
	std::string::size_type susn = 0;
	std::string::size_type spw = 0;
	long long usnlen = 0, pwlen = 0;
	ifile.read((char*)&susn, sizeof(susn));
	ifile.read((char*)&usnlen, sizeof(usnlen));
	UserName.resize(usnlen);
	ifile.read((char*)UserName.data(), susn);
	ifile.read((char*)&spw, sizeof(spw));
	ifile.read((char*)&pwlen, sizeof(pwlen));
	Password.resize(pwlen);
	ifile.read((char*)Password.data(), spw);
}