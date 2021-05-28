#include "User.h"
#include "FileIOTools.h"

User::User(std::string inUserName, std::string inPassword, int inprl) :UserName(inUserName), Permission_level(inprl), Password(inPassword),postsID(0) {}
User::User(std::ifstream& ifile) : UserName(""), Permission_level(-1), Password(""),postsID(0) {
	LoadUserFromFile(ifile);
}
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

void User::Addmsg(std::string usernamekey, std::string msg){
	if (usernamekey == "guest") {
		return;
	}
	auto search = usermessage.find(usernamekey);
	if (search == usermessage.end()) {
		usermessage[usernamekey] = std::vector<std::string>(0);
	}
	usermessage[usernamekey].push_back(msg);
}
void User::Deletemsg(std::string usernamekey){
	auto search = usermessage.find(usernamekey);
	if (search != usermessage.end()) {
		usermessage.erase(usernamekey);
	}
}
std::map<std::string, std::vector<std::string>> User::Getmsg(){
	return usermessage;
}

void User::SaveUserToFile(std::ofstream& ofile) {
	SaveVectorToFile(postsID, ofile);
	SaveNormDataToFile(Permission_level, ofile);
	SaveStrToFile(UserName, ofile);
	SaveStrToFile(Password, ofile);
	int messagelength = usermessage.size();
	SaveNormDataToFile(messagelength, ofile);
	for (std::map<std::string, std::vector<std::string>>::iterator it = usermessage.begin(); it != usermessage.end(); ++it) {
		SaveStrToFile(it->first,ofile);
		int submessagelength = it->second.size();
		SaveNormDataToFile(submessagelength, ofile);
		for (int i = 0; i < submessagelength; i++) {
			SaveStrToFile(it->second[i], ofile);
		}
	}
}
void User::LoadUserFromFile(std::ifstream& ifile) {
	LoadVectorFromFile(postsID, ifile);
	LoadNormDataFromFile(Permission_level, ifile);
	LoadStrFromFile(UserName, ifile);
	LoadStrFromFile(Password, ifile);
	int messagelength = 0;
	LoadNormDataFromFile(messagelength, ifile);
	for (int i = 0; i < messagelength;i++) {
		std::string thiskey = "";
		LoadStrFromFile(thiskey, ifile);
		usermessage[thiskey] = std::vector<std::string>(0);
		int submessagelength = 0;
		LoadNormDataFromFile(submessagelength, ifile);
		for (int i = 0; i < submessagelength; i++) {
			std::string thissubmsg = "";
			LoadStrFromFile(thissubmsg, ifile);
			usermessage[thiskey].push_back(thissubmsg);
		}
	}
}