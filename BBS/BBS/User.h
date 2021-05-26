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
	//std::vector<int> GetpushpostsID();  ///*/*spec沒有，不一定要*/*/
	//std::vector<int> GetshpostsID();    ///*/*spec沒有，不一定要*/*/
	void NewpostID(int postID);
	void DeletepostID(int postID);
	//void NewpushpostsID(int postID);    ///*/*spec沒有，不一定要*/*/
	//void DeletepushpostsID(int postID); ///*/*spec沒有，不一定要*/*/
	//void NewshpostsID(int postID);      ///*/*spec沒有，不一定要*/*/
	//void DeleteshpostsID(int postID);   ///*/*spec沒有，不一定要*/*/

	void ChangeUserName(std::string inUserName);
	void ChangePassword(std::string inPassword);
	int GetPermission_level();
	std::string GetUserName();
	bool CheckUserName(std::string inUserName);
	bool CheckPassword(std::string inPassword);

	void SaveUserToFile(std::ofstream& ofile);
	void LoadUserFromFile(std::ifstream& ifile);
private:
	std::vector<int> postsID;	// 紀錄建立過的post
	int Permission_level;	// 權限等級  0 = admin  1 = normal user  3 = guests
	std::string UserName;
	std::string Password;

	//std::vector<int> pushpostsID;	// 紀錄推過的post   /*/*spec沒有，不一定要*/*/
	//std::vector<int> shpostsID;	// 紀錄虛過的post       /*/*spec沒有，不一定要*/*/
};