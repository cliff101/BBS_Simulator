#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "User.h"


class Post {
public:
	class Comment {
	public:
		Comment(std::string incmcontent, int increateuserID, std::vector<User*>* inusersptr);//construct comment with content, createuserID
		Comment(std::ifstream& ifile, std::vector<User*>* inusersptr);//construct comment with load file
		std::string cmcontent;

		int createuserID;//紀錄本Comment由哪位user creat的                在有使用者要操作時才assign
		std::vector<User*>* usersptr;

		void SaveCommentToFile(std::ofstream& ofile);
		void LoadCommentFromFile(std::ifstream& ifile);
	};
	Post(std::string inTopic, std::string incontent, int increateuserID, int inthis_postID, std::vector<User*>* inusersptr);//construct post with content, createuserID
	Post(std::ifstream& ifile, std::vector<User*>* inusersptr);//construct post with load file
	~Post();

	long long this_postID;
	int createuserID;//紀錄本post由哪位user creat的
	std::vector<int> pushuserID;//紀錄該推該post的userID
	std::vector<int> shuserID;//紀錄該虛該post的userID
	std::string Topic = "";
	std::string Pocontent = "";
	std::vector<Comment*> comments;

	void NewComment();//func for all none guest to create comment
	void DeleteComment();//func for admin or that user to delete comment
	void DeleteAllComment();//func for admin to delete all comments

	int current_user = -1;//紀錄目前是哪個user在操作這個post(新增comment用)  在有使用者要操作時才assign
	std::vector<User*>* usersptr;

	void SavePostToFile(std::ofstream& ofile);//including num of comments
	void LoadPostFromFile(std::ifstream& ifile);
private:
};