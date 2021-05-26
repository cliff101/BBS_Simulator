#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <map>

class User {
public:
	User(std::string inUserName, std::string inPassword, int inprl);//create user with UserName and Permission_level
	User(std::ifstream& ifile);//construct user with load file
	User();
	User(const User& in);

	std::vector<int> GetpostsID();
	//std::vector<int> GetpushpostsID();  ///*/*spec�S���A���@�w�n*/*/
	//std::vector<int> GetshpostsID();    ///*/*spec�S���A���@�w�n*/*/
	void NewpostID(int postID);
	void DeletepostID(int postID);
	//void NewpushpostsID(int postID);    ///*/*spec�S���A���@�w�n*/*/
	//void DeletepushpostsID(int postID); ///*/*spec�S���A���@�w�n*/*/
	//void NewshpostsID(int postID);      ///*/*spec�S���A���@�w�n*/*/
	//void DeleteshpostsID(int postID);   ///*/*spec�S���A���@�w�n*/*/

	void ChangeUserName(std::string inUserName);
	void ChangePassword(std::string inPassword);
	int GetPermission_level();
	std::string GetUserName();
	bool CheckUserName(std::string inUserName);
	bool CheckPassword(std::string inPassword);

	void SaveUserToFile(std::ofstream& ofile);
	void LoadUserFromFile(std::ifstream& ifile);
private:
	std::vector<int> postsID;	// �����إ߹L��post
	int Permission_level;	// �v������  0 = admin  1 = normal user  3 = guests
	std::string UserName;
	std::string Password;

	//std::vector<int> pushpostsID;	// �������L��post   /*/*spec�S���A���@�w�n*/*/
	//std::vector<int> shpostsID;	// ������L��post       /*/*spec�S���A���@�w�n*/*/
};