#pragma once
#include <vector>
#include <string>

class User {
public:
	User();//create normal user
	User(int inprl);//create user with Permission_level
	std::vector<int> GetpostsID();
	std::vector<int> GetpushpostsID();
	std::vector<int> GetshpostsID();
	void NewpostID(int postID);
	void DeletepostID(int postID);
	void NewpushpostsID(int postID);    ///*/*spec�S���A���@�w�n*/*/
	void DeletepushpostsID(int postID); ///*/*spec�S���A���@�w�n*/*/
	void NewshpostsID(int postID);      ///*/*spec�S���A���@�w�n*/*/
	void DeleteshpostsID(int postID);   ///*/*spec�S���A���@�w�n*/*/

	void SetPermission_level();
	void GetPermission_level();
private:
	std::vector<int> postsID;	// �����إ߹L��post
	int Permission_level;	// �v������  0 = admin  1 = normal user
	std::string UserName;

	std::vector<int> pushpostsID;	// �������L��post   /*/*spec�S���A���@�w�n*/*/
	std::vector<int> shpostsID;	// ������L��post       /*/*spec�S���A���@�w�n*/*/
};