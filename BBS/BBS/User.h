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
	void NewpushpostsID(int postID);    ///*/*spec沒有，不一定要*/*/
	void DeletepushpostsID(int postID); ///*/*spec沒有，不一定要*/*/
	void NewshpostsID(int postID);      ///*/*spec沒有，不一定要*/*/
	void DeleteshpostsID(int postID);   ///*/*spec沒有，不一定要*/*/

	void SetPermission_level();
	void GetPermission_level();
private:
	std::vector<int> postsID;	// 紀錄建立過的post
	int Permission_level;	// 權限等級  0 = admin  1 = normal user
	std::string UserName;

	std::vector<int> pushpostsID;	// 紀錄推過的post   /*/*spec沒有，不一定要*/*/
	std::vector<int> shpostsID;	// 紀錄虛過的post       /*/*spec沒有，不一定要*/*/
};